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
    VAR_KEYWORD = 263,
    FLOAT_KEYWORD = 264,
    INT_KEYWORD = 265,
    STRING_KEYWORD = 266,
    BOOLEAN_KEYWORD = 267,
    IF_KEYWORD = 268,
    ELSE_KEYWORD = 269,
    WHILE_KEYWORD = 270,
    READ_KEYWORD = 271,
    PRINT_KEYWORD = 272,
    EQUALS_KEYWORD = 273,
    DOUBLE_OPENING_QUOTES_TOKEN = 274,
    DOUBLE_CLOSING_QUOTES_TOKEN = 275,
    COLON_KEYWORD = 276,
    SEMI_COLON_KEYWORD = 277
  };
#endif
/* Tokens.  */
#define TRUE_KEYWORD 258
#define FALSE_KEYWORD 259
#define INTEGER_TOKEN 260
#define IDENTIFIER_TOKEN 261
#define FLOAT_NUMBER_TOKEN 262
#define VAR_KEYWORD 263
#define FLOAT_KEYWORD 264
#define INT_KEYWORD 265
#define STRING_KEYWORD 266
#define BOOLEAN_KEYWORD 267
#define IF_KEYWORD 268
#define ELSE_KEYWORD 269
#define WHILE_KEYWORD 270
#define READ_KEYWORD 271
#define PRINT_KEYWORD 272
#define EQUALS_KEYWORD 273
#define DOUBLE_OPENING_QUOTES_TOKEN 274
#define DOUBLE_CLOSING_QUOTES_TOKEN 275
#define COLON_KEYWORD 276
#define SEMI_COLON_KEYWORD 277

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 14 "MiniLang.y" /* yacc.c:1909  */

	int ACTUAL_BOOLEAN;
	int ACTUAL_INTEGER;
	char * ACTUAL_TEXT;
	float  ACTUAL_FLOAT;

#line 105 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
