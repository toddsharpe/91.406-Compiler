#ifndef tacend_h
#define tacend_h

#include "symbol.h"
#include "expression.h"
#include "tac.h"

Tac *tac_assign(Symbol *symbol, Expression *expression);
Tac *tac_if_else(Expression *condition, Tac *true, Tac *false);
Tac *tac_while(Expression *condition, Tac *body);

Tac *tac_function(Symbol *function, Tac *arguments, Tac *body);
Tac *tac_procedure_start(Symbol *function, Tac *arguments);

#endif

