#ifndef codegen_h
#define codegen_h

#include <stdio.h>
#include "tac.h"
#include "type.h"
#include "symbol.h"
#include "regdesc.h"
#include <stdarg.h>

//Here are our instructions
#define PUSH "pushl"
#define MOVE "movl"
#define QUADWORD "cltd"
#define LOAD_ADDRESS "leal"

//Jumps
#define JUMP "jmp"
#define JUMP_NE "jne"
#define JUMP_E "je"
#define JUMP_Z "jz"
#define JUMP_NZ "jnz"

//Math
#define ADD "addl"
#define SUBTRACT "subl"
#define MULTIPLY "imull"
#define DIVIDE "idivl"
#define NEGATE "negl"
#define ATT_MOD "mod"//Yes, I know this isn't a real instruction...

//Control flow
#define CALL "call"
#define LEAVE "leave"
#define RETURN "ret"

//Logic
#define INVERT "notl"
#define LOGIC_AND "andl"
#define LOGIC_OR "orl"
#define LOGIC_XOR "xorl"//Added 5-19-2011

//Comparing
#define COMPARE "cmpl"
#define IS_EQUAL "sete"
#define IS_NOT_EQUAL "setne"
#define IS_GREATER "setg"
#define IS_GREATER_EQUAL "setge"
#define IS_LESS "setl"
#define IS_LESS_EQUAL "setle"

//Define our registers
#define EAX "%eax"
#define EBX "%ebx"
#define ECX "%ecx"
#define EDX "%edx"
#define ESI "%esi"
#define EDI "%edi"
#define EBP "%ebp"
#define ESP "%esp"

//Specific memory locations
#define CURRENT_STATIC_LINK "-4(%ebp)"
#define NEXT_STATIC_LINK "-12(%esp)"//-4 from esp is ret addr, -8 is old bp, sl is -12
#define FUNCTION_RETURN_VALUE "-8(%ebp)"

void assign_offsets(Symbol *symbol);

//Generate assembly code
void generate_code(FILE *file, Tac *code, SymbolTable *programTable, SymbolTable *constantTable);
void code_strings(FILE *file, SymbolTable *table);
void code_main(FILE *file);
void code_tac(FILE *file, RegDesc *registers, Tac *current);
void code_begin_function(FILE *file, Symbol *function);
void code_end_function(FILE *file, RegDesc *registers);
void code_instruction(FILE *file, char *mnemonic, char *source, char *destination);
void code_comment(FILE *file, const char *format, ...);

//Specific actions
void code_binary(FILE *file, RegDesc *registers, char *op, Symbol *result, Symbol *operand1, Symbol *operand2);
void code_unary(FILE *file, RegDesc *registers, char *op, Symbol *result, Symbol *operand);
void code_compare(FILE *file, RegDesc *registers, char *op, Symbol *result, Symbol *operand1, Symbol *operand2);
void code_copy(FILE *file, RegDesc *registers, Symbol *result, Symbol *operand1);
void code_arg(FILE *file, RegDesc *registers, Symbol *result);
void code_call(FILE *file, RegDesc *registers, Symbol *function, Symbol *result);
void code_jump(FILE *file, RegDesc *registers, char *op,  Symbol *destination, Symbol *condition);
void code_return(FILE *file, RegDesc *registers, Symbol *result);

//Some gets
int get_size(Type *type);
char *get_location(FILE *file, RegDesc *registers, Symbol *symbol);

//Register spilling
void code_spill_reg(FILE *file, RegDesc *registers, int reg);
void code_spill_all(FILE *file, RegDesc *registers);
void code_flush_all(FILE *file, RegDesc *registers);

//Register loading
void code_load_reg(FILE *file, RegDesc *registers, int reg, Symbol *symbol);

//Helpers
char *make_memory_offset(Symbol *name, char *base);
char *make_integer(int i);
char *make_relative_address(int addr, char *base);
char *make_array_offset(int c, char* index, char *base);
char *make_low(char *reg);

#endif
