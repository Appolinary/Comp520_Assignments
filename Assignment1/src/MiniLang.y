%{
	#include <stdio.h>
	#include <stdbool.h>
	#include <stdlib.h>
	#include "tree.h"

	extern int yylineno;
	extern STATEMENT * root;

	int yylex();
	void yyerror(const char *s){fprintf(stderr, "Error: line %d %s \n", yylineno,s ); exit(1);}
%}

%locations
%error-verbose

%code requires{
	#include "tree.h"
}

%union {
	int ACTUAL_INTEGER;
	char * ACTUAL_TEXT;
	float  ACTUAL_FLOAT;
	STATEMENT * mystatement;
	EXP * exp;
}

%type <mystatement> program statement while_statement if_statement
%type <exp> expression



%token <ACTUAL_INTEGER>tINTVAL
%token <ACTUAL_FLOAT>tFLOATVAL
%token <ACTUAL_TEXT>tSTRINGVAL


%token <ACTUAL_TEXT> tIDENTIFIER
%token tVAR
%token tFLOAT
%token tINT
%token tSTRING
%token tBOOLEAN
%token tIF
%token tELSE
%token tWHILE
%token <ACTUAL_TEXT>tREAD
%token <ACTUAL_TEXT>tPRINT
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

program : %empty                 {$$ = NULL;}
        | statement ';' program   {root =  $1; $$ = $1;  $$->next = $3;}
		| if_statement program    {root = $1; $$ = $1; $$->next = $2;}
		| while_statement program  {root = $1; $$ = $1; $$->next = $2;}
;

statement: tVAR tIDENTIFIER ':' tBOOLEAN '=' expression { $$ = initialisationStatement($2,"boolean", $6); }
		 | tVAR tIDENTIFIER ':' tINT '=' expression   { $$ = initialisationStatement($2, "int",$6); }
		 | tVAR tIDENTIFIER ':' tFLOAT '=' expression  { $$ = initialisationStatement($2,"float", $6); }
		 | tVAR tIDENTIFIER ':' tSTRING '=' expression   { $$ = initialisationStatement($2,"string" , $6); }
         | tVAR tIDENTIFIER ':' tBOOLEAN   {$$ = declarationStatement($2, "boolean");}
         | tVAR tIDENTIFIER ':' tINT   {$$ = declarationStatement($2, "int");}
         | tVAR tIDENTIFIER ':' tFLOAT   {$$ = declarationStatement($2, "float");}
         | tVAR tIDENTIFIER ':' tSTRING   {$$ = declarationStatement($2, "string");}
         | tIDENTIFIER '=' expression  {$$ = assignmentStatement($1, $3);}
         | tPRINT '(' expression ')'  {$$ = printStatement($3);}
         | tREAD '(' tIDENTIFIER ')'  {$$ = readStatement($3);}


expression: tINTVAL                                       {$$ = makeIntLiteralExpression($1);}
  		  | tFLOATVAL                                     {$$ = makeFloatLiteralExpression($1);}
  		  | tSTRINGVAL                                    {$$ = makeStringLiteralExpression($1);}
  		  | tFALSE                                        {$$ = makeBooleanLiteralExpression("false");}
  		  | tTRUE                                         {$$ = makeBooleanLiteralExpression("true");}
		  | tIDENTIFIER                                   {$$ = makeIdentifierExpression($1);}
          | expression '*' expression                     {$$ = makeExpressionFromOperations( $1, $3, k_expressionKindMultiplication);}
          | expression '/' expression                     {$$ = makeExpressionFromOperations( $1, $3, k_expressionKindDivision);}
          | expression '+' expression                     {$$ = makeExpressionFromOperations( $1, $3, k_expressionKindAddition);}
          | expression '-' expression                     {$$ = makeExpressionFromOperations( $1, $3, k_expressionKindSubtraction);}
          | expression tEQUALS expression                 {$$ = makeExpressionFromOperations( $1, $3, k_expressionKindDoubleEquals);}
          | expression t_LESS_THAN_OR_EQUAL expression     {$$ = makeExpressionFromOperations( $1, $3, k_expressionKindLessThanOrEqualTo);}
		  |	expression t_GREATER_THAN_OR_EQUAL expression  {$$ = makeExpressionFromOperations( $1, $3, k_expressionKindGreaterThanOrEqualTo);}
          | expression t_NOT_EQUAL_TO expression            {$$ = makeExpressionFromOperations( $1, $3, k_expressionKindNotEqualTo);}
          | expression  tAND expression                    {$$ = makeExpressionFromOperations( $1, $3, k_expressionKindBooleanAnd);}
		  | expression tOR expression                      {$$ = makeExpressionFromOperations( $1, $3, k_expressionKindBooleanOr);}
		  | expression '<' expression                      {$$ = makeExpressionFromOperations( $1, $3, k_expressionKindLessThan);}
		  | expression '>' expression                      {$$ = makeExpressionFromOperations( $1, $3, k_expressionKindGreaterThan);}
          | '!' expression                                 {$$ = makeExpressionFromOperations( $2, NULL, k_expressionKindUnaryNegate);}
          | '-' expression %prec tUMINUS                   {$$ = makeExpressionFromOperations( $2, NULL, k_expressionKindUnaryMinus);}
          | '(' expression ')'                             {$$ = $2;}
;
 
if_statement: tIF '(' expression ')' '{' program '}'   {$$ =  ifStatementCreation($3, $6); }
			| tIF '(' expression ')' '{' program '}' tELSE if_statement {$$ = ifStatementCreation3($3, $6, $9);}
			| tIF '(' expression ')' '{' program '}' tELSE '{' program '}'  {$$ = ifStatementCreation2($3, $6, $10);}
;

while_statement: tWHILE '(' expression ')' '{' program '}' {$$ = whileStatementCreation($3, $6); }
;

%%