#ifndef expression_h
#define expression_h

#include "symbol.h"
#include "tac.h"

struct expression
{
  Symbol *result;
  Tac *tac;
  struct expression *next;
};

typedef struct expression Expression;

//Functions
Expression *make_expression(Expression *next, Symbol *res, Tac *tac);

//Expressions
Expression *expression_unary(int op, Expression *only);
Expression *expression_binary(int op, Expression *first, Expression *second);
Expression *expression_array(Symbol *array, Expression *index);

//Functions
Expression *expression_call(Symbol *function, Expression *arguments);


void dump_expressions(Expression* start);

#endif

