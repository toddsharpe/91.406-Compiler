#ifndef main_h
#define main_h

//Give C the power of booleans!
#define TRUE 1
#define FALSE 0

//Types - for symbols, todo - rename SYMBOL_
#define TYPE_UNDEFINED 0
#define TYPE_VARIABLE 1//generic type, before it is typed
#define TYPE_FUNCTION 2
#define TYPE_STRING 3
#define TYPE_INTEGER 4
#define TYPE_REAL 5
#define TYPE_PROGRAM 6
#define TYPE_PARAMETER 7 //Used as the generic input, output parameters to Program
#define TYPE_PROCEDURE 8
#define TYPE_LABEL 9

//Value types
#define TYPE_NUM 10
#define TYPE_NATURAL 11

//Globals
#define EndOfString 0

//TAC Operations
#define TAC_UNDEFINED 0
#define TAC_ADD 1
#define TAC_SUBTRACT 2
#define TAC_MULTIPLY 3
#define TAC_DIVIDE 4
#define TAC_NEGATIVE 5//unary minus
#define TAC_COPY 6
#define TAC_GOTO 7
#define TAC_IFZ 8
#define TAC_IFNZ 9
#define TAC_ARG 10
#define TAC_CALL 11
#define TAC_RETURN 12
#define TAC_MOD 13
#define TAC_NOP 14

//Logic
#define TAC_AND 20
#define TAC_OR 21
#define TAC_NOT 22

//Relationals
#define TAC_GT 30
#define TAC_LT 31
#define TAC_GTE 32
#define TAC_LTE 33
#define TAC_EQUAL 34
#define TAC_NOTEQUAL 35

//High-order TACs
#define TAC_ARRAY 40//This tac will need to be broken down in assembly

//TAC Pseudo-Operations
#define TAC_VARIABLE 100
#define TAC_LABEL 101 //Branch targets
#define TAC_BEGINFUNCTION 102
#define TAC_ENDFUNCTION 103
#define TAC_BEGINPROGRAM 104
#define TAC_ENDPROGRAM 105

//Symbol table
#define HASHSIZE 64

//Define our registers in x86 land
#define REG_EAX 0
#define REG_EBX 1
#define REG_ECX 2
#define REG_EDX 3
//#define REG_ESI 4
//#define REG_EDI 5
//#define REG_EBP 6
//#define REG_ESP 7 - lets ignore these two, we shouldn't touch them
#define REG_MAX 4//We have 6 registers

#endif
