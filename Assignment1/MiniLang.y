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
	int ACTUAL_BOOLEAN;
	int ACTUAL_INTEGER;
	char * ACTUAL_TEXT;
	float  ACTUAL_FLOAT;
}

%token <ACTUAL_BOOLEAN> TRUE_KEYWORD
%token <ACTUAL_BOOLEAN> FALSE_KEYWORD
%token <ACTUAL_INTEGER> INTEGER_TOKEN
%token <ACTUAL_TEXT> IDENTIFIER_TOKEN
%token <ACTUAL_FLOAT> FLOAT_NUMBER_TOKEN

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

%token COLON_KEYWORD
%token SEMI_COLON_KEYWORD

%start program
%%

program : expression SEMI_COLON_KEYWORD program
		| 

;    

expression : declaration
		   | initialisation
;

declaration : VAR_KEYWORD IDENTIFIER_TOKEN COLON_KEYWORD type 
              {printf("\n Found a declaration \n"); }

;

initialisation :  VAR_KEYWORD IDENTIFIER_TOKEN COLON_KEYWORD type EQUALS_KEYWORD value 
              {printf("\n Found an initialisation \n"); }
;

type : BOOLEAN_KEYWORD 
     | FLOAT_KEYWORD 
     | INT_KEYWORD 
     | STRING_KEYWORD
; 

value : FLOAT_NUMBER_TOKEN
	  | boolean
	  | INTEGER_TOKEN
;

boolean : FALSE_KEYWORD
		| TRUE_KEYWORD
;


%%