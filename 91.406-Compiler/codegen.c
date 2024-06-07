#include "codegen.h"
#include "tac.h"
#include "regdesc.h"
#include "main.h"
#include "utilities.h"
#include <stdlib.h>
#include <stdio.h>
#include "symbol.h"
#include "string.h"

Symbol *current_scope;
extern Symbol *symbol_one;
int arg_count = 0;
extern int comment_mode;

void generate_code(FILE *file, Tac *code, SymbolTable *programTable, SymbolTable *constantTable)
{
  //Get our register descriptors
  RegDesc registers[REG_MAX];
  Tac *current = code;

  //Clear registers
  name_registers(registers);
  clear_registers(registers);

  //Put our constant strings in the file
  code_strings(file, constantTable);

  while (current != NULL)
    {
      code_comment(file, "Current %d", current);
      code_tac(file, registers, current);

      current = current->next;
    }
}

void code_tac(FILE *file, RegDesc *registers, Tac *current)
{
  switch (current->op)
    {
    case TAC_BEGINPROGRAM:
      code_main(file);
      code_begin_function(file, current->result);
      break;

    case TAC_BEGINFUNCTION:
      code_begin_function(file, current->result);
      break;

    case TAC_ENDFUNCTION:
      code_end_function(file, registers);
      break;

    case TAC_RETURN:
      code_return(file, registers, current->result);
      break;

    case TAC_ENDPROGRAM:
      code_end_function(file, registers);
      break;

    case TAC_GOTO:
      code_jump(file, registers, JUMP, current->location->result, NULL);
      break;

    case TAC_IFZ:
      code_jump(file, registers, JUMP_NE, current->location->result, current->condition);
      break;

    case TAC_IFNZ:
      code_jump(file, registers, JUMP_E, current->location->result, current->condition);
      break;

    case TAC_ADD:
      code_binary(file, registers, ADD, current->result, current->operand1, current->operand2);
      break;

    case TAC_SUBTRACT:
      code_binary(file, registers, SUBTRACT, current->result, current->operand1, current->operand2);
      break;

    case TAC_MULTIPLY:
      code_binary(file, registers, MULTIPLY, current->result, current->operand1, current->operand2);
      break;

    case TAC_DIVIDE:
      code_binary(file, registers, DIVIDE, current->result, current->operand1, current->operand2);
      break;

    case TAC_NOT:
      //FIX 5-19-2011 - INVERT is not what we want - thats a bit wise invert
      //Since we are using booleans, just xor them
      //code_unary(file, registers, INVERT, current->result, current->operand1);
      code_binary(file, registers, LOGIC_XOR, current->result, current->operand1, symbol_one);
      break;

    case TAC_NEGATIVE:
      code_unary(file, registers, NEGATE, current->result, current->operand1);
      break;

    case TAC_AND:
      code_binary(file, registers, LOGIC_AND, current->result, current->operand1, current->operand2);
      break;

    case TAC_OR:
      code_binary(file, registers, LOGIC_OR, current->result, current->operand1, current->operand2);
      break;

    case TAC_MOD:
      code_binary(file, registers, ATT_MOD, current->result, current->operand1, current->operand2);
      break;

    case TAC_COPY:
      code_copy(file, registers, current->result, current->operand1);
      break;

    case TAC_ARG:
      code_arg(file, registers, current->result);
      break;

    case TAC_CALL://On a TAC call, the function is the operand, and the return is the result
      code_call(file, registers, current->operand1, current->result);
      break;

    case TAC_LABEL:
      debug("Code_Label - Symbol: %s", symbol_to_string(current->result));
      code_flush_all(file, registers);
      fprintf(file, "%s:\n", current->result->name);
      break;

    case TAC_GT:
      code_compare(file, registers, IS_GREATER, current->result, current->operand1, current->operand2);
      break;

    case TAC_LT:
      code_compare(file, registers, IS_LESS, current->result, current->operand1, current->operand2);
      break;

    case TAC_GTE:
      code_compare(file, registers, IS_GREATER_EQUAL, current->result, current->operand1, current->operand2);
      break;

    case TAC_LTE:
      code_compare(file, registers, IS_LESS_EQUAL, current->result, current->operand1, current->operand2);
      break;

    case TAC_EQUAL:
      code_compare(file, registers, IS_EQUAL, current->result, current->operand1, current->operand2);
      break;

    case TAC_NOTEQUAL:
      code_compare(file, registers, IS_NOT_EQUAL, current->result, current->operand1, current->operand2);
      break;

    case TAC_VARIABLE:
      //do nothing
      break;

    case TAC_NOP:
      //Do nothing
      break;

    default:
      die("Unrecognized TAC: %d", current->op);
      break;

    }
}

