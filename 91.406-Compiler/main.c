#include "type.h"
#include "symbol.h"
#include "tac.h"
#include "expression.h"
#include <stdio.h>
#include "main.h"
#include "y.tab.h"
#include "symboltable.h"
#include "codegen.h"
#include "utilities.h"

//Function prototypes
void initialize(void);
void yyerror(char * error);
int yywrap(void);
void inject_string(char *s);

//External variables
extern char yytext[];
extern int yyleng;
extern YYSTYPE yyval;
extern int yydebug;

//Debug
int debug_mode = FALSE;
int comment_mode = FALSE;

//Variables
SymbolTable *mainTable;
SymbolTable *constantTable;
Stack *symbolStack;
int blockDepth = 0;
Tac *program;
Symbol *symbol_one;//A constant reference to a symbol of value one

int main(int argc, char * argv[])
{
  yydebug = 0;
  
  printf("Initializing\n");
  initialize();
  printf("\n");

  printf("Parsing...\n");
  if (! yyparse())
    printf("Parsed without errors\n");
  else
    printf("Errors in parsing\n");
  printf("\n");

  inject_string("%d\\n");

  //printf("Dumping Program Symbol Table at Nested %d\n", mainTable->nested);
  //symboltable_dump(mainTable); 
  //printf("\n");

  printf("Dumping Constant Table\n");
  symboltable_dump(constantTable);
  printf("\n");

  printf("Dumping reversed TAC List\n");
  program = reverse_tac(program);
//tac_dump(yylval.tac); - For some reason, yyval.tac isn't the tac I told program to reduce to, so now I do it myself
  tac_dump(program);
  printf("\n");

  //Make our constant one
  symbol_one = make_symbol();
  symbol_one->value.integer = 1;
  symbol_one->type = make_type(TYPE_NATURAL);
  
  char *name = (char*)safe_malloc(sizeof(char) * 4);
  sprintf(name, "%d", symbol_one->value.integer);
  symbol_one->name = name;

  char *file_name = "code.s";

  //Open handle
  FILE *file = fopen(file_name, "w");
  if (file == NULL)
    die("Couldn't open %s", file_name);

  //Generate code
  generate_code(file, program, mainTable, constantTable);

  //Close file
  fclose(file);
}

void inject_string(char *string)
{
  Symbol *inject = make_symbol();
  inject->value.string = string;
  inject->name = string;
  inject->type = make_type(TYPE_STRING);
  symboltable_insert(constantTable, inject);
}

void initialize(void)
{
  //Set symbol stack
  symbolStack = make_stack();

  //Set constant table
  constantTable = make_symboltable();
}

void yyerror(char * error)
{
  printf("Error: %s\n", error);
}

int yywrap(void)
{
  return 1;
}
