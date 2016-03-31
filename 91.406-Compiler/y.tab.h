#ifndef YYERRCODE
#define YYERRCODE 256
#endif

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
typedef union
{
  Type *type;
  Tac *tac;
  Symbol *symbol;
  Expression *expression;
  int op;
  Interval *interval;
} YYSTYPE;
extern YYSTYPE yylval;