char *get_destination(FILE *file, RegDesc *registers, Symbol *symbol)
{
  debug("Getting destination for %s in scope %s", symbol->name, current_scope->name);

  char *name;
  if (symbol->is_array_element)
    name = symbol->array->name;
  else
    name = symbol->name;

  Symbol *lookup = symboltable_lookup(current_scope->symbols, name);
  
  char *base;
  if (lookup == NULL)
    {
      debug("Variable declared in another scope");
    
      //Load our SL into EDI
      code_instruction(file, MOVE, CURRENT_STATIC_LINK, EDI);

      int hops = 0;
      SymbolTable *current = current_scope->symbols;
      while (symboltable_lookup(current, name) == NULL)
	{
	  hops++;
	  current = current->parent;
	}

      int i;
      for (i = 0; i < hops - 1; i++)
	{
	  code_instruction(file, MOVE, make_relative_address(0, EDI), EDI);
	}

      code_instruction(file, ADD, make_integer(4), EDI);

      base = EDI;
    }
  else
    {
      base = EBP;
    }

  if (symbol->is_array_element == FALSE)
    {
      code_comment(file, "Variable %s", symbol->name);
      return make_memory_offset(symbol, base);
    }
  else
    {
      //We have a bit more work
      //If the index is a constant, we can give a constant address
      Symbol *array = symbol->array;
      Symbol *index = symbol->index;
      
      if (index->type->code == TYPE_NATURAL)
	{
	  //Calculate constant offset
	  int offset = array->type->c + index->value.integer * 4;
	  debug("Constant offset");
	  code_comment(file, "Array Constant Index for %s", symbol->name);
	  return make_relative_address(offset, base);
	}
      else
	{
	  //AT&T has a syntax for arrays:
	  //0(%ebp, %esi, 4) -> 0 + %ebp + %esi * 4
	  //I want to avoidl multiplying the index by negative one...lets think about this
	  //Well I flipped the array in memory so the last index is first, we now solved our problem

	  code_comment(file, "Array Variable Index for %s", symbol->name);

	  //Step 1: load index
	  code_instruction(file, MOVE, get_location(file, registers, index), ESI);
	  //code_instruction(file, MOVE, get_destination(file, registers, index), ESI);

	  //Step 2: print
	  char *dest = make_array_offset(array->type->c, base, ESI); 
	  code_comment(file, "Index: %s", dest);
	  return dest;
	}
    }
}

char *get_location(FILE *file, RegDesc *registers, Symbol *symbol)
{
  debug("Get location: %s", symbol->name);
  int reg = registers_contains(registers, symbol);
  if (reg >= 0)
    return registers[reg].name;
  else
    {
      return get_destination(file, registers, symbol);
    }
}

void code_arg(FILE *file, RegDesc *registers, Symbol *result)
{
  arg_count++;
  debug("Code_Arg - Symbol: %s, Arg Count: %d", symbol_to_string(result), arg_count);

  code_spill_all(file, registers);
  clear_registers(registers);
  
  if (result->type->code == TYPE_NATURAL)
    code_instruction(file, PUSH, make_integer(result->value.integer), NULL);
  else
    code_instruction(file, PUSH, get_location(file, registers, result), NULL);
}

void code_return(FILE *file, RegDesc *registers, Symbol *result)
{
  //FIX: 5-19-2011
  //We can't simply load eax, as function calls can come after this return statement
  //and mess up with what we want to return
  //Therefore, we must put this value in memory

  //Spill EAX
  //code_spill_reg(file, registers, REG_EAX);

  //Load eax
  //code_load_reg(file, registers, REG_EAX, result);

  //Load return symbol into register if it isn't already there
  int source_reg = get_result_register(file, registers, result);

  code_instruction(file, MOVE, registers[source_reg].name, FUNCTION_RETURN_VALUE);
}

