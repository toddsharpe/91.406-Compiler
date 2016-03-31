#ifndef symbollist_h
#define symbollist_h

#include "symbol.h"

struct symbolNode
{
  Symbol * value;
  struct symbolNode * next;
};

typedef struct symbolNode SymbolNode;

typedef SymbolNode * SymbolList;

#endif
