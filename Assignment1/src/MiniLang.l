%{
	#include "y.tab.h"
	#include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>

    extern int print_token;
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

"<"   { if(print_token) printf("tLESSTHAN\n"); return '<';}
">"   { if(print_token) printf("tGREATERTHAN\n");return '>';}
"<="   { if(print_token) printf("t_LESS_THAN_OR_EQUAL\n");return t_LESS_THAN_OR_EQUAL;}
">="   { if(print_token) printf("t_GREATER_THAN_OR_EQUAL\n");return t_GREATER_THAN_OR_EQUAL;}
"!="   {if(print_token) printf("t_NOT_EQUAL_TO\n");return t_NOT_EQUAL_TO; }
"+"    { if(print_token) printf("tPLUS\n");return '+';}
"-"     {if(print_token) printf("tMINUS\n");return '-';}
"/"     {if(print_token) printf("tDIV\n");return '/';}
"*"     {if(print_token) printf("tMULT\n");return '*';}
"!"     {if(print_token) printf("tUNARY_NOT\n");return '!';}
"("     {if(print_token) printf("tOPENBRACKET\n");return '(';}
")"     {if(print_token) printf("TCLOSEBRACKET\n");return ')';}
"{"      {if(print_token) printf("tCURLYOPENBRACKET\n");return '{';}
"}"      {if(print_token) printf("tCLOSECURLYBRACKET\n");return '}';}
"=="     {if(print_token) printf("tBOOLEANEQUALS\n");return tEQUALS;}
"&&"    {if(print_token) printf("tAND\n");return tAND;}
"||"    {if(print_token) printf("tOR\n");return tOR;}
":"   {if(print_token) printf("tCOLON\n");return ':';}
";"   {if(print_token) printf("tSEMICOLON\n");return ';';}
"="   {if(print_token) printf("tEQUALS\n");return '=';}
"var" { if(print_token) printf("tVAR\n"); return tVAR;}
"float" {if(print_token) printf("tFLOAT\n"); return tFLOAT;}
"int" {if(print_token) printf("tINT\n"); return tINT;}
"string" {if(print_token) printf("tSTRING\n"); return tSTRING;}
"boolean" { if(print_token) printf("tBOOLEAN\n"); return tBOOLEAN;}
"if" {if(print_token) printf("tIF\n"); return tIF;}
"else" {if(print_token) printf("tELSE\n"); return tELSE;}
"while" {if(print_token) printf("tWHILE\n"); return tWHILE;}
"read" {if(print_token) printf("tREAD\n"); return tREAD;}
"print" {if(print_token) printf("tPRINT\n"); return tPRINT;}
"true" {if(print_token) printf("tTRUE\n");  return tTRUE;}
"false" {if(print_token) printf("tFALSE\n"); return tFALSE;}

[+-]?([0-9])*  {
	yylval.ACTUAL_INTEGER = atoi(yytext);
	if(print_token) printf("tINTVAL(%s)\n", yytext); 
	return  tINTVAL;
}


[+-]?([0-9]*[.])?[0-9]+ {
	yylval.ACTUAL_FLOAT = atof(yytext);
	if(print_token) printf("tFLOATVAL(%s)\n", yytext); 
	return tFLOATVAL;
}

[a-zA-Z_][a-zA-Z0-9_]* {
	yylval.ACTUAL_TEXT = yytext;
	if(print_token) printf("tIDENTIFIER(%s)\n", yytext); 
	return tIDENTIFIER;
} 


\"(\\.|[^"\\])*\" { 
	yylval.ACTUAL_TEXT = yytext;
	if(print_token) printf("tSTRINGVAL(%s)\n", yytext); 
	return tSTRINGVAL; 
}

.  {fprintf(stderr, "Error: line %d unkown symbol %s \n", yylineno, yytext); exit(1);}


%%
