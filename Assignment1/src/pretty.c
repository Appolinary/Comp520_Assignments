#include "pretty.h"



void pretty_print(STATEMENT * statement){

	switch(statement->kind){

        case k_statementKindAssignment:
        	printf("%s = ", statement->val.assignment.identifier); prettyEXP(statement->val.assignment.expression); printf(";\n");
		    pretty_print(statement->next);
		    break;
	    case k_statementKindDeclaration:
	    	printf("var %s : %s\n", statement->val.declaration.identifier, statement->val.declaration.type);
		    pretty_print(statement->next);
		    break;
	    case k_statementKindInitialisation:
	    	printf("var %s : %s = ", statement->val.initialisation.identifier, statement->val.initialisation.type); prettyEXP(statement->val.initialisation.expression); printf(";\n");
		    pretty_print(statement->next);
		    break;
		case k_statementKindPrintStatement:
			printf("print("); prettyEXP(statement->val.print); printf(") \n");
		    pretty_print(statement->next);
		    break;
		case k_statementKindReadStatement:
		    printf("read(%s)\n", statement->val.read);
		    pretty_print(statement->next);
		    break;
		case k_statementKindIfStatement:
			break;
		case k_statementKindWhileStatement:
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
		case k_expressionKindAddition:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf("+");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case k_expressionKindSubtraction:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf("-");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case k_expressionKindMultiplication:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf("*");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case k_expressionKindDivision:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf("/");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case k_expressionKindBooleanAnd: 
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf("&&");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case k_expressionKindGreaterThan:
		    printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(">");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
	    case k_expressionKindLessThan:
	    	printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(">");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;
		case k_expressionKindDoubleEquals:
			printf("(");
			prettyEXP(e->val.binary.lhs);
			printf(">");
			prettyEXP(e->val.binary.rhs);
			printf(")");
			break;

	}

}