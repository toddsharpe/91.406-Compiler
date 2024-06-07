/**********************************************************
pascal.y

Initial Author: Todd Sharpe, February 2011

**************************************************************/

//Definitions

%{

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "symbol.h"
#include "tac.h"
#include "tacend.h"
#include "expression.h"
#include "type.h"
#include "stack.h"
#include "symboltable.h"
#include "utilities.h"
#include "codegen.h"
#include "symboltable.h"

/* External Functions */
extern Tac *declare_variable(Symbol *s);
extern void yyerror(char * error);
extern void type_identifiers(Tac *tac, Type *type);
extern int yylex (void);

//Scope
extern void activate_scope(int is_program);
extern SymbolTable *deactivate_scope();
extern SymbolTable *get_scope();

extern Type *make_variable_type(int code);
extern void type_variables(Tac *tac, Type *type);
extern void mark_parameters(Symbol *id, Tac *params);

/* External Vars */
extern Stack symbolStack;
extern Tac *program;
extern SymbolTable *constantTable;

%}

%union
{
  Type *type;
  Tac *tac;
  Symbol *symbol;
  Expression *expression;
  int op;
  Interval *interval;
}

%token AND ARRAY _BEGIN CASE CONST DIV DO DOWNTO ELSE END _FILE FOR FORWARD FUNCTION GOTO
%token IF IN LABEL MOD NIL NOT OF OR PACKED PROCEDURE PROGRAM RECORD REPEAT SET THEN TO TYPE UNTIL
%token WHILE WITH VAR ASSIGN NE GE LE DOTDOT PRINT

%token <symbol> ID
%token <symbol> NUM
%token <symbol> NATURAL
%token <symbol> STRING

//Types
%token <type> INTEGER
%token <type> REAL

//Tac
%type <tac> program
%type <tac> declarations

%type <tac> arguments
%type <tac> parameter_list
%type <tac> identifier_list

%type <tac> procedure_statement
%type <tac> compound_statement
%type <tac> optional_statements
%type <tac> statement_list
%type <tac> statement

%type <tac> subprogram_head
%type <tac> subprogram_declarations
%type <tac> subprogram_declaration

//Types
%type <type> type
%type <type> standard_type

//Symbols
%type <symbol> array_index

//Intervals
%type <interval> array_interval

//int - tac actions
%type <op> addop
%type <op> mulop
%type <op> relop
%type <op> assignop

//Expression
%type <expression> expression
%type <expression> simple_expression
%type <expression> factor
%type <expression> term
%type <expression> expression_list
%type <expression> variable

%%

//Rules
	
program: 
        PROGRAM { activate_scope(TRUE); } ID '(' identifier_list ')' ';'
	declarations
	subprogram_declarations
	compound_statement
	'.'
{
  //Type our program ID  
  $3->type = make_type(TYPE_PROGRAM);
 
  $3->symbols = deactivate_scope();
  //deactivate_scope();

  //Now type our identifier list
  type_identifiers($5, make_type(TYPE_PARAMETER));

  //offsets
  assign_offsets($3);
 
  //Set program
  //  program = join_tac(make_tac(TAC_BEGINPROGRAM, NULL, NULL, NULL), join_tac($5, join_tac($8, join_tac($9, join_tac($10, make_tac(TAC_ENDPROGRAM, NULL, NULL, NULL))))));

  //Define program tacs
  Tac *begin = make_tac(TAC_BEGINPROGRAM, $3, NULL, NULL);
  Tac *end = make_tac(TAC_ENDPROGRAM, NULL, NULL, NULL);

  program = join_tac($9, join_tac(begin, join_tac($5, join_tac($8, join_tac($10, end)))));

  $$ = program;
}
	;

identifier_list:
	ID
{
  $$ = declare_variable($1);
}
	| identifier_list ',' ID
{
  Tac *tac = declare_variable($3);
  tac->prev = $1;
  
  $$ = tac;
}
	;
				
declarations:
	declarations VAR identifier_list ':' type ';'
{
  //Assign the type
  Tac *tac = $3;
  while (tac != NULL)
    {
      tac->result->type= $5;
      tac = tac->prev;
    }
  
  $$ = join_tac($1, $3);
}
	|
{
  $$ = NULL;
}
	;
		