//Here we should make the call, and if we are saving the result, tell the regdesc that
void code_call(FILE *file, RegDesc *registers, Symbol *function, Symbol *result)
{
  code_spill_all(file, registers);
  clear_registers(registers);

  if (function->external != NULL)
    {
      //If this is printf, push the appropriate string
      if (strcmp(function->external, "printf") == 0)
	{
	  arg_count++;
	  code_instruction(file, PUSH, "$.LC0", NULL);
	}
      //This an external call, so drop the instruction using the linked name
      code_instruction(file, CALL, function->external, NULL);
    }
  else
    {
      //This is an internal routine
      //Therefore, we need to set up the static link
      int caller_nested = current_scope->symbols->nested;
      int callee_nested = function->symbols->nested;
      debug("Static Linking - Caller: %d to Callee: %d", caller_nested, callee_nested);
      if (caller_nested < callee_nested)
      	{
	  //This is one hop, so we can Load address
	  code_instruction(file, LOAD_ADDRESS, CURRENT_STATIC_LINK, EAX);
	  code_instruction(file, MOVE, EAX, NEXT_STATIC_LINK);
	}
      else
	{
	  code_instruction(file, MOVE, CURRENT_STATIC_LINK, EDI);
	  int i;
	  int hops = caller_nested - callee_nested + 1;
	  for (i = 0; i < hops - 1; i++)
	    code_instruction(file, MOVE, make_relative_address(0, EDI), EDI);

	  code_instruction(file, MOVE, EDI, NEXT_STATIC_LINK);
	}
      
      code_instruction(file, CALL, function->name, NULL);
    }

  //Clean up the stack
  if (arg_count > 0)
    {
      code_instruction(file, ADD, make_integer(arg_count * 4), ESP);
      arg_count = 0;
    }

  if (result != NULL)
    {
      //Return values are put in eax
      insert_register(registers, REG_EAX, result, TRUE); 
    }
}

void code_copy(FILE *file, RegDesc *registers, Symbol *result, Symbol *operand1)
{
  int source = get_result_register(file, registers, operand1);
  
  insert_register(registers, source, result, TRUE);

  if (result->is_array_element == TRUE)
    {
      code_spill_reg(file, registers, source);
    }

  debug("Copied %s to %s Array %d", operand1->name, result->name, result->is_array_element);
}

// result = operand1 op operand2
void code_binary(FILE *file, RegDesc *registers, char *op, Symbol *result, Symbol *operand1, Symbol *operand2)
{
  int dest_reg;
  if ((strcmp(op, ATT_MOD) == 0) || (strcmp(op, MULTIPLY) == 0) || (strcmp(op, DIVIDE) == 0))
    {
      //Spill eax
      code_spill_reg(file, registers, REG_EAX);
      
      //Set destination
      dest_reg = REG_EAX;
      clear_register(registers, dest_reg);

      code_load_reg(file, registers, REG_EAX, operand1);
      insert_register(registers, dest_reg, operand1, FALSE);

      if ((strcmp(op, ATT_MOD) == 0) || (strcmp(op, DIVIDE) == 0))
	code_instruction(file, QUADWORD, NULL, NULL);
    }
  else
    {
      dest_reg = get_result_register(file, registers, operand1);
    }

  int source_reg = get_argument_register(file, registers, operand2, dest_reg);

  debug("Code Binary %s Dest: %d Source: %d", op, dest_reg, source_reg);

  if (strcmp(op, ATT_MOD) == 0)
    {
      code_instruction(file, DIVIDE, registers[source_reg].name, registers[dest_reg].name);
      clear_register(registers, REG_EDX);
      insert_register(registers, REG_EDX, result, TRUE);
    }
  else
    {
      code_instruction(file, op, registers[source_reg].name, registers[dest_reg].name);
      clear_register(registers, dest_reg);
      insert_register(registers, dest_reg, result, TRUE);
    }
}

void code_jump(FILE *file, RegDesc *registers, char *op, Symbol *location, Symbol *condition)
{
  debug("Code_Jump -  Op: %s Location: %s Condition: %s", op, symbol_to_string(location), symbol_to_string(condition));

  code_spill_all(file, registers);
  clear_registers(registers);

  //If there is a condition, compare it to 1
  if (condition != NULL)
    {
      int dest_reg = get_result_register(file, registers, condition);
      int source_reg = get_argument_register(file, registers, symbol_one, dest_reg);
      debug("Dest %d Source %d", dest_reg, source_reg);
      //code_instruction(file, COMPARE, registers[source_reg].name, registers[dest_reg].name);
      code_instruction(file, COMPARE, registers[dest_reg].name, registers[source_reg].name);
    }

  code_flush_all(file, registers);

  //Output jump instruction
  code_instruction(file, op, location->name, NULL);
}

