#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "pretty.h"

void yyparse();
int yylex();

int print_token = 0;

STATEMENT * root;

int main(int argc, char ** argv){

	if(argc != 2){
		printf("Enter the right number of arguments \n");
		return 0;
	}

	char * mode = argv[1];
	char * tokens = "tokens";
	char * scan = "scan";
	char * parse = "parse";

	print_token = 0;

	if(strcmp(mode, scan) == 0){
		while(yylex());
		printf("OK\n");
	}

	if(strcmp(mode, tokens) == 0){
		print_token =  1;
		while(yylex());
	}
	if(strcmp(mode, parse) == 0){
		yyparse();       
		printf("OK\n\n\n");

		pretty_print(root , 0); //ie its not in body

		printf("\n\n\n\n");

	}


	return 0;
}
