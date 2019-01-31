/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 17 "MiniLang.y" /* yacc.c:1909  */

	#include "tree.h"

#line 48 "y.tab.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    tINTVAL = 258,
    tFLOATVAL = 259,
    tSTRINGVAL = 260,
    tIDENTIFIER = 261,
    tVAR = 262,
    tFLOAT = 263,
    tINT = 264,
    tSTRING = 265,
    tBOOLEAN = 266,
    tIF = 267,
    tELSE = 268,
    tWHILE = 269,
    tREAD = 270,
    tPRINT = 271,
    tTRUE = 272,
    tFALSE = 273,
    t_LESS_THAN_OR_EQUAL = 274,
    t_GREATER_THAN_OR_EQUAL = 275,
    t_NOT_EQUAL_TO = 276,
    tEQUALS = 277,
    tAND = 278,
    tOR = 279,
    tNOT_IMPORTANT = 280,
    tUMINUS = 281
  };
#endif
/* Tokens.  */
#define tINTVAL 258
#define tFLOATVAL 259
#define tSTRINGVAL 260
#define tIDENTIFIER 261
#define tVAR 262
#define tFLOAT 263
#define tINT 264
#define tSTRING 265
#define tBOOLEAN 266
#define tIF 267
#define tELSE 268
#define tWHILE 269
#define tREAD 270
#define tPRINT 271
#define tTRUE 272
#define tFALSE 273
#define t_LESS_THAN_OR_EQUAL 274
#define t_GREATER_THAN_OR_EQUAL 275
#define t_NOT_EQUAL_TO 276
#define tEQUALS 277
#define tAND 278
#define tOR 279
#define tNOT_IMPORTANT 280
#define tUMINUS 281

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 21 "MiniLang.y" /* yacc.c:1909  */

	int ACTUAL_INTEGER;
	char * ACTUAL_TEXT;
	float  ACTUAL_FLOAT;
	STATEMENT * mystatement;
	EXP * exp;

#line 120 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
