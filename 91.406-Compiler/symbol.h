#ifndef symbol_h
#define symbol_h

#include "tac.h"
#include "type.h"
#include "symboltable.h"

typedef struct symbol
{
  struct symbol *next;
  Type *type;
  
  //Is this a symbol or an array element
  int is_array_element;
  int is_parameter;

  //Name - every symbol is given a name, even if its just the value converted to a string
  char *name;

  //When the ID can declare variables, they are placed here
  struct symbolTable *symbols;
 
  //When the ID is a function, procedure, or program, it has paramaters
  struct tac * parameters;

  //When we generate code, each symbol has an offset
  int offset;

  //If the symbol is an external function call, we need a name for it:
  char *external;
 
  //This holds the constants
  union
  {
    int integer;
    double decimal;
    char *string;
  } value;

  //When this is a string, we need to reference it via a label
  char *label;

  //When we are referencing an item in an array, we need to uses these fields
  struct symbol *array;
  struct symbol *index;

} Symbol;

//Functions
Symbol *make_symbol(void);
Symbol *make_array_symbol(Symbol *array, Symbol *index);
char *symbol_to_string(Symbol *symbol);

#endif
