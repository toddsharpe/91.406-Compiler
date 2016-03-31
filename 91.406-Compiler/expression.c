#include "expression.h"
#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include "frontend.h"
#include "symboltable.h"
#include "symbol.h"

extern SymbolTable *constantTable;

Expression *make_expression(Expression *next, Symbol *res, Tac *tac)
{
  Expression *exp = (Expression*)safe_malloc(sizeof(Expression));
  exp->result = res;
  exp->tac = tac;
  exp->next = next;
  
  debug("Expression for %s", symbol_to_string(res));

  return exp;
}

void dump_expressions(Expression *start)
{
  Expression *current = start;
  while (current != NULL)
    {
      printf("Current %d Next %d Result %s Tac %d\n", current, current->next, current->result->name, current->tac);

      current = current->next;
    }
}

Expression *expression_unary(int op, Expression *only)
{
  Tac *temp;
  Tac *result;
  Symbol *temp_variable;

  debug("Unary: %d Symbol: %s Type: %d", op, only->result->name, only->result->type->code);

  //Constant folding
  if (only->result->type->code == TYPE_NATURAL)
    {
      //Fix 5-19-2011
      //Since each symbol is added to the constant table only once
      //if we delete a symbol that was used previously
      //We wil have problems
      //Instead - make a new symbol, and do the wiring

      //Remove from symbol table
      //symboltable_delete(constantTable, only->result);

      Symbol *fold_result = make_symbol();
      fold_result->type = make_type(TYPE_NATURAL);
      fold_result->name = (char*)safe_malloc(sizeof(char) * 12);

      switch (op)
	{
	case TAC_NEGATIVE:
	  //only->result->value.integer = - only->result->value.integer;
	  fold_result->value.integer = - only->result->value.integer;

	  //Make new name, overwriting old name
	  //sprintf(only->result->name, "%d", only->result->value.integer);
	  break;
	}

      //rewire expression to use new result
      only->result = fold_result;

      //Fix name
      sprintf(only->result->name, "%d", only->result->value.integer);

      //Reinsert
      symboltable_insert(constantTable, only->result);

      //debug("Folded constant to %d", only->result->value.integer);
      return only;
    }

  temp_variable = make_temp();
  temp_variable->type = make_type(TYPE_VARIABLE);//Generic variable type

  //Since we dont have a constant, we make a new tac with a temporary symbol
  temp = make_tac(TAC_VARIABLE, temp_variable, NULL, NULL);
  temp->prev = only->tac;
  
  //This is result of "calling" operator
  
  //FIX 5-19-2011
  //The backend looks for the only operand in operand1, not operand 2
  //result = make_tac(op, temp->result, NULL, only->result);

  result = make_tac(op, temp->result, only->result, NULL);
  result->prev = temp;

  //Rewire the expression struct to point to the true result
  only->result = temp->result;
  only->tac = result;

  return only;
}

