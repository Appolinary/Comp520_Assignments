%{
	#include <stdio.h>
	#include <stdbool.h>
	#include <stdlib.h>

	extern int yylineno;

	int yylex();
	void yyerror(const char *s){fprintf(stderr, "Error: line %d %s \n", yylineno,s ); exit(1);}
%}

%error-verbose

%union {
	int ACTUAL_INTEGER;
	char * ACTUAL_TEXT;
	float  ACTUAL_FLOAT;
}

%token tIDENTIFIER
%token <ACTUAL_INTEGER>tINTVAL
%token <ACTUAL_FLOAT>tFLOATVAL
%token <ACTUAL_TEXT>tSTRINGVAL

%token tVAR
%token tFLOAT
%token tINT
%token tSTRING
%token tBOOLEAN
%token tIF
%token tELSE
%token tWHILE
%token tREAD
%token tPRINT
%token tTRUE
%token tFALSE
%token t_LESS_THAN_OR_EQUAL
%token t_GREATER_THAN_OR_EQUAL
%token t_NOT_EQUAL_TO
%token tEQUALS
%token tAND
%token tOR
%token tNOT_IMPORTANT

%left tOR
%left tAND
%left tEQUALS t_NOT_EQUAL_TO
%left t_GREATER_THAN_OR_EQUAL t_LESS_THAN_OR_EQUAL  '>' '<'
%left '+' '-'
%left '*' '/'
%left '!' tUMINUS

%start program

%%

program : statement ';' program
		| if_statement program
		| while_statement program
		|
;

statement: tVAR tIDENTIFIER ':' tBOOLEAN '=' expression
		 | tVAR tIDENTIFIER ':' tINT '=' expression
		 | tVAR tIDENTIFIER ':' tFLOAT '=' expression
		 | tVAR tIDENTIFIER ':' tSTRING '=' expression
         | tVAR tIDENTIFIER ':' tBOOLEAN
         | tVAR tIDENTIFIER ':' tINT
         | tVAR tIDENTIFIER ':' tFLOAT
         | tVAR tIDENTIFIER ':' tSTRING
         | tIDENTIFIER '=' expression
         | tPRINT '(' expression ')' 
         | tREAD '(' tIDENTIFIER ')'
;

expression: tINTVAL
  		  | tFLOATVAL
  		  | tSTRINGVAL
  		  | tFALSE
  		  | tTRUE
		  | tIDENTIFIER
          | expression '*' expression
          | expression '/' expression
          | expression '+' expression
          | expression '-' expression
          | expression tEQUALS expression
          | expression t_LESS_THAN_OR_EQUAL expression 
		  |	expression t_GREATER_THAN_OR_EQUAL expression 
          | expression t_NOT_EQUAL_TO expression
          | expression  tAND expression
		  | expression tOR expression 
		  | expression '<' expression
		  | expression '>' expression
          | '!' expression
          | '-' expression %prec tUMINUS
          | '(' expression ')'
;

if_statement: tIF '(' expression ')' '{' program '}' 
			| tIF '(' expression ')' '{' program '}' tELSE if_statement
			| tIF '(' expression ')' '{' program '}' tELSE '{' program '}'
;

while_statement: tWHILE '(' expression ')' '{' program '}'
;

%%