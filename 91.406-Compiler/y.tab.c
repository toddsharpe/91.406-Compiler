#ifndef lint
static char const 
yyrcsid[] = "$FreeBSD: src/usr.bin/yacc/skeleton.c,v 1.28 2000/01/17 02:04:06 bde Exp $";
#endif
#include <stdlib.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
static int yygrowstack();
#define YYPREFIX "yy"
#line 11 "pascal.y"

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

/*Scope*/
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

#line 45 "pascal.y"
typedef union
{
  Type *type;
  Tac *tac;
  Symbol *symbol;
  Expression *expression;
  int op;
  Interval *interval;
} YYSTYPE;
#line 60 "y.tab.c"
#define YYERRCODE 256
#define AND 257
#define ARRAY 258
#define _BEGIN 259
#define CASE 260
#define CONST 261
#define DIV 262
#define DO 263
#define DOWNTO 264
#define ELSE 265
#define END 266
#define _FILE 267
#define FOR 268
#define FORWARD 269
#define FUNCTION 270
#define GOTO 271
#define IF 272
#define IN 273
#define LABEL 274
#define MOD 275
#define NIL 276
#define NOT 277
#define OF 278
#define OR 279
#define PACKED 280
#define PROCEDURE 281
#define PROGRAM 282
#define RECORD 283
#define REPEAT 284
#define SET 285
#define THEN 286
#define TO 287
#define TYPE 288
#define UNTIL 289
#define WHILE 290
#define WITH 291
#define VAR 292
#define ASSIGN 293
#define NE 294
#define GE 295
#define LE 296
#define DOTDOT 297
#define PRINT 298
#define ID 299
#define NUM 300
#define NATURAL 301
#define STRING 302
#define INTEGER 303
#define REAL 304
const short yylhs[] = {                                        -1,
   27,    0,    4,    4,    1,    1,   13,   13,   16,   15,
   15,   25,   25,   21,   21,   22,   22,   22,   24,   24,
   23,   23,   23,   23,   23,   23,   23,   14,   14,   11,
   11,   12,   28,   10,   29,   10,    2,    2,    3,    3,
    6,    7,    7,    8,    8,    9,    9,    9,    9,    9,
    9,   26,   26,    5,    5,   17,   17,   17,   18,   18,
   18,   18,   18,   19,   19,   19,   19,   19,   19,   20,
};
const short yylen[] = {                                         2,
    0,   11,    1,    3,    6,    0,    1,    6,    3,    1,
    2,    1,    3,    1,    3,    1,    2,    3,    1,    3,
    1,    4,    4,    1,    1,    3,    2,    1,    1,    3,
    0,    4,    0,    7,    0,    5,    3,    0,    3,    5,
    3,    1,    0,    1,    3,    3,    1,    1,    6,    4,
    2,    1,    4,    1,    4,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
};
const short yydefred[] = {                                      0,
    1,    0,    0,    0,    0,    3,    0,    0,    0,    6,
    4,    0,    0,    0,    0,    0,    0,    0,    0,    6,
    0,    0,    0,    0,    0,    0,   47,   48,    0,    0,
   44,    0,   33,   35,    2,    0,   30,    0,   28,   29,
    0,    7,    0,    0,   24,   25,    0,    0,    0,    0,
   19,    0,    0,   51,    0,    0,   41,    0,   70,    0,
    0,    0,    0,    0,    5,   27,    0,    0,    0,    0,
    0,   58,   65,   67,   66,   57,   56,   64,   68,   69,
    0,    0,   63,   60,   62,   59,   61,    0,    0,   12,
    0,    0,   45,   46,    0,    0,    0,   32,   10,    0,
    0,    0,    0,    0,   26,    0,    0,    0,   20,   50,
   55,    0,   53,    0,    0,    0,   36,   11,    0,    0,
   23,   22,    0,   13,   37,    0,    0,    0,    9,    0,
   49,    0,   39,   34,    8,    0,   40,
};
const short yydgoto[] = {                                       2,
   12,   96,  114,    7,   27,   28,   29,   30,   31,   20,
   14,   21,   41,   42,  101,  102,   81,   88,   82,   60,
   90,   50,   51,   52,   91,   32,    3,   61,   62,
};
const short yysindex[] = {                                   -270,
    0,    0, -284,  -23, -272,    0,   60,  -15, -267,    0,
    0, -244, -272, -171,  -28, -177, -243, -228,   79,    0,
   67, -250,  -40,  -40,  -40,  -30,    0,    0, -160,   69,
    0, -164,    0,    0,    0, -244,    0,   39,    0,    0,
   73,    0,  -37,  -26,    0,    0,  -40,  -37, -153,    2,
    0,  -36, -129,    0,  -40,  -40,    0, -177,    0,  -40,
   95,   95, -171,  -44,    0,    0,  -40,  -40,   96,  -36,
 -177,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -37,  -40,    0,    0,    0,    0,    0,  -37, -177,    0,
   75,   43,    0,    0, -272,   80,   81,    0,    0, -162,
 -156,   50,   83,   51,    0, -120,  -36,  -41,    0,    0,
    0,  -40,    0,  -22,   47, -207,    0,    0,  -44, -132,
    0,    0, -177,    0,    0, -272, -250,   88,    0, -207,
    0,   54,    0,    0,    0, -250,    0,
};
const short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -167,    0,    0,    0, -118,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -50,    0,    0,    0, -117,
    0,    0,    0,    0,    0, -167,    0,    0,    0,    0,
    0,    0,    0,  -21,    0,    0,    0,    0,    0,  -16,
    0,  -10,    0,    0,    0,    0,    0,    0,    0,    0,
   92,   93,    0,    0,    0,    0,    0,    0,    0,   14,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   25,   49,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,
};
const short yygindex[] = {                                      0,
  131,   91,    0,   -6,    0,    4,    0,    0,  -29,    0,
  118,    0,  -27,    1,   36,    0,    0,    0,    0,    0,
   55,   74,   -7,  -35,   90,    0,    0,    0,    0,
};
#define YYTABLESIZE 335
const short yytable[] = {                                      47,
  100,   77,   47,   76,   48,   86,   15,   38,   54,   55,
   87,    1,   70,   67,    4,    9,    5,   19,  125,   21,
   21,   21,   21,   21,   14,   21,    6,   14,   93,   22,
   16,   11,   16,   16,   16,   66,  126,   21,   21,   21,
   21,  106,   14,   10,   77,  107,   76,   13,   16,   16,
   16,   16,   39,   40,   17,   33,   17,   17,   17,  110,
   56,   79,   78,   80,   68,   18,   98,   18,   18,   18,
   34,   21,   17,   17,   17,   17,   14,   49,   53,   54,
  109,   16,   16,   18,   18,   18,   18,   16,  115,   15,
    9,   31,   15,  131,   23,   39,   40,    9,   17,  133,
    8,   69,   31,    9,  127,   57,   17,   15,  137,   18,
   92,  136,   24,   31,   94,  111,  128,   18,  112,  132,
   25,   26,  104,  121,   35,   37,  112,   58,   59,   64,
  135,   65,   71,   89,   95,  113,  105,  116,  118,  117,
  119,   15,  120,  122,  123,  130,  134,   43,   42,   38,
   36,   38,   97,   63,  129,  108,  103,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  124,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   54,   54,    0,    0,    0,    0,
   83,    0,    0,    0,    0,   84,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   21,   43,   72,   85,   43,
   21,   21,   52,   21,   21,    0,   14,    0,   14,   14,
    0,    0,   16,   21,   16,   16,   99,   21,   44,   45,
   46,   44,   45,   46,   21,    0,    0,    0,   16,   14,
    0,    0,   21,   21,   21,   16,   17,    0,   17,   17,
   72,    0,    0,   16,   16,   16,    0,   18,    0,   18,
   18,    0,   17,    0,    0,   73,   74,   75,    0,   17,
    0,    0,    0,   18,    0,    0,    0,   17,   17,   17,
   18,   15,    0,   15,   15,    0,    0,    0,   18,   18,
   18,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   15,
};
const short yycheck[] = {                                      40,
   45,   43,   40,   45,   45,   42,   13,  258,   59,   40,
   47,  282,   48,   40,  299,   44,   40,   14,   41,   41,
   42,   43,   44,   45,   41,   47,  299,   44,   58,   58,
   41,  299,   43,   44,   45,   43,   59,   59,   60,   61,
   62,   71,   59,   59,   43,   81,   45,  292,   59,   60,
   61,   62,  303,  304,   41,  299,   43,   44,   45,   89,
   91,   60,   61,   62,   91,   41,   63,   43,   44,   45,
  299,   93,   59,   60,   61,   62,   93,   23,   24,   25,
   88,  259,   93,   59,   60,   61,   62,  259,   95,   41,
   44,  259,   44,  123,  272,  303,  304,   44,  270,  127,
   41,   47,  270,   44,   58,  266,   93,   59,  136,  281,
   56,   58,  290,  281,   60,   41,  116,   93,   44,  126,
  298,  299,   68,   41,   46,   59,   44,   59,  293,   91,
  130,   59,  286,  263,   40,   93,   41,   58,  301,   59,
  297,   93,   93,   93,  265,  278,   59,  266,  266,   58,
   20,   59,   62,   36,  119,   82,   67,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  112,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  265,  266,   -1,   -1,   -1,   -1,
  257,   -1,   -1,   -1,   -1,  262,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  257,  277,  279,  275,  277,
  262,  263,  293,  265,  266,   -1,  263,   -1,  265,  266,
   -1,   -1,  263,  275,  265,  266,  301,  279,  299,  300,
  301,  299,  300,  301,  286,   -1,   -1,   -1,  279,  286,
   -1,   -1,  294,  295,  296,  286,  263,   -1,  265,  266,
  279,   -1,   -1,  294,  295,  296,   -1,  263,   -1,  265,
  266,   -1,  279,   -1,   -1,  294,  295,  296,   -1,  286,
   -1,   -1,   -1,  279,   -1,   -1,   -1,  294,  295,  296,
  286,  263,   -1,  265,  266,   -1,   -1,   -1,  294,  295,
  296,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  286,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 304
#if YYDEBUG
const char * const yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'","'*'","'+'","','","'-'","'.'","'/'",0,0,0,0,0,0,0,0,0,0,
"':'","';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,"AND","ARRAY","_BEGIN","CASE","CONST","DIV","DO",
"DOWNTO","ELSE","END","_FILE","FOR","FORWARD","FUNCTION","GOTO","IF","IN",
"LABEL","MOD","NIL","NOT","OF","OR","PACKED","PROCEDURE","PROGRAM","RECORD",
"REPEAT","SET","THEN","TO","TYPE","UNTIL","WHILE","WITH","VAR","ASSIGN","NE",
"GE","LE","DOTDOT","PRINT","ID","NUM","NATURAL","STRING","INTEGER","REAL",
};
const char * const yyrule[] = {
"$accept : program",
"$$1 :",
"program : PROGRAM $$1 ID '(' identifier_list ')' ';' declarations subprogram_declarations compound_statement '.'",
"identifier_list : ID",
"identifier_list : identifier_list ',' ID",
"declarations : declarations VAR identifier_list ':' type ';'",
"declarations :",
"type : standard_type",
"type : ARRAY '[' array_interval ']' OF standard_type",
"array_interval : array_index DOTDOT array_index",
"array_index : NATURAL",
"array_index : '-' NATURAL",
"expression_list : expression",
"expression_list : expression_list ',' expression",
"expression : simple_expression",
"expression : simple_expression relop simple_expression",
"simple_expression : term",
"simple_expression : '-' term",
"simple_expression : simple_expression addop term",
"term : factor",
"term : term mulop factor",
"factor : ID",
"factor : ID '[' expression ']'",
"factor : ID '(' expression_list ')'",
"factor : NUM",
"factor : NATURAL",
"factor : '(' expression ')'",
"factor : NOT factor",
"standard_type : INTEGER",
"standard_type : REAL",
"subprogram_declarations : subprogram_declarations subprogram_declaration ';'",
"subprogram_declarations :",
"subprogram_declaration : subprogram_head declarations subprogram_declarations compound_statement",
"$$2 :",
"subprogram_head : FUNCTION ID $$2 arguments ':' standard_type ';'",
"$$3 :",
"subprogram_head : PROCEDURE ID $$3 arguments ';'",
"arguments : '(' parameter_list ')'",
"arguments :",
"parameter_list : identifier_list ':' type",
"parameter_list : parameter_list ';' identifier_list ':' type",
"compound_statement : _BEGIN optional_statements END",
"optional_statements : statement_list",
"optional_statements :",
"statement_list : statement",
"statement_list : statement_list ';' statement",
"statement : variable assignop expression",
"statement : procedure_statement",
"statement : compound_statement",
"statement : IF expression THEN statement ELSE statement",
"statement : WHILE expression DO statement",
"statement : PRINT expression",
"variable : ID",
"variable : ID '[' expression ']'",
"procedure_statement : ID",
"procedure_statement : ID '(' expression_list ')'",
"addop : '+'",
"addop : '-'",
"addop : OR",
"mulop : '*'",
"mulop : DIV",
"mulop : '/'",
"mulop : MOD",
"mulop : AND",
"relop : '='",
"relop : NE",
"relop : LE",
"relop : GE",
"relop : '<'",
"relop : '>'",
"assignop : ASSIGN",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
int yystacksize;
#line 605 "pascal.y"

//Subroutines
#line 383 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack()
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    i = yyssp - yyss;
    newss = yyss ? (short *)realloc(yyss, newsize * sizeof *newss) :
      (short *)malloc(newsize * sizeof *newss);
    if (newss == NULL)
        return -1;
    yyss = newss;
    yyssp = newss + i;
    newvs = yyvs ? (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs) :
      (YYSTYPE *)malloc(newsize * sizeof *newvs);
    if (newvs == NULL)
        return -1;
    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab

#ifndef YYPARSE_PARAM
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG void
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif	/* ANSI-C/C++ */
#else	/* YYPARSE_PARAM */
#ifndef YYPARSE_PARAM_TYPE
#define YYPARSE_PARAM_TYPE void *
#endif
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG YYPARSE_PARAM_TYPE YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL YYPARSE_PARAM_TYPE YYPARSE_PARAM;
#endif	/* ANSI-C/C++ */
#endif	/* ! YYPARSE_PARAM */

int
yyparse (YYPARSE_PARAM_ARG)
    YYPARSE_PARAM_DECL
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate])) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#if defined(lint) || defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 115 "pascal.y"
{ activate_scope(TRUE); }
break;
case 2:
#line 120 "pascal.y"
{
  /*Type our program ID  */
  yyvsp[-8].symbol->type = make_type(TYPE_PROGRAM);
 
  yyvsp[-8].symbol->symbols = deactivate_scope();
  /*deactivate_scope();*/

  /*Now type our identifier list*/
  type_identifiers(yyvsp[-6].tac, make_type(TYPE_PARAMETER));

  /*offsets*/
  assign_offsets(yyvsp[-8].symbol);
 
  /*Set program*/
  /*  program = join_tac(make_tac(TAC_BEGINPROGRAM, NULL, NULL, NULL), join_tac($5, join_tac($8, join_tac($9, join_tac($10, make_tac(TAC_ENDPROGRAM, NULL, NULL, NULL))))));*/

  /*Define program tacs*/
  Tac *begin = make_tac(TAC_BEGINPROGRAM, yyvsp[-8].symbol, NULL, NULL);
  Tac *end = make_tac(TAC_ENDPROGRAM, NULL, NULL, NULL);

  program = join_tac(yyvsp[-2].tac, join_tac(begin, join_tac(yyvsp[-6].tac, join_tac(yyvsp[-3].tac, join_tac(yyvsp[-1].tac, end)))));

  yyval.tac = program;
}
break;
case 3:
#line 148 "pascal.y"
{
  yyval.tac = declare_variable(yyvsp[0].symbol);
}
break;
case 4:
#line 152 "pascal.y"
{
  Tac *tac = declare_variable(yyvsp[0].symbol);
  tac->prev = yyvsp[-2].tac;
  
  yyval.tac = tac;
}
break;
case 5:
#line 162 "pascal.y"
{
  /*Assign the type*/
  Tac *tac = yyvsp[-3].tac;
  while (tac != NULL)
    {
      tac->result->type= yyvsp[-1].type;
      tac = tac->prev;
    }
  
  yyval.tac = join_tac(yyvsp[-5].tac, yyvsp[-3].tac);
}
break;
case 6:
#line 174 "pascal.y"
{
  yyval.tac = NULL;
}
break;
case 7:
#line 180 "pascal.y"
{
  yyval.type = yyvsp[0].type;
}
break;
case 8:
#line 184 "pascal.y"
{
  Type *t = make_type(yyvsp[0].type->code);
  t->is_array = TRUE;
  t->intervals = yyvsp[-3].interval;

  yyval.type = t;
}
break;
case 9:
#line 194 "pascal.y"
{
  yyval.interval = make_interval(yyvsp[-2].symbol->value.integer, yyvsp[0].symbol->value.integer);
}
break;
case 10:
#line 200 "pascal.y"
{
  yyval.symbol = yyvsp[0].symbol;
}
break;
case 11:
#line 204 "pascal.y"
{
  /*Fix: 5-19-2011 See Expression_unary*/
  /*Remove from constant table*/
  /*symboltable_delete(constantTable, $2);*/
  
  Symbol *fold_result = make_symbol();
  fold_result->type = make_type(TYPE_NATURAL);
  fold_result->name = (char*)safe_malloc(sizeof(char) * 12);

  /*Fix integer and name*/
  /*$2->value.integer = $2->value.integer * -1;*/
  /*sprintf($2->name, "%d", $2->value.integer);*/
  
  fold_result->value.integer = yyvsp[0].symbol->value.integer * -1;
  sprintf(fold_result->name, "%d", fold_result->value.integer);

  /*Put back in constant table*/
  symboltable_insert(constantTable, fold_result);

  /*Return*/
  yyval.symbol = fold_result;
}
break;
case 12:
#line 230 "pascal.y"
{
  yyval.expression = yyvsp[0].expression;
}
break;
case 13:
#line 234 "pascal.y"
{
  Expression *prev = yyvsp[-2].expression;
  Expression *current = prev->next;
  while (current != NULL)
    {
      prev = current;
      current = current->next;
    }

  prev->next = yyvsp[0].expression;

  yyval.expression = yyvsp[-2].expression;
}
break;
case 14:
#line 251 "pascal.y"
{
  yyval.expression = yyvsp[0].expression;
}
break;
case 15:
#line 255 "pascal.y"
{
  debug("Binary Expression - Relop: %d Operand1: %s Operand2: %s", yyvsp[-1].op, yyvsp[-2].expression->result->name, yyvsp[0].expression->result->name);
  yyval.expression = expression_binary(yyvsp[-1].op, yyvsp[-2].expression, yyvsp[0].expression);
}
break;
case 16:
#line 263 "pascal.y"
{
  yyval.expression = yyvsp[0].expression;
}
break;
case 17:
#line 267 "pascal.y"
{
  yyval.expression = expression_unary(TAC_NEGATIVE, yyvsp[0].expression);
}
break;
case 18:
#line 271 "pascal.y"
{
 
  yyval.expression = expression_binary(yyvsp[-1].op, yyvsp[-2].expression, yyvsp[0].expression);
}
break;
case 19:
#line 279 "pascal.y"
{
  yyval.expression = yyvsp[0].expression;
}
break;
case 20:
#line 283 "pascal.y"
{
 
  yyval.expression = expression_binary(yyvsp[-1].op, yyvsp[-2].expression, yyvsp[0].expression);
}
break;
case 21:
#line 291 "pascal.y"
{
  if (yyvsp[0].symbol->type->code == TYPE_PROCEDURE)
    die("%s is a Procedure, and can't be used in a factor/expression", yyvsp[0].symbol);
  
  if (yyvsp[0].symbol->type->code == TYPE_FUNCTION)
    yyval.expression = expression_call(yyvsp[0].symbol, NULL);
  else
    yyval.expression = make_expression(NULL, yyvsp[0].symbol, NULL);
}
break;
case 22:
#line 301 "pascal.y"
{
  yyval.expression = expression_array(yyvsp[-3].symbol, yyvsp[-1].expression);
}
break;
case 23:
#line 305 "pascal.y"
{
  yyval.expression = expression_call(yyvsp[-3].symbol, yyvsp[-1].expression);
}
break;
case 24:
#line 309 "pascal.y"
{
  yyval.expression = make_expression(NULL, yyvsp[0].symbol, NULL);
}
break;
case 25:
#line 313 "pascal.y"
{
  yyval.expression = make_expression(NULL, yyvsp[0].symbol, NULL);
}
break;
case 26:
#line 317 "pascal.y"
{
  yyval.expression = yyvsp[-1].expression;
}
break;
case 27:
#line 321 "pascal.y"
{
  yyval.expression = expression_unary(TAC_NOT, yyvsp[0].expression);
}
break;
case 28:
#line 329 "pascal.y"
{
  yyval.type = yyvsp[0].type;
}
break;
case 29:
#line 333 "pascal.y"
{
  yyval.type = yyvsp[0].type;
}
break;
case 30:
#line 340 "pascal.y"
{
  yyval.tac = join_tac(yyvsp[-2].tac, yyvsp[-1].tac);
}
break;
case 31:
#line 344 "pascal.y"
{
  yyval.tac = NULL;
}
break;
case 32:
#line 351 "pascal.y"
{
  Tac *last = last_tac(yyvsp[-3].tac);
  Symbol *function = last->result;
  SymbolTable *table = deactivate_scope();
  function->symbols = table;

  Tac *end = make_tac(TAC_ENDFUNCTION, NULL, NULL, NULL);

  /*Assign offsets*/
  assign_offsets(function);

  yyval.tac = join_tac(yyvsp[-3].tac, join_tac(yyvsp[-2].tac, join_tac(yyvsp[0].tac, join_tac(end, yyvsp[-1].tac))));
}
break;
case 33:
#line 368 "pascal.y"
{ activate_scope(FALSE); }
break;
case 34:
#line 369 "pascal.y"
{
  yyvsp[-5].symbol->type = make_type(TYPE_FUNCTION);
  mark_parameters(yyvsp[-5].symbol, yyvsp[-3].tac);

  /*Mark symbols as parameters*/
  Tac *current = yyvsp[-3].tac;
  while (current != NULL)
    {
      current->result->is_parameter = TRUE;
      current = current->prev;
    }

  /*Add ID to this functions symbol table*/
  /*Symbol *symb = make_symbol();*/
  /*symb->name = $2->name;*/
  /*symb->type = $6;*/
  /*symboltable_insert(get_scope(), symb);*/

  /*Declare function*/
  yyval.tac = tac_procedure_start(yyvsp[-5].symbol, yyvsp[-3].tac);
}
break;
case 35:
#line 390 "pascal.y"
{ activate_scope(FALSE); }
break;
case 36:
#line 391 "pascal.y"
{
  yyvsp[-3].symbol->type = make_type(TYPE_PROCEDURE);
  mark_parameters(yyvsp[-3].symbol, yyvsp[-1].tac);
  
  yyval.tac = tac_procedure_start(yyvsp[-3].symbol, yyvsp[-1].tac);
}
break;
case 37:
#line 401 "pascal.y"
{
  yyval.tac = yyvsp[-1].tac;
}
break;
case 38:
#line 405 "pascal.y"
{
  yyval.tac = NULL;
}
break;
case 39:
#line 412 "pascal.y"
{
  type_identifiers(yyvsp[-2].tac, yyvsp[0].type);
  yyval.tac = yyvsp[-2].tac;
}
break;
case 40:
#line 417 "pascal.y"
{
  type_identifiers(yyvsp[-2].tac, yyvsp[0].type);

  /*Join the tacs*/
  yyvsp[-2].tac->prev = yyvsp[-4].tac;

  yyval.tac = yyvsp[-2].tac;
}
break;
case 41:
#line 431 "pascal.y"
{
  yyval.tac = yyvsp[-1].tac;
}
break;
case 42:
#line 438 "pascal.y"
{
  yyval.tac = yyvsp[0].tac;
}
break;
case 43:
#line 442 "pascal.y"
{
  yyval.tac = NULL;
}
break;
case 44:
#line 449 "pascal.y"
{
  yyval.tac = yyvsp[0].tac;
}
break;
case 45:
#line 453 "pascal.y"
{
  yyval.tac = join_tac(yyvsp[-2].tac, yyvsp[0].tac);
}
break;
case 46:
#line 460 "pascal.y"
{
  if (yyvsp[-2].expression->result->type->code == TYPE_FUNCTION)
    {
      /*This is pascal syntax for returning a value from a function*/
      Tac *ret = make_tac(TAC_RETURN, yyvsp[0].expression->result, NULL, NULL);
      ret->prev = yyvsp[0].expression->tac;
      yyval.tac = ret;
    }
  else
    {
      /*Join code needed to access array with the expression code, executing the array index code last*/
      Tac *joined = join_tac(yyvsp[0].expression->tac, yyvsp[-2].expression->tac);

      /*Update the expression with a pointer to our bolted together code*/
      yyvsp[0].expression->tac = joined;
      yyval.tac = tac_assign(yyvsp[-2].expression->result, yyvsp[0].expression);
    }

  /*Free*/
  free(yyvsp[-2].expression);
}
break;
case 47:
#line 482 "pascal.y"
{
  yyval.tac = yyvsp[0].tac;
}
break;
case 48:
#line 486 "pascal.y"
{
  yyval.tac = yyvsp[0].tac;
}
break;
case 49:
#line 490 "pascal.y"
{
  yyval.tac = tac_if_else(yyvsp[-4].expression, yyvsp[-2].tac, yyvsp[0].tac);
}
break;
case 50:
#line 494 "pascal.y"
{
  yyval.tac = tac_while(yyvsp[-2].expression, yyvsp[0].tac);
}
break;
case 51:
#line 498 "pascal.y"
{
  debug("PRINT expression");
  Symbol *print = symboltable_recurse(get_scope(), "print");
  debug("print %d", print);
  yyval.tac = expression_call(print, yyvsp[0].expression)->tac;
}
break;
case 52:
#line 508 "pascal.y"
{
  /*$$ = $1;*/
  yyval.expression = make_expression(NULL, yyvsp[0].symbol, NULL);
}
break;
case 53:
#line 513 "pascal.y"
{
  yyval.expression = expression_array(yyvsp[-3].symbol, yyvsp[-1].expression);
/*die("Arrays not supported yet");*/
}
break;
case 54:
#line 521 "pascal.y"
{ 
  yyval.tac = expression_call(yyvsp[0].symbol, NULL)->tac;
}
break;
case 55:
#line 525 "pascal.y"
{
  debug("Expression call %s", yyvsp[-3].symbol->name);
  dump_expressions(yyvsp[-1].expression);
  yyval.tac = expression_call(yyvsp[-3].symbol, yyvsp[-1].expression)->tac;
}
break;
case 56:
#line 534 "pascal.y"
{
  yyval.op = TAC_ADD;
}
break;
case 57:
#line 538 "pascal.y"
{
  yyval.op = TAC_SUBTRACT;
}
break;
case 58:
#line 542 "pascal.y"
{
  yyval.op = TAC_OR;
}
break;
case 59:
#line 549 "pascal.y"
{
  yyval.op = TAC_MULTIPLY;
}
break;
case 60:
#line 553 "pascal.y"
{
  yyval.op = TAC_DIVIDE;
}
break;
case 61:
#line 557 "pascal.y"
{
  yyval.op = TAC_DIVIDE;/*TODO: this should be for reals*/
}
break;
case 62:
#line 561 "pascal.y"
{
  yyval.op = TAC_MOD;
}
break;
case 63:
#line 565 "pascal.y"
{
  yyval.op = TAC_AND;
}
break;
case 64:
#line 572 "pascal.y"
{
  yyval.op = TAC_EQUAL;
}
break;
case 65:
#line 576 "pascal.y"
{
  yyval.op = TAC_NOTEQUAL;
}
break;
case 66:
#line 580 "pascal.y"
{
yyval.op = TAC_LTE;
}
break;
case 67:
#line 584 "pascal.y"
{
  yyval.op = TAC_GTE;
}
break;
case 68:
#line 588 "pascal.y"
{
  yyval.op = TAC_LT;
}
break;
case 69:
#line 592 "pascal.y"
{
  yyval.op = TAC_GT;
}
break;
case 70:
#line 599 "pascal.y"
{
  
}
break;
#line 1128 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
