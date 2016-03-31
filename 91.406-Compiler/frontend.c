#include "type.h"
#include "frontend.h"
#include "main.h"
#include "utilities.h"
#include "y.tab.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

//Globals
int temp_count = 0;

//Globals
int label_count = 0;

//Externals
extern Stack *symbolStack;
extern SymbolTable *constantTable;
extern char* yytext;
extern int yyleng;
extern SymbolTable *mainTable;
extern int blockDepth;

//Symbol stack SymbolTable manipulation
SymbolTable *top_symboltable()
{
  if (stack_is_empty(symbolStack) == TRUE)
    {
      die ("SymbolTable stack is empty");
      return;
    }
  
  return symbol_stack_peek(symbolStack);
}

SymbolTable *get_scope()
{
  return top_symboltable();
}

//Each call increments label_count
Symbol *make_label()
{
  Symbol *symbol = make_symbol();
  symbol->type = make_type(TYPE_LABEL);
  symbol->value.integer = label_count;

  //Set the symbol name
  char *name = (char*)safe_malloc(sizeof(char) * 8);//assume a 8 byte buffer
  sprintf(name, ".L%d", label_count);
  symbol->name = name;

  debug("Label Name: %s", symbol->name);

  label_count++;

  return symbol;
}

//Either creates a new Symbol or finds the right symbol higher in the tree
//When do we search for the symbol, and when do we create a new one?
//When type != TYPE_VARIABLE, we have a constant of types, look at constant table, or make a new one
//When we have a variable, we check to see if we are in "declaration mode", if block depth is 0
//If in DM, we declare it
//If not, we check other tables for it
void make_name(int type)
{
  Symbol *symb;
  char *s;
  SymbolTable *table;

  if (type == TYPE_VARIABLE)
    table = top_symboltable();
  else
    table = constantTable;

  if (type != TYPE_VARIABLE)
    {
      //we have a constant, check constant table
      if ((symb = (Symbol *)symboltable_lookup(table, yytext)) != NULL)
	{
	  yylval.symbol = symb;
	  return;
	}
    }

  if ((blockDepth != 0) && (type == TYPE_VARIABLE))
    {
      //This variable better be declared in this symbol scope, or the others
      SymbolTable *search = table;
      
      while (search != NULL)
	{
	  //debug("Searching table\n");
	  if ((symb = (Symbol*)symboltable_lookup(search, yytext)) != NULL)
	    {
	      yylval.symbol = symb;
	      return;
	    }

	  search = search->parent;
	}

      //If we got here, we have an undeclared variable
      //Note - this occurs in test6 because bar() is used before being declared
      die("Symbol with name %s undeclared in this or parent scopes", yytext);
    }

 //Time to declare the variable
  symb = make_symbol();
  
  //Copy the text field, even for constants - this will make hashing a lot easier
  s = (char *)safe_malloc(yyleng + 1);
  strcpy(s, yytext);
  s[yyleng] = EndOfString;
  symb->name = s;
  
  if (type != TYPE_VARIABLE)
    {
      if (type == TYPE_NATURAL)
	{
	  //Get int value
	  symb->value.integer = atoi(yytext);
	}
      else if (type == TYPE_NUM)
	{
	  //Get double value
	  symb->value.decimal = atof(yytext);
	}

      //These will all be constants, so their type is pretty vanilla
      symb->type = make_type(type);
    }

  //Now add to our table
  symboltable_insert(table, symb);
  
  yylval.symbol = symb;
}

Symbol *make_temp(int type)
{
  //Save old value
  Symbol *old_yylval = yylval.symbol;
  Symbol *temp;

  //Since our make_name uses blockdepth to determine if variable can be declared, we must save value, reset, and restore
  int old_blockDepth = blockDepth;
  blockDepth = 0;

  //If yytext is smaller in length than our new temp value, yacc will die
  //Save yacc - widen yytext
  yytext = (char*)safe_malloc(sizeof(char*) * 8);

  //Create temp name and put into LEX's buffer
  sprintf(yytext, "T%d", temp_count);
  yyleng = strlen(yytext);

  //Increment the counter
  temp_count++;;

  //Call make name to get a name
  make_name(TYPE_VARIABLE);
  
  //Get our data
  temp = yylval.symbol;

  //We should type it
  temp->type = make_type(TYPE_VARIABLE);

  //Perform the restorations
  yylval.symbol = old_yylval;
  blockDepth = old_blockDepth;

  return temp;
}

void type_identifiers(Tac *tac, Type *type)
{
  while (tac != NULL)
    {
      tac->result->type = type;
      tac = tac->prev;
    }

}

void mark_parameters(Symbol *id, Tac *parameters)
{
  if ((id->type->code != TYPE_FUNCTION) && (id->type->code != TYPE_PROCEDURE))
    die("Frontend::mark_parameters - %s isn't a function or procedure", symbol_to_string(id));

  id->parameters = parameters;

}

void make_variable_type(int code)
{
  Type *t = make_type(code);

  yylval.type = t;
}

void inject_function(char *name, char *link)
{
  debug("Injecting Function: %s mapped to %s", name, link);
  Symbol *inject = make_symbol();
  inject->name = name;
  inject->external = link;
  inject->type = make_type(TYPE_FUNCTION);

  symboltable_insert(mainTable, inject);
}

//Creates a new SymbolTable and pushes on to symbolStack 
SymbolTable *activate_scope(int is_program)
{
  debug("\nActivating new scope");

  SymbolTable *table = make_symboltable();
  if (is_program == TRUE)
    {
      mainTable = table;
      table->nested = 1;//The main program starts at level 1

      //Inject some symbols into our main table
      inject_function("write", "printf");
      inject_function("print", "printf");
    }
  else
    {
      table->parent = top_symboltable();//The main program has no parent
      table->nested = table->parent->nested + 1;
    }
  
  symbol_stack_push(symbolStack, table);
  
  return table;
}

//Pops from symbol stack
SymbolTable *deactivate_scope()
{
  debug("Deactivating scope\n");

  SymbolTable *table = symbol_stack_pop(symbolStack);

  return table;
}

Tac *declare_variable(Symbol *symb)
{
  if (symb->type != NULL)
    {
      die("Variable already declared!");
      return NULL;
    }

  return make_tac(TAC_VARIABLE, symb, NULL, NULL); 
}
