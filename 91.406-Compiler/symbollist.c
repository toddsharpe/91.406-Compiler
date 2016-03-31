#include "symbollist.h"
#include "utilities.h"
#include <stdio.h>

SymbolList make_symbol_list()
{
  SymbolList list = (SymbolList)safe_malloc(sizeof(SymbolNode));
  list->next = NULL;
  list->value = NULL;
}