type: standard_type
{
  $$ = $1;
}
	| ARRAY '[' array_interval ']' OF standard_type
{
  Type *t = make_type($6->code);
  t->is_array = TRUE;
  t->intervals = $3;

  $$ = t;
}
	;

array_interval: array_index DOTDOT array_index
{
  $$ = make_interval($1->value.integer, $3->value.integer);
}
	;

array_index: NATURAL
{
  $$ = $1;
}
	| '-' NATURAL
{
  //Fix: 5-19-2011 See Expression_unary
  //Remove from constant table
  //symboltable_delete(constantTable, $2);
  
  Symbol *fold_result = make_symbol();
  fold_result->type = make_type(TYPE_NATURAL);
  fold_result->name = (char*)safe_malloc(sizeof(char) * 12);

  //Fix integer and name
  //$2->value.integer = $2->value.integer * -1;
  //sprintf($2->name, "%d", $2->value.integer);
  
  fold_result->value.integer = $2->value.integer * -1;
  sprintf(fold_result->name, "%d", fold_result->value.integer);

  //Put back in constant table
  symboltable_insert(constantTable, fold_result);

  //Return
  $$ = fold_result;
}
	;
	
expression_list:
	expression
{
  $$ = $1;
}
	| expression_list ',' expression
{
  //FIX 5-19-2011 - To correctly add a node to the list, we must run down the next pointers
  Expression *prev = $1;
  Expression *current = prev->next;
  while (current != NULL)
    {
      prev = current;
      current = current->next;
    }

  prev->next = $3;

  $$ = $1;
}
	;
	
expression:
	simple_expression
{
  $$ = $1;
}
	| simple_expression relop simple_expression
{
  debug("Binary Expression - Relop: %d Operand1: %s Operand2: %s", $2, $1->result->name, $3->result->name);
  $$ = expression_binary($2, $1, $3);
}
	;

simple_expression:
	term
{
  $$ = $1;
}
	| '-' term
{
  $$ = expression_unary(TAC_NEGATIVE, $2);
}
	| simple_expression addop term
{
 
  $$ = expression_binary($2, $1, $3);
}
	;
	
term:
	factor
{
  $$ = $1;
}
	| term mulop factor
{
 
  $$ = expression_binary($2, $1, $3);
}
	;
	
factor:
	ID
{
  if ($1->type->code == TYPE_PROCEDURE)
    die("%s is a Procedure, and can't be used in a factor/expression", $1);
  
  if ($1->type->code == TYPE_FUNCTION)
    $$ = expression_call($1, NULL);
  else
    $$ = make_expression(NULL, $1, NULL);
}
	| ID '[' expression ']'
{
  $$ = expression_array($1, $3);
}
	| ID '(' expression_list ')'
{
  $$ = expression_call($1, $3);
}
	| NUM
{
  $$ = make_expression(NULL, $1, NULL);
}
	| NATURAL
{
  $$ = make_expression(NULL, $1, NULL);
}
	| '(' expression ')'
{
  $$ = $2;
}
	| NOT factor
{
  $$ = expression_unary(TAC_NOT, $2);
}
	;
		
	
standard_type:
	INTEGER
{
  $$ = $1;
}
	| REAL
{
  $$ = $1;
}
	;

subprogram_declarations:
	subprogram_declarations subprogram_declaration ';'
{
  $$ = join_tac($1, $2);
}
	|
{
  $$ = NULL;
}
	;

subprogram_declaration:
	subprogram_head declarations subprogram_declarations compound_statement
{
  Tac *last = last_tac($1);
  Symbol *function = last->result;
  SymbolTable *table = deactivate_scope();
  function->symbols = table;

  Tac *end = make_tac(TAC_ENDFUNCTION, NULL, NULL, NULL);

  //Assign offsets
  assign_offsets(function);

  $$ = join_tac($1, join_tac($2, join_tac($4, join_tac(end, $3))));
}
	;
						
