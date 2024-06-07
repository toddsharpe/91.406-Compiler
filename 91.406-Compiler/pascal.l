/**********************************************************
pascal.l

Initial Author: Jim Canning, January 1999
Modified By: Todd Sharpe, February 2011

**************************************************************/

/* This section is directly copied to the output */
%{

#include "type.h"
#include "tac.h"
#include "symbol.h"
#include "expression.h"
#include "y.tab.h"
#include "main.h"
#include <stdio.h>
#include "frontend.h"

/* Externals */
extern int blockDepth;
extern int debug_mode;
extern void make_variable_type(int code);

/* #define token(x) x */

int token(int x)
{
if ((1 == 0) && (debug_mode == TRUE))
if (x < 255)
{
char c = (char)x;
printf("Character found: %c\n", c);
}
else
{
printf("Token Found: %d\n", x);
}
	return x;
}

%}

/* Regular expressions */
alpha [a-zA-Z_]
alphanum [a-zA-Z_0-9]
comment "{"[^}]*"}"
exponent e([+-])?[0-9]+
string \'([^'\n]|\'\')+\'
unsignedint [0-9]+
whitespace [ \t\n]+

%%

":=" return token(ASSIGN);
">=" return token(GE);
"<=" return token(LE);
"<>" return token(NE);
".." return token(DOTDOT);

"AND" return token(AND);
"ARRAY" return token(ARRAY);
"BEGIN" { blockDepth++; return token(_BEGIN); }
"CASE" return token(CASE);
"CONST" return token(CONST);
"DIV" return token(DIV);
"DO" return token(DO);
"DOWNTO" return token(DOWNTO);
"ELSE" return token(ELSE);
"END" { blockDepth--; return token(END); }
"FILE" return token(_FILE);
"FOR" return token(FOR);
"FORWARD" return token(FORWARD);
"FUNCTION" return token(FUNCTION);
"GOTO" return token(GOTO);
"IF" return token(IF);
"IN" return token(IN);
"LABEL" return token(LABEL);
"MOD" return token(MOD);
"NIL" return token(NIL);
"NOT" return token(NOT);
"OF" return token(OF);
"OR" return token(OR);
"PACKED" return token(PACKED);
"PROCEDURE" return token(PROCEDURE);
"PROGRAM" return token(PROGRAM);
"RECORD" return token(RECORD);
"REPEAT" return token(REPEAT);
"SET" return token(SET);
"THEN" return token(THEN);
"TO" return token(TO);
"TYPE" return token(TYPE);
"UNTIL" return token(UNTIL);
"VAR" return token(VAR);
"WHILE" return token(WHILE);
"WITH" return token(WITH);
"INTEGER" { make_variable_type(TYPE_INTEGER); return token(INTEGER); }
"REAL" { make_variable_type(TYPE_REAL); return token(REAL);}
"PRINT" return token(PRINT);

{alpha}{alphanum}* { make_name(TYPE_VARIABLE); return token(ID); }
{unsignedint} { make_name(TYPE_NATURAL); return token(NATURAL); }
{unsignedint}\.{unsignedint}({exponent})? { make_name(TYPE_NUM); return token(NUM); }
{unsignedint}{exponent}? { make_name(TYPE_NUM); return token(NUM); }
{string} return token(STRING);
{whitespace} ;
{comment}+ ;
. return token(yytext[0]);

%%
