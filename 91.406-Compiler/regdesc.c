#include "regdesc.h"
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "symbol.h"
#include "codegen.h"

void name_registers(RegDesc *registers)
{
  registers[REG_EAX].name = EAX;
  registers[REG_EBX].name = EBX;
  registers[REG_ECX].name = ECX;
  registers[REG_EDX].name = EDX;
  //registers[REG_ESI].name = ESI;
  //registers[REG_EDI].name = EDI;
  //registers[REG_EBP].name = EBP;
  //registers[REG_ESP].name = ESP;
}

int registers_contains(RegDesc *registers, Symbol *symbol)
{
  int i;
  for (i = 0; i < REG_MAX; i++)
    {
      if (registers[i].symbol == symbol)
	return i;
    }
  return -1;
}

int get_result_register(FILE *file, RegDesc *registers, Symbol *symbol)
{
  return get_argument_register(file, registers, symbol, -1);
}

int get_argument_register(FILE *file, RegDesc *registers, Symbol *symbol, int avoid_reg)
{
  int i;

  debug("Get_Argument_register %s avoiding %d", symbol->name, avoid_reg);

  //Check if we are already in a register
  for (i = 0; i < REG_MAX; i++)
    {
      if (registers[i].symbol == symbol)
	{
	  if (avoid_reg == -1)//TODO: decide and fix
	    code_spill_reg(file, registers, i);
	  return i;
	}
    }

  //Check empty registers
  for (i = 0; i < REG_MAX; i++)
    {
      if ((registers[i].symbol == NULL) && (i != avoid_reg))
	{
	  code_load_reg(file, registers, i, symbol);
	  return i;
	}
    }

  //Check unmodified registers
  for (i = 0; i < REG_MAX; i++)
    {
      if ((registers[i].modified == FALSE) && (i != avoid_reg))
	{
	  clear_register(registers, i);//Since we don't need to spill, just remove
	  code_load_reg(file, registers, i, symbol);
	  return i;
	}
    }

  //Now check modified registers
  for (i = 0; i < REG_MAX; i++)
    {
      if (i != avoid_reg)
	{
	  code_spill_reg(file, registers, i);
	  clear_register(registers, i);
	  code_load_reg(file, registers, i, symbol);
	  return i;
	}
    }
  
  die("This should never happen...we didn't find any register...");
}

void clear_registers(RegDesc *registers)
{
  int i;
  for (i = 0; i < REG_MAX; i++)
    {
      clear_register(registers, i);
    }
}

void registers_dump(RegDesc *registers)
{
  int i;
  RegDesc current;

  printf("Dumping Registers\n");
  
  for (i = 0; i < REG_MAX; i++)
    {
      current = registers[i];
      printf("Register: %d Name %s Symbol: %s Modified: %d\n", i, current.name, symbol_to_string(current.symbol), current.modified);
    }

  printf("Done\n");
}

void clear_register(RegDesc *registers, int reg)
{
  registers[reg].symbol = NULL;
  registers[reg].modified = FALSE;
}

void insert_register(RegDesc *registers, int reg, Symbol *symbol, int modified)
{
  debug("Inserted symbol %s to Register %d", symbol->name, reg);
  registers[reg].symbol = symbol;
  registers[reg].modified = modified;
}