/* In both the following rules, we create the scope after the ID, so the ID is in the symbol table of the parent */
subprogram_head:
	FUNCTION ID { activate_scope(FALSE); } arguments ':' standard_type ';'
{
  $2->type = make_type(TYPE_FUNCTION);
  mark_parameters($2, $4);

  //Mark symbols as parameters
  Tac *current = $4;
  while (current != NULL)
    {
      current->result->is_parameter = TRUE;
      current = current->prev;
    }

  //Add ID to this functions symbol table
  //Symbol *symb = make_symbol();
  //symb->name = $2->name;
  //symb->type = $6;
  //symboltable_insert(get_scope(), symb);

  //Declare function
  $$ = tac_procedure_start($2, $4);
}
	| PROCEDURE ID { activate_scope(FALSE); } arguments ';'
{
  $2->type = make_type(TYPE_PROCEDURE);
  mark_parameters($2, $4);
  
  $$ = tac_procedure_start($2, $4);
}
	;
						
arguments:
	'(' parameter_list ')'
{
  $$ = $2;
}
	|
{
  $$ = NULL;
}
	;
			
parameter_list:
	identifier_list ':' type
{
  type_identifiers($1, $3);
  $$ = $1;
}
	| parameter_list ';' identifier_list ':' type
{
  type_identifiers($3, $5);

  //Join the tacs
  $3->prev = $1;

  $$ = $3;
}
	;
				
compound_statement:
	_BEGIN
	optional_statements
	END
{
  $$ = $2;
}
	;
					
optional_statements:
	statement_list
{
  $$ = $1;
}
	|
{
  $$ = NULL;
}
	;
					
statement_list:
	statement
{
  $$ = $1;
}
	| statement_list ';' statement
{
  $$ = join_tac($1, $3);
}
	;

statement:
	variable assignop expression
{
  if ($1->result->type->code == TYPE_FUNCTION)
    {
      //This is pascal syntax for returning a value from a function
      Tac *ret = make_tac(TAC_RETURN, $3->result, NULL, NULL);
      ret->prev = $3->tac;
      $$ = ret;
    }
  else
    {
      //Join code needed to access array with the expression code, executing the array index code last
      Tac *joined = join_tac($3->tac, $1->tac);

      //Update the expression with a pointer to our bolted together code
      $3->tac = joined;
      $$ = tac_assign($1->result, $3);
    }

  //Free
  free($1);
}
	| procedure_statement
{
  $$ = $1;
}
	| compound_statement
{
  $$ = $1;
}
	| IF expression THEN statement ELSE statement
{
  $$ = tac_if_else($2, $4, $6);
}
	| WHILE expression DO statement
{
  $$ = tac_while($2, $4);
}
	| PRINT expression
{
  debug("PRINT expression");
  Symbol *print = symboltable_recurse(get_scope(), "print");
  debug("print %d", print);
  $$ = expression_call(print, $2)->tac;
} 
	;

variable:
	ID
{
  //$$ = $1;
  $$ = make_expression(NULL, $1, NULL);
}
	| ID '[' expression ']'
{
  $$ = expression_array($1, $3);
//die("Arrays not supported yet");
}
    ;
			
procedure_statement:
	ID
{ 
  $$ = expression_call($1, NULL)->tac;
}
	| ID '(' expression_list ')'
{
  debug("Expression call %s", $1->name);
  dump_expressions($3);
  $$ = expression_call($1, $3)->tac;
}
	;

addop:
	'+'
{
  $$ = TAC_ADD;
}
	| '-'
{
  $$ = TAC_SUBTRACT;
}
	| OR 
{
  $$ = TAC_OR;
}
	;

mulop: 	
	'*'
{
  $$ = TAC_MULTIPLY;
}
	| DIV
{
  $$ = TAC_DIVIDE;
}
	| '/'
{
  $$ = TAC_DIVIDE;//TODO: this should be for reals
}
	| MOD
{
  $$ = TAC_MOD;
}
	| AND
{
  $$ = TAC_AND;
}
	;

relop: 	
	'='
{
  $$ = TAC_EQUAL;
}
	| NE
{
  $$ = TAC_NOTEQUAL;
}
	| LE
{
$$ = TAC_LTE;
}
	| GE
{
  $$ = TAC_GTE;
}
	| '<'
{
  $$ = TAC_LT;
}
	| '>'
{
  $$ = TAC_GT;
}
	;

assignop:
	ASSIGN
{
  
}
	;
		
%%

//Subroutines
