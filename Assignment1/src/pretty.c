#include "pretty.h"



void pretty_print(STATEMENT * statement , int indentation){ // 1  = in body means its in if body or while body; 0 = means its not

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
        	
		    pretty_print(statement->next, indentation);
		    
		    break;
	    case k_statementKindDeclaration:
	    	printf("var %s : %s\n", statement->val.declaration.identifier, statement->val.declaration.type);
		   
		    pretty_print(statement->next , indentation);
		    
		    break;
	    case k_statementKindInitialisation:
	    	printf("var %s : %s = ", statement->val.initialisation.identifier, statement->val.initialisation.type); prettyEXP(statement->val.initialisation.expression); printf(";\n");
		    
		    pretty_print(statement->next, indentation);
		    
		    break;
		case k_statementKindPrintStatement:
			printf("print("); prettyEXP(statement->val.print); printf("); \n");
		    
		    pretty_print(statement->next, indentation);
		    
		    break;
		case k_statementKindReadStatement:
		    printf("read(%s);\n", statement->val.read);
		    
		    pretty_print(statement->next, indentation);
		    
		    break;
		case k_statementKindIfStatement:
		    printf("if(");
		    prettyEXP(statement->val.ifStatement.conditionExpression);
		    printf("){\n");
		    pretty_print(statement->val.ifStatement.body, indentation + 1);
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
		    	pretty_print(statement->val.ifStatement.presentStatement, indentation);
		    }


		    	//else body
		    
		    if(statementPresent != NULL && strcmp(statement->val.ifStatement.present, "else") == 0 ){
		    	STATEMENT * elseStatement = statement->val.ifStatement.presentStatement;
		    	for(int i = 0; i < indentation; i++ ) {
		    		printf("%s", tab);
		        }
		    	printf("else {\n");
		    	pretty_print(elseStatement, indentation + 1);

		    	for(int i = 0; i < indentation; i++ ) {
		    		printf("%s", tab);
		        }
		    	printf("}\n");

		    }

		    pretty_print(statement->next, indentation);
			break;
		case k_statementKindWhileStatement:
		    printf("while("); prettyEXP(statement->val.whileStatement.conditionExpression); printf("){\n");
		    STATEMENT * st = statement->val.whileStatement.body;
		    
		    pretty_print(st, indentation + 1); //indent by 1 space
		    	
		    for(int i = 0; i < indentation; i++){
		    	printf("%s", tab);
		    }
		    printf("}\n");
		    
		    pretty_print(statement->next, indentation);
		    
		    break;

	}
}

void prettyEXP(EXP *e){
	switch (e->kind) {
		case k_expressionKindIdentifier:
			printf("%s", e->val.identifier);
			break;
		case k_expressionKindIntLiteral:
			printf("%i", e->val.intLiteral);
			break;
	    case k_expressionKindFloatLiteral:
	    	printf("%f", e->val.floatLiteral);
			break;
	    case k_expressionKindBooleanLiteral:
	         printf("%s", e->val.booleanLiteral);
	         break;
	    case k_expressionKindStringLiteral:
	         printf("\"%s\"", e->val.stringLiteral);
	         break;
		case k_expressionKindAddition:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" + ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case k_expressionKindSubtraction:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" - ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case k_expressionKindMultiplication:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" * ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case k_expressionKindDivision:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" / ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case k_expressionKindBooleanAnd: 
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" && ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case k_expressionKindBooleanOr:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" || ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case k_expressionKindGreaterThan:
		    printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" > ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
	    case k_expressionKindLessThan:
	    	printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" < ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case k_expressionKindDoubleEquals:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" == ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
	    case k_expressionKindNotEqualTo:
	    	printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" != ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case k_expressionKindUnaryMinus:
		    printf("(-");
		    prettyEXP(e->val.binary.lhs);
		    printf(")");
		    break;
	    case k_expressionKindUnaryNegate:
	        printf("(!");
		    prettyEXP(e->val.binary.lhs);
		    printf(")");
		    break;
	    case k_expressionKindLessThanOrEqualTo:
	        printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" <= ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
	    case k_expressionKindGreaterThanOrEqualTo:
	        printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(" >= ");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
	}

}