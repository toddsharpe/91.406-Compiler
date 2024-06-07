#include "symbol.h"
#include "main.h"
#include <stdio.h>
#include "type.h"
#include "utilities.h"

Symbol *make_symbol(void)
{
  Symbol *s = (Symbol *)safe_malloc(sizeof(Symbol));
  s->type = NULL;
  s->symbols = NULL;
  s->parameters = NULL;
  s->is_array_element = FALSE;
  s->is_parameter = FALSE;
  s->external = NULL;

  s->offset = 0;

  return s;
}

Symbol *make_array_symbol(Symbol *array, Symbol *index)
{
  Symbol *symbol = (Symbol *)safe_malloc(sizeof(Symbol));
  symbol->is_array_element = TRUE;
  symbol->array = array;
  symbol->index = index;

  char *name = (char*)safe_malloc(sizeof(char)*12);
  symbol->name = name;
  sprintf(name, "%s[%s]", symbol_to_string(array), symbol_to_string(index));

  symbol->type = make_type(array->type->code);

  debug("Made Proxy symbol for %s type %d", symbol_to_string(symbol), symbol->type->code);

  return symbol;
}

char *symbol_to_string(Symbol *symbol)
{
  if (symbol == NULL)
    return "(null)";
  else
    return symbol->name;

}
