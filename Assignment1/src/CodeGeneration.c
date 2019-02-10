
#include "CodeGeneration.h"




void codeGenerate(STATEMENT * statement , SymbolTable * table , int indentation){ // 1  = in body means its in if body or while body; 0 = means its not

	if(statement == NULL){return;}

	char * tab = "   ";

	for(int i = 0; i < indentation; i++){
		printf("%s",tab);
	}
	switch(statement->kind){

        case k_statementKindAssignment:{
        	printf("%s = ", statement->val.assignment.identifier); 

        	//where to write expression for string;
        	

        	prettyEXP(statement->val.assignment.expression); 
            
        	printf(";\n");
        	
		    codeGenerate(statement->next, table,  indentation);
		    
		    break;
		}
	    case k_statementKindDeclaration:

	    	//char * type = statement->val.declaration.type;
	    	if(strcmp(statement->val.declaration.type, "string") == 0){
	    	   printf("char *  %s = malloc(sizeof(char));\n", statement->val.declaration.identifier);

	    	}
	    	else if(strcmp(statement->val.declaration.type, "boolean") == 0){
	    	   printf("bool  %s = false;\n", statement->val.declaration.identifier);
	    	}
	    	else if(strcmp(statement->val.declaration.type, "float") == 0){
	    	   printf("float  %s = 0.0;\n", statement->val.declaration.identifier);
	    	}
	    	else{
	    	    printf("%s  %s = 0;\n", statement->val.declaration.type, statement->val.declaration.identifier);
	    	}

		   
		    codeGenerate(statement->next , table, indentation);
		    
		    break;
	    case k_statementKindInitialisation:


	    	//char * type = statement->val.initialisation.type;
	    	if(strcmp(statement->val.initialisation.type, "string") == 0){
	    	   printf("char *  %s = ", statement->val.initialisation.identifier);
	    	   prettyEXP(statement->val.initialisation.expression);
	    	   //prettyEXP(statement->val.initialisation.expression);
	    	   printf(";\n");

	    	}
	    	else if(strcmp(statement->val.initialisation.type, "boolean") == 0){
	    	   printf("bool  %s = ", statement->val.initialisation.identifier);
	    	   prettyEXP(statement->val.initialisation.expression); printf(";\n");
	    	}
	    	else{
	    	    printf("%s  %s = ", statement->val.initialisation.type, statement->val.initialisation.identifier);
	    	    prettyEXP(statement->val.initialisation.expression); printf(";\n");
	    	}
		    
		    codeGenerate(statement->next, table,  indentation);
		    
		    break;
		case k_statementKindPrintStatement: {
		    //get the type of the expression
   			Type type = k_typeInvalid;  type = getType(statement->val.print, table);

   			char * str1 = malloc(sizeof(char));

   		    str1 = "%s"; //assume the type is a string

   			if(type == k_typeInteger || type == k_typeBoolean){
   				str1 = "%d";
   			}
   			else if (type == k_typeFloat){
   				str1 = "%f";
   			}

			printf("printf(\"%s\\n\",", str1); 

        	prettyEXP(statement->val.print); 
            
			printf("); \n");
		    
		    codeGenerate(statement->next, table, indentation);
		    
		    break;
		}
		case k_statementKindReadStatement:{

             char * variable = statement->val.read;
		    //get the type of the variable
		    Symbol * symbol = getSymbol(table, variable);

		    char * type1 = malloc(sizeof(char));
            
            char * str = "%s";

            Type typeK =  k_typeInvalid;


            if(symbol->kind == k_symbolKindAssignment){
               typeK =  getType(symbol->data->data.assignmentSymbol->expressionValue, table);
            }
            if(symbol->kind == k_symbolKindDeclaration){
               type1  = symbol->data->data.declarationSymbol->type;
            }
            if(symbol->kind == k_symbolKindInitialisation){
               type1 = symbol->data->data.initialisationSymbol->type;
           }

           if(strcmp(type1, "boolean") == 0 || typeK == k_typeBoolean){
               str = "%s";
           }
           if(strcmp(type1, "int") == 0 || typeK ==  k_typeInteger){
              str =  "%d";
           }

           if(strcmp(type1, "float") == 0 || typeK ==  k_typeFloat){
               str = "%f";
           }


           if(strcmp(type1, "boolean") == 0 || typeK == k_typeBoolean){

              char  tempVariable[100]; //= malloc(sizeof(char));
           	  strcpy(tempVariable,"temp");
           	  strcat(tempVariable, variable);

           	  printf("char * %s =  malloc(sizeof(char));\n", tempVariable);

           	  for(int i = 0; i < indentation; i++){
           	  	printf("%s", tab);
           	  }

           	  printf("scanf(\"%s\", %s);\n", str, tempVariable);

           	  for(int i = 0; i < indentation; i++){
           	  	printf("%s", tab);
           	  }

           	  printf("if(strcmp(%s,\"true\") == 0){\n", tempVariable);

           	  for(int i = 0; i < indentation + 1; i++){
           	  	printf("%s", tab);
           	  }
           	  printf("%s = 1;\n", variable);
           	   for(int i = 0; i < indentation; i++){
           	  	printf("%s", tab);
           	  }
           	  printf("}\n");
           	   for(int i = 0; i < indentation; i++){
           	  	printf("%s", tab);
           	  }
           	  printf("else if(strcmp(%s,\"false\") == 0){\n", tempVariable);

           	  for(int i = 0; i < indentation + 1; i++){
           	  	printf("%s", tab);
           	  }
           	  printf("%s = 0;\n", variable);

           	  for(int i = 0; i < indentation; i++){
           	  	printf("%s", tab);
           	  }

           	  printf("}\n");

           	  for(int i = 0; i < indentation; i++){
           	  	printf("%s", tab);
           	  }
           	  printf("else{\n");

           	  for(int i = 0; i < indentation + 1; i++){
           	  	printf("%s", tab);
           	  }
           	  printf("printf(\"undefined boolean value\\n\");\n");
           	  for(int i = 0; i < indentation + 1; i++){
           	  	printf("%s", tab);
           	  }
           	  printf("exit(1);\n");

           	  for(int i = 0; i < indentation; i++){
           	  	printf("%s", tab);
           	  }

           	  printf("}\n");

           }
            else if(typeK == k_typeString || strcmp(type1, "string") == 0){
			  printf("scanf(\"%s\", %s);\n", str, variable);
		    }
		    else{
			  printf("scanf(\"%s\", &%s);\n", str, variable);
		    }
		    codeGenerate(statement->next, table,  indentation);
		    
		    break;
		}
		case k_statementKindIfStatement:
		    printf("if(");
		    prettyEXP(statement->val.ifStatement.conditionExpression);
		    printf("){\n");
		    codeGenerate(statement->val.ifStatement.body, table, indentation + 1);
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
		    	codeGenerate(statement->val.ifStatement.presentStatement, table , indentation);
		    }


		    	//else body
		    
		    if(statementPresent != NULL && strcmp(statement->val.ifStatement.present, "else") == 0 ){
		    	STATEMENT * elseStatement = statement->val.ifStatement.presentStatement;
		    	for(int i = 0; i < indentation; i++ ) {
		    		printf("%s", tab);
		        }
		    	printf("else {\n");
		    	codeGenerate(elseStatement, table,  indentation + 1);

		    	for(int i = 0; i < indentation; i++ ) {
		    		printf("%s", tab);
		        }
		    	printf("}\n");

		    }

		    codeGenerate(statement->next, table, indentation);
			break;
		case k_statementKindWhileStatement:
		    printf("while("); prettyEXP(statement->val.whileStatement.conditionExpression); printf("){\n");
		    STATEMENT * st = statement->val.whileStatement.body;
		    
		    codeGenerate(st, table,  indentation + 1); //indent by 1 space
		    	
		    for(int i = 0; i < indentation; i++){
		    	printf("%s", tab);
		    }
		    printf("}\n");
		    
		    codeGenerate(statement->next, table,  indentation);
		    
		    break;
	}
}