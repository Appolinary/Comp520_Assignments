
#include "CodeGeneration.h"




void codeGenerate(STATEMENT * statement , int indentation){ // 1  = in body means its in if body or while body; 0 = means its not

	if(statement == NULL){return;}

	char * tab = "   ";

	for(int i = 0; i < indentation; i++){
		printf("%s",tab);
	}
	switch(statement->kind){

        case k_statementKindAssignment:
        	printf("%s = ", statement->val.assignment.identifier); 
        	prettyEXP(statement->val.assignment.expression); 
        	printf(";\n");
        	
		    codeGenerate(statement->next, indentation);
		    
		    break;
	    case k_statementKindDeclaration:

	    	//char * type = statement->val.declaration.type;
	    	if(strcmp(statement->val.declaration.type, "string") == 0){
	    	   printf("char *  %s;\n", statement->val.declaration.identifier);

	    	}
	    	else if(strcmp(statement->val.declaration.type, "boolean") == 0){
	    	   printf("bool  %s;\n", statement->val.declaration.identifier);
	    	}
	    	else{
	    	    printf("%s  %s;\n", statement->val.declaration.type, statement->val.declaration.identifier);
	    	}

		   
		    codeGenerate(statement->next , indentation);
		    
		    break;
	    case k_statementKindInitialisation:


	    	//char * type = statement->val.initialisation.type;
	    	if(strcmp(statement->val.initialisation.type, "string") == 0){
	    	   printf("char *  %s = ", statement->val.initialisation.identifier);
	    	   prettyEXP(statement->val.initialisation.expression); printf(";\n");

	    	}
	    	else if(strcmp(statement->val.initialisation.type, "boolean") == 0){
	    	   printf("bool  %s = ", statement->val.initialisation.identifier);
	    	   prettyEXP(statement->val.initialisation.expression); printf(";\n");
	    	}
	    	else{
	    	    printf("%s  %s = ", statement->val.initialisation.type, statement->val.initialisation.identifier);
	    	    prettyEXP(statement->val.initialisation.expression); printf(";\n");
	    	}
		    
		    codeGenerate(statement->next, indentation);
		    
		    break;
		case k_statementKindPrintStatement:
			printf("print("); prettyEXP(statement->val.print); printf("); \n");
		    
		    codeGenerate(statement->next, indentation);
		    
		    break;
		case k_statementKindReadStatement:

		    //first get the type of the variable


		    printf("read(%s);\n", statement->val.read);
		    
		    codeGenerate(statement->next, indentation);
		    
		    break;
		case k_statementKindIfStatement:
		    printf("if(");
		    prettyEXP(statement->val.ifStatement.conditionExpression);
		    printf("){\n");
		    codeGenerate(statement->val.ifStatement.body, indentation + 1);
		    for(int i = 0; i < indentation; i++ ) {
		    	printf("%s", tab);

		    }
		    printf("}\n");
		    	//if its an else if statement then just call the same function
		    char * statementPresent = statement->val.ifStatement.present;
		    if(statementPresent != NULL && strcmp(statement->val.ifStatement.present, "elseIf") == 0 ){
		    	for(int i = 0; i < indentation; i++ ) {
		    		printf("%s", tab);
		        }
		    	printf("else");
		    	codeGenerate(statement->val.ifStatement.presentStatement, indentation);
		    }


		    	//else body
		    
		    if(statementPresent != NULL && strcmp(statement->val.ifStatement.present, "else") == 0 ){
		    	STATEMENT * elseStatement = statement->val.ifStatement.presentStatement;
		    	for(int i = 0; i < indentation; i++ ) {
		    		printf("%s", tab);
		        }
		    	printf("else {\n");
		    	codeGenerate(elseStatement, indentation + 1);

		    	for(int i = 0; i < indentation; i++ ) {
		    		printf("%s", tab);
		        }
		    	printf("}\n");

		    }

		    codeGenerate(statement->next, indentation);
			break;
		case k_statementKindWhileStatement:
		    printf("while("); prettyEXP(statement->val.whileStatement.conditionExpression); printf("){\n");
		    STATEMENT * st = statement->val.whileStatement.body;
		    
		    codeGenerate(st, indentation + 1); //indent by 1 space
		    	
		    for(int i = 0; i < indentation; i++){
		    	printf("%s", tab);
		    }
		    printf("}\n");
		    
		    codeGenerate(statement->next, indentation);
		    
		    break;

	}
}