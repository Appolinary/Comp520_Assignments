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

"//".* 

"~"  {return tNOT_IMPORTANT ; }
"@"  {return tNOT_IMPORTANT ; }
"#"  {return tNOT_IMPORTANT ; }
"$"  {return tNOT_IMPORTANT ; }
"%"  {return tNOT_IMPORTANT ; }
"^"  {return tNOT_IMPORTANT ; }
"&"  {return tNOT_IMPORTANT ; }
"["  {return tNOT_IMPORTANT ; }
"]"  {return tNOT_IMPORTANT ; }
"?"  {return tNOT_IMPORTANT ; }
"'"  {return tNOT_IMPORTANT ; }
"`"  {return tNOT_IMPORTANT ; }
"|"  {return tNOT_IMPORTANT ; }
"_"  {return tNOT_IMPORTANT ; }

"<"   { return '<';}
">"   { return '>';}
"<="   { return t_LESS_THAN_OR_EQUAL;}
">="   { return t_GREATER_THAN_OR_EQUAL;}
"!="   {return t_NOT_EQUAL_TO; }
"+"    { return '+';}
"-"     {return '-';}
"/"     {return '/';}
"*"     {return '*';}
"!"     {return '!';}
"("     {return '(';}
")"     {return ')';}
"{"      {return '{';}
"}"      {return '}';}
"=="     {return tEQUALS;}
"&&"    {return tAND;}
"||"    {return tOR;}
":"   {return ':';}
";"   {return ';';}
"="   {return '=';}
"var" {return tVAR;}
"float" {return tFLOAT;}
"int" {return tINT;}
"string" {return tSTRING;}
"boolean" { return tBOOLEAN;}
"if" {return tIF;}
"else" {return tELSE;}
"while" {return tWHILE;}
"read" {return tREAD;}
"print" {return tPRINT;}
"true" { return tTRUE;}
"false" {return tFALSE;}

[+-]?([0-9])*  {
	yylval.ACTUAL_INTEGER = atoi(yytext);
	return  tINTVAL;
}


[+-]?([0-9]*[.])?[0-9]+ {
	yylval.ACTUAL_FLOAT = atof(yytext);
	return tFLOATVAL;
}

[a-zA-Z_][a-zA-Z0-9_]* {
	yylval.ACTUAL_TEXT = yytext;
	return tIDENTIFIER;
} 


\"(\\.|[^"\\])*\" { 
	yylval.ACTUAL_TEXT = yytext;
	return tSTRINGVAL; 
}

.  { printf(" Error at :  '%d\n", yylineno ); exit(1);}


%%

