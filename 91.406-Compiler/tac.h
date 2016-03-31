#ifndef tac_h
#define tac_h

#include "symbol.h"
#include <stdarg.h>

typedef struct tac
{
  struct tac *next;
  struct tac *prev;
  int op;

  //Bennett uses too many damn unions

  //When op is control flow
  struct tac *location;
  struct symbol *condition;

  //When op is binary/unary
  struct symbol *result;
  struct symbol *operand1;
  struct symbol *operand2;

} Tac;

//Prototypes
Tac *make_tac(int op, struct symbol *result, struct symbol *operand1, struct symbol *operand2);
Tac *make_label_tac(int op, struct tac *location, struct symbol *condition);

Tac *join_tac(Tac *first, Tac *second);
Tac *reverse_tac(Tac *first);
Tac *join_tacs(int num, ...);

Tac *last_tac(Tac *first);

//Debug
void tac_dump(Tac *tac);

#endif
