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

%token COLON_KEYWORD
%token SEMI_COLON_KEYWORD

%left OR_TOKEN LESS_THAN LESS_THAN_OR_EQUAL AND_TOKEN GREATER_THAN GREATER_THAN_OR_EQUAL BOOLEAN_EQUALS
%left NOT_EQUAL_TO MULT DIV MINUS PLUS 


%start program
%%

program : statement SEMI_COLON_KEYWORD program
		| comment program 
		| 
;    

comment : COMMENT_VALUE_TOKEN 
   {printf("\n This is a comment \n");}
;

statement : declaration
		  | initialisation
		  | read_statement
		  | print_statement

;

declaration : VAR_KEYWORD IDENTIFIER_TOKEN COLON_KEYWORD type 
              {printf("\n Found a declaration \n"); }

;

initialisation : boolean_initialisation | int_initialisation | float_initialisation | string_initialisation
;

read_statement : READ_KEYWORD OPENBRACKET IDENTIFIER_TOKEN CLOSEBRACKET
		{printf("\n  This is a read statement \n");}
;

print_statement : PRINT_KEYWORD OPENBRACKET general_expression CLOSEBRACKET
		{printf("\n  This is a print statement \n");}
;

general_expression : boolean_expression 
				   | integer_expression
				   | float_expression
				   | string_expression
;

boolean_initialisation :  VAR_KEYWORD IDENTIFIER_TOKEN COLON_KEYWORD BOOLEAN_KEYWORD EQUALS_KEYWORD boolean_expression 
              {printf("\n Found an initialisation  of a boolean\n"); }
;
int_initialisation :  VAR_KEYWORD IDENTIFIER_TOKEN COLON_KEYWORD INT_KEYWORD EQUALS_KEYWORD integer_expression 
              {printf("\n Found an initialisation  of an integer\n"); }
;

float_initialisation :  VAR_KEYWORD IDENTIFIER_TOKEN COLON_KEYWORD FLOAT_KEYWORD EQUALS_KEYWORD float_expression 
              {printf("\n Found an initialisation  of a float\n"); }
;

string_initialisation :  VAR_KEYWORD IDENTIFIER_TOKEN COLON_KEYWORD STRING_KEYWORD EQUALS_KEYWORD string_expression
              {printf("\n Found an initialisation  of a string\n"); }
;


type: BOOLEAN_KEYWORD | INT_KEYWORD | STRING_KEYWORD | FLOAT_KEYWORD
;

string_expression : STRING_VALUE_TOKEN
				  | OPENBRACKET string_expression CLOSEBRACKET
;

boolean_expression : boolean_value
				   | IDENTIFIER_TOKEN
				   | boolean_expression boolean_comparator boolean_expression
				   | NOT boolean_expression
				   | OPENBRACKET boolean_expression CLOSEBRACKET
				   | INTEGER_TOKEN boolean_comparator INTEGER_TOKEN
				   | FLOAT_NUMBER_TOKEN boolean_comparator FLOAT_NUMBER_TOKEN

;

boolean_comparator : OR_TOKEN
                   | AND_TOKEN
                   | BOOLEAN_EQUALS
                   | NOT_EQUAL_TO
                   | LESS_THAN
                   | LESS_THAN_OR_EQUAL
                   | GREATER_THAN
                   | GREATER_THAN_OR_EQUAL
;

boolean_value : TRUE_KEYWORD | FALSE_KEYWORD 
; 

integer_expression : INTEGER_TOKEN
				   | IDENTIFIER_TOKEN
				   | integer_expression number_comparator integer_expression
				   | OPENBRACKET integer_expression CLOSEBRACKET
				   | PLUS OPENBRACKET integer_expression CLOSEBRACKET
				   | MINUS OPENBRACKET integer_expression CLOSEBRACKET
;

float_expression   : FLOAT_NUMBER_TOKEN
				   | IDENTIFIER_TOKEN
				   | float_expression number_comparator float_expression
				   | OPENBRACKET float_expression CLOSEBRACKET
				   | PLUS OPENBRACKET float_expression CLOSEBRACKET
				   | MINUS OPENBRACKET float_expression CLOSEBRACKET
;




number_comparator : MINUS | PLUS | DIV | MULT 
;
         


%%