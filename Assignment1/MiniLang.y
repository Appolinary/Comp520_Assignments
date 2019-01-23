%{
	#include <stdio.h>
	#include <stdbool.h>
	#include <stdlib.h>

	extern int yylineno;

	int yylex();
	void yyerror(const char *s){fprintf(stderr, "Error at line : %d %s \n", yylineno,s ); exit(1);}
%}

%error-verbose

%union {
	int ACTUAL_INTEGER;
	char * ACTUAL_TEXT;
	float  ACTUAL_FLOAT;
}

%token <ACTUAL_INTEGER> TRUE_KEYWORD
%token <ACTUAL_INTEGER> FALSE_KEYWORD
%token <ACTUAL_INTEGER> INTEGER_TOKEN
%token <ACTUAL_TEXT> IDENTIFIER_TOKEN
%token <ACTUAL_FLOAT> FLOAT_NUMBER_TOKEN
%token <ACTUAL_TEXT> STRING_VALUE_TOKEN
%token <ACTUAL_TEXT> COMMENT_VALUE_TOKEN


%token VAR_KEYWORD
%token FLOAT_KEYWORD
%token INT_KEYWORD
%token STRING_KEYWORD
%token BOOLEAN_KEYWORD
%token IF_KEYWORD
%token ELSE_KEYWORD
%token WHILE_KEYWORD
%token READ_KEYWORD
%token PRINT_KEYWORD
%token EQUALS_KEYWORD
%token DOUBLE_OPENING_QUOTES_TOKEN
%token DOUBLE_CLOSING_QUOTES_TOKEN
%token OPENCURLYBRACKET
%token CLOSECURLYBRACKET

%token LESS_THAN
%token GREATER_THAN
%token LESS_THAN_OR_EQUAL
%token GREATER_THAN_OR_EQUAL
%token NOT_EQUAL_TO
%token PLUS
%token MINUS
%token DIV
%token MULT
%token NOT
%token OPENBRACKET
%token CLOSEBRACKET
%token BOOLEAN_EQUALS
%token AND_TOKEN
%token OR_TOKEN
%token EOLN
%token WILDCARD
%token NOT_IMPORTANT

%token COLON_KEYWORD
%token SEMI_COLON_KEYWORD

%left OR_TOKEN LESS_THAN LESS_THAN_OR_EQUAL AND_TOKEN GREATER_THAN GREATER_THAN_OR_EQUAL BOOLEAN_EQUALS
%left NOT_EQUAL_TO MULT DIV MINUS PLUS 


%start program
%%

program: statement SEMI_COLON_KEYWORD program | comment program | while_statement program | if_statement program
	   | 
; 
while_statement: WHILE_KEYWORD OPENBRACKET expression CLOSEBRACKET  OPENCURLYBRACKET program CLOSECURLYBRACKET
               ;
if_statement:IF_KEYWORD OPENBRACKET expression CLOSEBRACKET  OPENCURLYBRACKET program CLOSECURLYBRACKET else_if_statements
            | IF_KEYWORD OPENBRACKET expression CLOSEBRACKET  OPENCURLYBRACKET program CLOSECURLYBRACKET else_statement 
			
; 
else_statement : ELSE_KEYWORD OPENCURLYBRACKET program CLOSECURLYBRACKET | 
;

else_if_statements: ELSE_KEYWORD IF_KEYWORD OPENBRACKET expression CLOSEBRACKET OPENCURLYBRACKET program CLOSECURLYBRACKET else_statement
				  | ELSE_KEYWORD IF_KEYWORD OPENBRACKET expression CLOSEBRACKET OPENCURLYBRACKET program CLOSECURLYBRACKET else_if_statements
;

comment : COMMENT_VALUE_TOKEN 
   {printf("\n This is a comment \n");}
;

expression: literal | expression binary_operator expression | unary_operator expression | OPENBRACKET expression CLOSEBRACKET
;

literal: IDENTIFIER_TOKEN | FLOAT_NUMBER_TOKEN | INTEGER_TOKEN | STRING_VALUE_TOKEN | TRUE_KEYWORD | FALSE_KEYWORD
;

statement: initialisation | declaration | assignment | read_statement | print_statement | OPENBRACKET statement CLOSEBRACKET
;

initialisation: VAR_KEYWORD IDENTIFIER_TOKEN COLON_KEYWORD type EQUALS_KEYWORD expression
;

declaration: VAR_KEYWORD IDENTIFIER_TOKEN COLON_KEYWORD type 
;

assignment: IDENTIFIER_TOKEN EQUALS_KEYWORD expression
;

read_statement: READ_KEYWORD OPENBRACKET IDENTIFIER_TOKEN CLOSEBRACKET
;

print_statement: PRINT_KEYWORD OPENBRACKET expression CLOSEBRACKET 
;

binary_operator: PLUS | MINUS | MULT | DIV | BOOLEAN_EQUALS | NOT_EQUAL_TO | GREATER_THAN_OR_EQUAL | LESS_THAN_OR_EQUAL | GREATER_THAN | LESS_THAN | AND_TOKEN | OR_TOKEN
;

unary_operator: NOT | MINUS
; 

type: FLOAT_KEYWORD | INT_KEYWORD | STRING_KEYWORD | BOOLEAN_KEYWORD
;


%%