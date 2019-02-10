#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "pretty.h"
#include "SymbolTable.h"
#include "CodeGeneration.h"

#include <unistd.h>
#include <sys/fcntl.h>

void yyparse();
int yylex();

int print_token = 0;

STATEMENT * root;

int main(int argc, char ** argv){

	if(argc != 2){
		printf("Enter the right number of arguments \n");
		return 0;
	}
   // char * fileName = argv[2];

	char * mode = argv[1];
	char * tokens = "tokens";
	char * scan = "scan";
	char * parse = "parse";

	//new ones for assignment 2
	char * symbol = "symbol";
	char * typecheck = "typecheck";
	char * pretty = "pretty";
	char * codegen = "codegen";

	print_token = 0;

	SymbolTable * table = malloc(sizeof(SymbolTable));


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

	}
	if(strcmp(mode, symbol) == 0){
		//print out the symbol table
		validateSymbols(root, table);

	}

	if(strcmp(mode, typecheck) == 0){
        validateSymbols(root, table);
	}

	if(strcmp(mode, pretty) == 0){

		yyparse();       
		pretty_print(root, 1);

	}
	if(strcmp(mode, codegen) == 0){

		yyparse();       

		validateSymbols(root, table);

		int std = dup(1);

		printf("\n");
		close(1);

		int fd = open("codegen.c", O_WRONLY |O_CREAT , 0644);

		printf("#include <stdio.h>\n#include <stdlib.h>\n#include <stdbool.h>\n#include <string.h>\n\n\n");
		printf("int main(){\n");
        
		codeGenerate(root, table, 1);

		printf("   return 0;\n");
		printf("}\n");
		printf("\n\n");
        
        close(fd);
		dup2(std, 1);

	
		printf("OK\n");

	}


	return 0;
}
