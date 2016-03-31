#ifndef regdesc_h
#define regdesc_h

#include "symbol.h"
#include <stdio.h>

struct regdesc
{
  char *name;
  Symbol *symbol;
  int modified;
};

typedef struct regdesc RegDesc;

//Prototypes
void clear_registers(RegDesc *registers);
void registers_dump(RegDesc *registers);
void name_registers(RegDesc *registers);

//CRUD
void clear_register(RegDesc *registers, int reg);
void insert_register(RegDesc *registers, int reg, Symbol *symbol, int modified);

//Getting registers
int get_result_register(FILE *file, RegDesc *registers, Symbol *symbol);
int get_argument_register(FILE *file, RegDesc *registers, Symbol *symbol, int avoid_reg);

int registers_contains(RegDesc *registers, Symbol *symbol);

#endif