void code_compare(FILE *file, RegDesc *registers, char *op, Symbol *result, Symbol *operand1, Symbol *operand2)
{
  debug("%s = %s %s %s", result->name, op, operand1->name, operand2->name); 

  int dest_reg = get_result_register(file, registers, operand1);
  int source_reg = get_argument_register(file, registers, operand2, dest_reg);

  debug("Code Compare Dest: %d Source: %d", dest_reg, source_reg);

  //Compare
  code_instruction(file, COMPARE, registers[source_reg].name, registers[dest_reg].name);
  //code_instruction(file, COMPARE, registers[dest_reg].name, registers[source_reg].name);

  //Get the low bytes
  char *low = make_low(registers[dest_reg].name);

  //Get the value
  code_instruction(file, op, low, NULL);

  //Now clear remaining bytes
  code_instruction(file, "movzbl", low, registers[dest_reg].name);

  //Update
  clear_register(registers, dest_reg);
  insert_register(registers, dest_reg, result, TRUE);
}

void code_unary(FILE *file, RegDesc *registers, char *op, Symbol *result, Symbol *operand)
{
  int dest_reg = get_result_register(file, registers, operand);
  
  debug("Code Unary %s Dest: %d", op, dest_reg);
  
  code_instruction(file, op, registers[dest_reg].name, NULL);
  
  clear_register(registers, dest_reg);
  insert_register(registers, dest_reg, result, TRUE);
}

void code_begin_function(FILE *file, Symbol *symbol)
{
  debug("Setting Scope to %s from %s", symbol_to_string(symbol), symbol_to_string(current_scope));
  //Set our scope
  current_scope = symbol;

  //print label
  fprintf(file, "%s:\n", symbol->name);
  
  //print our function header
  code_instruction(file, PUSH, EBP, NULL);
  code_instruction(file, MOVE, ESP, EBP);
  
  if (symbol->symbols->nested == 1)
    {
      //this is main
      code_instruction(file, MOVE, make_integer(0), CURRENT_STATIC_LINK);
    }

  //Get the last offset, and adjust stack pointer
  //FIX 5-19-2011
  //int offset = -4;
  int offset = -8;
  int i;
  SymbolTable *table = symbol->symbols;
  Symbol *current;
  for (i = 0; i < HASHSIZE; i++)
    {
      current = table->entries[i];
      
      while (current != NULL)
	{
	  if (current->offset < offset)
	    offset = current->offset;
	  current = current->next;
	}
    }
  
  //Set esp to point to the next location after our variables, make it positive so we subtract
  int esp_fix = -offset;
  
  code_instruction(file, SUBTRACT, make_integer(esp_fix), ESP);
}

void assign_offsets(Symbol *symbol)
{
//At this point, we need to assign offsets to our symbols in the table
  SymbolTable *table = symbol->symbols;
  int i;
  Symbol *current;
  Type *type;
  //int offset = -4;//Lets leave the first 4 for our static link
  //FIX 5-19-2011
  int offset = -8; //Reserve 4 for static link and 4 for return value

  for (i = 0; i < HASHSIZE; i++)
    {
      current = table->entries[i];
      
      while (current != NULL)
	{
	  if (current->is_parameter != TRUE)
	    {
	      type = current->type;
	      int code = type->code;
	      if ((code != TYPE_PARAMETER) && (code != TYPE_PROGRAM) && (code != TYPE_PROCEDURE) && (code != TYPE_FUNCTION) && (code != TYPE_LABEL))
		{
		  //we have a variable here that needs to take up space on the stack
		  //subtract an offset, and assign it
		  offset -= get_size(current->type);
		  current->offset = offset;
		  //offset -= get_size(current->type);
		  
		  //Set array C value
		  //TODO: Fix for multidimensional arrays and values of larger than 4 bytes
		  if (type->is_array == TRUE)
		    {
		      type->c = current->offset - type->intervals->start * 4;
		    }
		}
	    }
	  current = current->next;
	}
    }
  
  
  
  //Now assign our parameters
  offset = 4;//first 4 bytes below is return address
  Tac *tac_current = symbol->parameters;
  while ((tac_current != NULL) && (tac_current->op != TAC_BEGINFUNCTION))
    {
      offset += get_size(tac_current->result->type);
      tac_current->result->offset = offset;
      tac_current = tac_current->prev;
    }

  //display
  printf("Displaying Symbol Table for: %s\n", symbol->name);
  symboltable_dump(table);
  printf("\n");
}

void code_static_link(FILE *file, Symbol *function)
{

}

