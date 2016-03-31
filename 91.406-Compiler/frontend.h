#ifndef frontend_h
#define frontend_h

#include "symbol.h"
#include "stack.h"
#include "type.h"
#include "symboltable.h"
#include "expression.h"
#include "tac.h"

void make_name(int type);

//Scoping variables
SymbolTable *activate_scope(int is_program);
SymbolTable *deactivate_scope();
SymbolTable *get_scope();

Tac *declare_variable(Symbol *symb);
void make_variable_type(int code);
void type_identifiers(Tac *tac, Type *type);
void mark_parameters(Symbol *id, Tac *params);

Symbol *make_temp();
Symbol *make_label();

#endif
