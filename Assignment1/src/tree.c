#include "tree.h"




EXP * makeIdentifierExpression(char * identifier){
	EXP * expression = malloc(sizeof(EXP));
	expression->kind = k_expressionKindIdentifier;
	expression->val.identifier = identifier;

    return expression;
}
EXP * makeIntLiteralExpression( int intLiteral){
	EXP * expression = malloc(sizeof(EXP));
	expression->kind = k_expressionKindIntLiteral;
	expression->val.intLiteral = intLiteral;

    return expression;
}
EXP * makeFloatLiteralExpression(float  floatLiteral){
	EXP * expression = malloc(sizeof(EXP));
	expression->kind = k_expressionKindFloatLiteral;
	expression->val.floatLiteral = floatLiteral;

    return expression;
}
EXP * makeBooleanLiteralExpression(char * booleanLiteral){
	EXP * expression = malloc(sizeof(EXP));
	expression->kind = k_expressionKindBooleanLiteral;
	expression->val.booleanLiteral = booleanLiteral;

    return expression;

} 
EXP * makeStringLiteralExpression(char * stringLiteral){
	EXP * expression = malloc(sizeof(EXP));
	expression->kind = k_expressionKindStringLiteral;
	expression->val.stringLiteral = stringLiteral;

    return expression;
} 

EXP * makeExpressionFromOperations( EXP * leftHandSideExp, EXP * rightHandSideExp, ExpressionKind kind){
	EXP * expression = malloc(sizeof(EXP));
	expression->kind = kind;
	expression->val.binary.lhs = leftHandSideExp;
	expression->val.binary.rhs = rightHandSideExp;

    return expression;
}
//===========================================STATEMENT===============================================================================

STATEMENT * initialisationStatement(char * identifier, char * type, EXP * expression){
     STATEMENT * statement = malloc(sizeof(STATEMENT));
     statement->kind = k_statementKindInitialisation;
     statement->val.initialisation.type = type;
     statement->val.initialisation.identifier = identifier;
     statement->val.initialisation.expression = expression;
     
     return statement;

}
STATEMENT * declarationStatement(char * identifier, char * type){
	 STATEMENT * statement = malloc(sizeof(STATEMENT));
     statement->kind = k_statementKindDeclaration;
     statement->val.declaration.type = type;
     statement->val.declaration.identifier = identifier;
     
     return statement;

}
STATEMENT * assignmentStatement(char * identifier, EXP * expression){
	 STATEMENT * statement = malloc(sizeof(STATEMENT));
     statement->kind = k_statementKindAssignment;
     statement->val.assignment.identifier = identifier;
     statement->val.assignment.expression = expression;
     
     return statement;


}
STATEMENT * printStatement(EXP * expression){
	 STATEMENT * statement = malloc(sizeof(STATEMENT));
     statement->kind = k_statementKindPrintStatement;
     statement->val.print = expression;
     
     return statement;

}
STATEMENT * readStatement(char * variable){
	 STATEMENT * statement = malloc(sizeof(STATEMENT));
     statement->kind = k_statementKindReadStatement;
     statement->val.read = variable;
     
     return statement;

}
STATEMENT * ifStatementCreation(EXP * expressionCondition, STATEMENT * body){
     STATEMENT * statement = malloc(sizeof(STATEMENT));
     statement->kind = k_statementKindIfStatement;
     statement->val.ifStatement.conditionExpression = expressionCondition;
     statement->val.ifStatement.body = body;

     return statement;
}

STATEMENT * ifStatementCreation2(EXP * expressionCondition, STATEMENT * body, STATEMENT * elseBody){
     STATEMENT * statement = malloc(sizeof(STATEMENT));
     statement->kind = k_statementKindIfStatement;
     statement->val.ifStatement.conditionExpression = expressionCondition;
     statement->val.ifStatement.body = body;
     statement->val.ifStatement.present = "else";
     statement->val.ifStatement.presentStatement = elseBody;

     return statement;

}

STATEMENT * ifStatementCreation3(EXP * expressionCondition, STATEMENT * body, STATEMENT * elseIfStatement){
     STATEMENT * statement = malloc(sizeof(STATEMENT));
     statement->kind = k_statementKindIfStatement;
     statement->val.ifStatement.conditionExpression = expressionCondition;
     statement->val.ifStatement.body = body;
     statement->val.ifStatement.present = "elseIf";
     statement->val.ifStatement.presentStatement = elseIfStatement;

     return statement;
}
STATEMENT * whileStatementCreation(EXP * expressionCondition, STATEMENT * body){
    STATEMENT * statement = malloc(sizeof(STATEMENT));
     statement->kind = k_statementKindWhileStatement;
     statement->val.whileStatement.conditionExpression = expressionCondition;
     statement->val.whileStatement.body = body;
     
     return statement;

}

