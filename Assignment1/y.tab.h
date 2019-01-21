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

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TRUE_KEYWORD = 258,
    FALSE_KEYWORD = 259,
    INTEGER_TOKEN = 260,
    IDENTIFIER_TOKEN = 261,
    FLOAT_NUMBER_TOKEN = 262,
    STRING_VALUE_TOKEN = 263,
    COMMENT_VALUE_TOKEN = 264,
    VAR_KEYWORD = 265,
    FLOAT_KEYWORD = 266,
    INT_KEYWORD = 267,
    STRING_KEYWORD = 268,
    BOOLEAN_KEYWORD = 269,
    IF_KEYWORD = 270,
    ELSE_KEYWORD = 271,
    WHILE_KEYWORD = 272,
    READ_KEYWORD = 273,
    PRINT_KEYWORD = 274,
    EQUALS_KEYWORD = 275,
    DOUBLE_OPENING_QUOTES_TOKEN = 276,
    DOUBLE_CLOSING_QUOTES_TOKEN = 277,
    LESS_THAN = 278,
    GREATER_THAN = 279,
    LESS_THAN_OR_EQUAL = 280,
    GREATER_THAN_OR_EQUAL = 281,
    NOT_EQUAL_TO = 282,
    PLUS = 283,
    MINUS = 284,
    DIV = 285,
    MULT = 286,
    NOT = 287,
    OPENBRACKET = 288,
    CLOSEBRACKET = 289,
    BOOLEAN_EQUALS = 290,
    AND_TOKEN = 291,
    OR_TOKEN = 292,
    EOLN = 293,
    COLON_KEYWORD = 294,
    SEMI_COLON_KEYWORD = 295
  };
#endif
/* Tokens.  */
#define TRUE_KEYWORD 258
#define FALSE_KEYWORD 259
#define INTEGER_TOKEN 260
#define IDENTIFIER_TOKEN 261
#define FLOAT_NUMBER_TOKEN 262
#define STRING_VALUE_TOKEN 263
#define COMMENT_VALUE_TOKEN 264
#define VAR_KEYWORD 265
#define FLOAT_KEYWORD 266
#define INT_KEYWORD 267
#define STRING_KEYWORD 268
#define BOOLEAN_KEYWORD 269
#define IF_KEYWORD 270
#define ELSE_KEYWORD 271
#define WHILE_KEYWORD 272
#define READ_KEYWORD 273
#define PRINT_KEYWORD 274
#define EQUALS_KEYWORD 275
#define DOUBLE_OPENING_QUOTES_TOKEN 276
#define DOUBLE_CLOSING_QUOTES_TOKEN 277
#define LESS_THAN 278
#define GREATER_THAN 279
#define LESS_THAN_OR_EQUAL 280
#define GREATER_THAN_OR_EQUAL 281
#define NOT_EQUAL_TO 282
#define PLUS 283
#define MINUS 284
#define DIV 285
#define MULT 286
#define NOT 287
#define OPENBRACKET 288
#define CLOSEBRACKET 289
#define BOOLEAN_EQUALS 290
#define AND_TOKEN 291
#define OR_TOKEN 292
#define EOLN 293
#define COLON_KEYWORD 294
#define SEMI_COLON_KEYWORD 295

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 14 "MiniLang.y" /* yacc.c:1909  */

	int ACTUAL_INTEGER;
	char * ACTUAL_TEXT;
	float  ACTUAL_FLOAT;

#line 140 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
