#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
	k_expressionKindIdentifier,
	k_expressionKindIntLiteral,
	k_expressionKindFloatLiteral,
	k_expressionKindBooleanLiteral,
	k_expressionKindStringLiteral,
	k_expressionKindAddition,
	k_expressionKindSubtraction,
	k_expressionKindMultiplication,
	k_expressionKindDivision,
	k_expressionKindDoubleEquals,
	k_expressionKindLessThanOrEqualTo,
	k_expressionKindLessThan,
	k_expressionKindGreaterThanOrEqualTo,
	k_expressionKindGreaterThan,
	k_expressionKindNotEqualTo,
	k_expressionKindBooleanAnd,
	k_expressionKindBooleanOr,
	k_expressionKindUnaryMinus,
	k_expressionKindUnaryNegate,
	
}ExpressionKind;


typedef struct EXP EXP;

struct EXP {
	int lineno;
	ExpressionKind kind; // - or + or / or <= or >= etc
	union {
		char * identifier;
		int intLiteral;
		float floatLiteral;
		char *  booleanLiteral; // true or false
		char * stringLiteral;
		struct { EXP * lhs; EXP * rhs; } binary;
	} val;
};
//===================================================================================================END-OF-EXPRESSION=====================================

typedef enum {
	k_statementKindAssignment,
	k_statementKindDeclaration,
	k_statementKindInitialisation,
	k_statementKindPrintStatement,
	k_statementKindReadStatement,
	k_statementKindIfStatement,
	k_statementKindWhileStatement
}StatementKind;


typedef struct STATEMENT STATEMENT;
typedef struct ifStatement ifStatement;



struct STATEMENT{
	StatementKind kind;
	int lineno;

	union{
		char * read;
		struct {char * identifier; char *type;}declaration;
		EXP * print;
		struct {char * type; char * identifier; EXP * expression;}initialisation;
		struct {char * identifier; EXP * expression;}assignment;
		struct {
			EXP * conditionExpression; 
			STATEMENT * body;
			
			char * present; //could either be else or elseIf
			STATEMENT * presentStatement;
			
		}ifStatement;
	    struct {EXP * conditionExpression; STATEMENT * body;}whileStatement;

	} val;
    
    STATEMENT * next;

};



EXP * makeIdentifierExpression(char * identifier);
EXP * makeIntLiteralExpression( int intLiteral);
EXP * makeFloatLiteralExpression(float  floatLiteral);
EXP * makeBooleanLiteralExpression(char * booleanLiteral); // true or false only
EXP * makeStringLiteralExpression(char * stringLiteral); //the string including the qotes surrounding it
EXP * makeExpressionFromOperations( EXP * leftHandSideExp, EXP * rightHandSideExp, ExpressionKind kind);

//==============================================FOR STATEMENTS================================================================
STATEMENT * initialisationStatement(char * identifier, char * type, EXP * expression);
STATEMENT * declarationStatement(char * identifier, char * type);
STATEMENT * assignmentStatement(char * identifier, EXP * expression);
STATEMENT * printStatement(EXP * expression);
STATEMENT * readStatement(char * variable);
STATEMENT * ifStatementCreation(EXP * expressionCondition, STATEMENT * body);
STATEMENT * ifStatementCreation2(EXP * expressionCondition, STATEMENT * body, STATEMENT * elseBody);
STATEMENT * ifStatementCreation3(EXP * expressionCondition, STATEMENT * body, STATEMENT * elseIfStatement);
STATEMENT * whileStatementCreation(EXP * expressionCondition, STATEMENT * body);



#endif