void code_end_function(FILE *file, RegDesc *registers)
{
  //FIX 5-19-2011
  if (current_scope->type->code == TYPE_FUNCTION)
    {
      //We need to return this value

      //Spill eax
      code_spill_reg(file, registers, REG_EAX);

      //Load it
      code_instruction(file, MOVE, FUNCTION_RETURN_VALUE, EAX);
    }

  code_flush_all(file, registers);

  code_instruction(file, LEAVE, NULL, NULL);
  code_instruction(file, RETURN, NULL, NULL);
}

void code_strings(FILE *file, SymbolTable *table)
{
  int i;
  Symbol *current;
  int count = 0;

  for (i = 0; i < HASHSIZE; i++)
    {
      current = table->entries[i];
      
      //Iterate through this chian
      while (current != NULL)
	{
	  if (current->type->code == TYPE_STRING)
	    {
	      //Create the label
	      char *label = (char*)safe_malloc(sizeof(char) * 8);
	      sprintf(label, ".LC%d", count);
	      current->label = label;

	      fprintf(file, "%s:\n\t.string \"%s\"\n", label, current->value.string);
	      count++;
	    }

	  current = current->next;
	}
    }

  fprintf(file, "\n");
}

void code_main(FILE *file)
{
  fprintf(file, ".global main\n\n");
}

//Changes to the syntax will be done here
void code_instruction(FILE *file, char *mnemonic, char *source, char *destination)
{
  if (source == NULL)
    fprintf(file, "\t%s\n", mnemonic);
  else if (destination == NULL)
    fprintf(file, "\t%s\t%s\n", mnemonic, source);
  else
    fprintf(file, "\t%s\t%s,%s\n", mnemonic, source, destination);
}

void code_comment(FILE *file, const char *format, ...)
{
  if (comment_mode == FALSE)
    return;

  //Print beginnning
  fprintf(file, "\t# ");

  //Print middle
  va_list args;
  va_start(args, format);
  vfprintf(file, format, args);
  va_end(args);

  //Print end
  fprintf(file, "\n");
}

int get_size(Type *type)
{
  int size = 4;

  if (type->is_array == FALSE)
    return size;
  else
    {
      int cells = 0;
      Interval *current = type->intervals;
      while (current != NULL)
	{
	  cells += (current->end - current->start + 1);
	  current = current->next;
	}
      return cells * size;
    }
}

void code_spill_reg(FILE *file, RegDesc *registers, int reg)
{
  RegDesc desc = registers[reg];

  if (desc.modified == FALSE)
    return;//No need to update memory

  debug("Spilling Register %s holding %s", desc.name, desc.symbol->name);

  char *dest = get_destination(file, registers, desc.symbol);
  code_instruction(file, MOVE, desc.name, dest);
  registers[reg].modified = FALSE;//Don't keep spilling
}

void code_spill_all(FILE *file, RegDesc *registers)
{
  int i;
  for (i = 0; i <REG_MAX; i++)
    code_spill_reg(file, registers, i);
}

void code_flush_all(FILE *file, RegDesc *registers)
{
  code_spill_all(file, registers);
  clear_registers(registers);
}

void code_load_reg(FILE *file, RegDesc *registers, int reg, Symbol *symbol)
{
  char *name = registers[reg].name;

  debug("Code_Load_Reg %s to %d", symbol->name, reg);

  switch (symbol->type->code)
    {
    case TYPE_NATURAL:
      code_instruction(file, MOVE, make_integer(symbol->value.integer), name);
      break;

    default:
      code_instruction(file, MOVE, get_destination(file, registers, symbol), name);
      break;
    }
}

char *make_memory_offset(Symbol *name, char *base)
{
  char *dest = (char*)safe_malloc(sizeof(char) * 8);
  sprintf(dest, "%d(%s)", name->offset, base);
  return dest;
} 

char *make_relative_address(int addr, char *base)
{
  char *dest = (char*)safe_malloc(sizeof(char) * 8);
  sprintf(dest, "%d(%s)", addr, base);
  return dest;
}

char *make_integer(int i)
{
  char *dest = (char*)safe_malloc(sizeof(char) * 8);
  sprintf(dest, "$%d", i);
  return dest;
}

char *make_array_offset(int c, char *base, char *index)
{
  char *dest = (char*)safe_malloc(sizeof(char) * 24);
  sprintf(dest, "%d(%s, %s, %d)", c, EBP, index, 4);
  return dest;
}

char *make_low(char *reg)
{
  char *dest = (char*)safe_malloc(sizeof(char) * 4);
  sprintf(dest, "%%%cl", reg[2]);
  return dest; 
}
