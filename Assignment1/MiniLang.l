%{
	#include "y.tab.h"
	#include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
%}

%option yylineno


%%

[ \a\b\f\n\r\t\v] 

"//".*  {
	yylval.ACTUAL_TEXT = yytext;
    return COMMENT_VALUE_TOKEN;
}

"~"  {return NOT_IMPORTANT;}
"@"  {return NOT_IMPORTANT;}
"#" {return NOT_IMPORTANT;}
"$" {return NOT_IMPORTANT;}
"%" {return NOT_IMPORTANT;}
"^" {return NOT_IMPORTANT;}
"&" {return NOT_IMPORTANT;}
"["  {return NOT_IMPORTANT;}
"]" {return NOT_IMPORTANT;}
"?" {return NOT_IMPORTANT;}
"'" {return NOT_IMPORTANT;}
"`"  {return NOT_IMPORTANT;}

"<"   { return LESS_THAN;}
">"   { return GREATER_THAN;}
"<="   { return LESS_THAN_OR_EQUAL;}
">="   { return GREATER_THAN_OR_EQUAL;}
"!="   {return NOT_EQUAL_TO; }
"+"    { return PLUS;}
"-"     {return MINUS;}
"/"     {return DIV;}
"*"     {return MULT;}
"!"     {return NOT;}
"("     {return OPENBRACKET;}
")"     {return CLOSEBRACKET;}
"{"      {return OPENCURLYBRACKET;}
"}"      {return CLOSECURLYBRACKET;}
"=="     {return BOOLEAN_EQUALS;}
"&&"    {return AND_TOKEN;}
"||"    {return OR_TOKEN;}
":"   {return COLON_KEYWORD;}
";"   {return SEMI_COLON_KEYWORD;}
"="   {return EQUALS_KEYWORD;}
"var" {return VAR_KEYWORD;}
"float" {return FLOAT_KEYWORD;}
"int" {return INT_KEYWORD;}
"string" {return STRING_KEYWORD;}
"boolean" { return BOOLEAN_KEYWORD;}
"if" {return IF_KEYWORD;}
"else" {return ELSE_KEYWORD;}
"while" {return WHILE_KEYWORD;}
"read" {return READ_KEYWORD;}
"print" {return PRINT_KEYWORD;}
"true" {
 	  yylval.ACTUAL_INTEGER = 1;
      return TRUE_KEYWORD;
  }
"false" {
	yylval.ACTUAL_INTEGER = 0;
	return FALSE_KEYWORD;
}

[+-]?([0-9])*  {
	yylval.ACTUAL_INTEGER = atoi(yytext);
	return  INTEGER_TOKEN;
}


[+-]?([0-9]*[.])?[0-9]+ {
	yylval.ACTUAL_FLOAT = atof(yytext);
	return FLOAT_NUMBER_TOKEN;
}

[a-zA-Z_][a-zA-Z0-9_]* {
	yylval.ACTUAL_TEXT = yytext;
	return IDENTIFIER_TOKEN;
} 


\"(\\.|[^"\\])*\" { 
	yylval.ACTUAL_TEXT = yytext;
	return STRING_VALUE_TOKEN; 
}

.  { printf(" Error at :  '%d\n", yylineno ); exit(1);}


%%

