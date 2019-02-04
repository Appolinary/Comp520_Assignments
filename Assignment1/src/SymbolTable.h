#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include "tree.h"

#define HashSize 317



typedef enum {
	k_symbolKindAssignment,
	k_symbolKindDeclaration,
	k_symbolKindInitialisation,
	k_symbolKindPrintStatement,
	k_symbolKindReadStatement,
}SymbolKind;


typedef struct Symbol  Symbol;
typedef struct SymbolData SymbolData;

typedef struct Symbol{
	SymbolKind kind;
    char * name;
    SymbolData * data;
    Symbol * next;
}Symbol;


typedef struct SymbolTable{
	Symbol *table[HashSize];
	struct SymbolTable * parent;
}SymbolTable;

typedef struct AssignmentSymbol{
	char * identifier;
	EXP * expressionValue;
}AssignmentSymbol;

typedef struct DeclarationSymbol{
	char * identifier;
	char * type;
}DeclarationSymbol;

typedef struct InitialisationSymbol{
	char * identifier;
	char * type;
	EXP * expressionValue;
}InitialisationSymbol;

typedef struct PrintSymbol{
	EXP * expressionValue;
}PrintSymbol;

typedef struct ReadSymbol{
	EXP * expressionValue;
}ReadSymbol;


typedef struct SymbolData {
	union {
	AssignmentSymbol * assignmentSymbol;
    DeclarationSymbol * declarationSymbol;
    InitialisationSymbol * initialisationSymbol;
    PrintSymbol * printSymbol;
    ReadSymbol * readSymbol;
   }data;
}SymbolData;


int hash(char * name);
SymbolTable * initSymbolTable();
SymbolTable * scopeSymbolTable(SymbolTable * table);
SymbolTable * unscopeSymbolTable(SymbolTable * table);
Symbol * putSymbol(SymbolTable * table, char * name, SymbolKind kind, SymbolData * data);
Symbol * getSymbol(SymbolTable * table, char * name);

void validateSymbols(STATEMENT * root, SymbolTable * table);

void checkInitialisationValidity(STATEMENT * statment, SymbolTable * table);
void checkDeclarationValidity(STATEMENT * statment, SymbolTable * table);
void checkAssignmentValidity(STATEMENT * statment, SymbolTable * table);
void checkPrintValidity(STATEMENT * statment, SymbolTable * table);
void checkReadValidity(STATEMENT * statment, SymbolTable * table);


#endif