Expression *expression_binary(int op, Expression *first, Expression *second)
{
  Tac *temp;
  Tac *result;
  Symbol *temp_variable;

  debug("Binary Op: %d First: %s Type: %d Second: %s Type: %d", op, first->result->name, first->result->type->code, second->result->name, second->result->type->code);

  //Constant folding
  //if ((first->result->type->code == TYPE_NATURAL) && (second->result->type->code == TYPE_NATURAL)
  //    && ((op == TAC_ADD) || (op == TAC_SUBTRACT) || (op == TAC_MULTIPLY) || (op == TAC_DIVIDE)))
  
  if ((first->result->type->code == TYPE_NATURAL) && (second->result->type->code == TYPE_NATURAL))
  {
    //Fix 5-19-2011
    //For same reasons in expression_unary

    //Remove both symbols from symbol table
    //symboltable_delete(constantTable, first->result);
    //symboltable_delete(constantTable, second->result);
      
    Symbol* fold_result = make_symbol();
    fold_result->type = make_type(TYPE_NATURAL);
    fold_result->name = (char*)safe_malloc(sizeof(char) * 12);

    switch (op)
      {
      case TAC_ADD:
	fold_result->value.integer = first->result->value.integer + second->result->value.integer;
	break;
	
      case TAC_SUBTRACT:
	fold_result->value.integer = first->result->value.integer - second->result->value.integer;
	break;
	
      case TAC_MULTIPLY:
	fold_result->value.integer = first->result->value.integer * second->result->value.integer;
	break;
	
      case TAC_DIVIDE:
	fold_result->value.integer = first->result->value.integer / second->result->value.integer;
	break;
	
      case TAC_GT:
	fold_result->value.integer = first->result->value.integer > second->result->value.integer;
	break;
	
      case TAC_LT:
	fold_result->value.integer = first->result->value.integer < second->result->value.integer;
	break;
	
      case TAC_GTE:
	fold_result->value.integer = first->result->value.integer >= second->result->value.integer;
	break;
	
      case TAC_LTE:
	fold_result->value.integer = first->result->value.integer <= second->result->value.integer;
	break;
	
      case TAC_EQUAL:
	fold_result->value.integer = first->result->value.integer == second->result->value.integer;
	break;
	
      case TAC_NOTEQUAL:
	fold_result->value.integer = first->result->value.integer != second->result->value.integer;
	break;
	
      default:
	die("Unrecognized Binary Operation: %s", op);
	break;

      }

    //Rewire expression
    first->result = fold_result;
    
    //Now fix the symbol name
    sprintf(first->result->name, "%d", first->result->value.integer);
    
    //Insert the symbol back
    symboltable_insert(constantTable, first->result);
    
    //Give back some resources
    //free(second->result);
    free(second);
    
    debug("Folded constant %d", first->result->value.integer);
    
    return first;
  }

  //Create temp
  temp_variable = make_temp();
  temp_variable->type = make_type(TYPE_VARIABLE);//Generic variable type

  temp = make_tac(TAC_VARIABLE, temp_variable, NULL, NULL);
  temp->prev = join_tac(first->tac, second->tac);

  //Call operator
  result = make_tac(op, temp->result, first->result, second->result);
  result->prev = temp;

  //Rewire the expression
  first->result = temp->result;
  first->tac = result;

  //Cleanup
  free(second);
  return first;
}

//the main idea here is to create a new Tac for an array
//The first argument we will have as the array symbol itself
//The second argument will be the symbol from the expression
//And we will join the tacs, so the array tac is AFTER the index tac
Expression *expression_array(Symbol *array, Expression *index)
{
  debug("Creating expression %s[%s]", symbol_to_string(array), symbol_to_string(index->result));

  if (array->type->is_array != TRUE)
    die("Symbol %s isn't an array", symbol_to_string(array));

  Symbol *proxy = make_array_symbol(array, index->result);

  debug("Created proxy symbol %s", symbol_to_string(proxy));
  
  //Repurpose index
  index->result = proxy;
  
  return index;
}

Expression *expression_call(Symbol *function, Expression *arguments)
{
  debug("Creating expression call for %s Type: %d", symbol_to_string(function), function->type->code);

  if ((function->type->code != TYPE_FUNCTION) && (function->type->code != TYPE_PROCEDURE))
    die("Symbol %s isn't a function or procedure", symbol_to_string(function));

  Expression *alt;
  Symbol *result = NULL;//If this is a function, it returns a value
  Tac *code;
  Tac *temp;

  if ((function->type->code == TYPE_FUNCTION) && (function->external == NULL))
    {
      //Create symbol for result, and declare variable
      result = make_temp();
      code = make_tac(TAC_VARIABLE, result, NULL, NULL);
    }
  else
    {
      code = make_tac(TAC_NOP, NULL, NULL, NULL);
    }

  //Connect up rest of arguments
  alt = arguments;
  while (alt != NULL)
    {
      code = join_tac(code, alt->tac);

      alt = alt->next;
    }

  //Generate argument instructions
  while (arguments != NULL)
    {
      temp = make_tac(TAC_ARG, arguments->result, NULL, NULL);
      temp->prev = code;
      code = temp;

      alt = arguments->next;
      free(arguments);
      arguments = alt;
    }

  //temp = make_label_tac(TAC_CALL, function->label, result);
  temp = make_tac(TAC_CALL, result, function, NULL);
  temp->prev = code;
  code = temp;

  return make_expression(NULL, result, code);
}

