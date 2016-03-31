#ifndef symboltable_h
#define symboltable_h

#include "main.h"
#include "stack.h"
#include "symbol.h"

//Defitions
typedef struct symbolTable
{
  struct symbolTable *parent;
  struct symbol *entries[HASHSIZE];
  int nested;
} SymbolTable;

#endif

//SymbolTable functions
SymbolTable* make_symboltable();
void symboltable_insert(SymbolTable *symbolTable, struct symbol *item);
struct symbol *symboltable_lookup(SymbolTable *symbolTable, char *text);
struct symbol *symboltable_recurse(SymbolTable *current, char *text);
void symboltable_dump(SymbolTable *symbolTable);
void symboltable_delete(SymbolTable *table, struct symbol *symbol);

//Symbol Stack functions
SymbolTable* symbol_stack_pop(Stack *stack);
SymbolTable* symbol_stack_peek(Stack *stack);
void symbol_stack_push(Stack *stack, SymbolTable *item);
