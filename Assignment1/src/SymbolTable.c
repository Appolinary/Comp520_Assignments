#include "SymbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int hash(char * name){
	unsigned int hash = 0;
   while (*name) hash = (hash << 1) + *name++;

   return hash % HashSize;
}
SymbolTable * initSymbolTable(){
	SymbolTable * t = malloc(sizeof(SymbolTable));
    for (int i = 0; i < HashSize; i++) {
        t->table[i] = NULL;
    }
    t->parent = NULL;
    return t;
}
SymbolTable * scopeSymbolTable(SymbolTable * table){
   SymbolTable * t = initSymbolTable();
   t->parent = table;
   return t;
}
SymbolTable * unscopeSymbolTable(SymbolTable * table){
    
     SymbolTable * parent = table->parent;

     table = NULL;


     return parent;


}
Symbol * putSymbol(SymbolTable * table, char * name, SymbolKind kind, SymbolData * data){
    	int i = hash(name);
        for (Symbol*s = table->table[i]; s; s = s->next) {
             if (strcmp(s->name, name) == 0) {

             }
        }
        Symbol*s = malloc(sizeof(Symbol));
        s->name = name;
       s->kind = kind;
       s->data = data;
       s->next = table->table[i];
       table->table[i] = s;

       return s;

}
Symbol * getSymbol(SymbolTable * table, char * name){
    int i = hash(name);
    // Check the current scope
   for (Symbol*s = table->table[i]; s; s = s->next) {
        if (strcmp(s->name, name) == 0) return s;
   }
   // Check for existence of a parent scope
   if (table->parent == NULL)
        return NULL;

    // Check the parent scopes
    return getSymbol(table->parent, name);

}

void validateSymbols(STATEMENT * root, SymbolTable * table){

    if(root == NULL){
        return;
    }

    /*if the statement is an if else statement, else if statement, else statement
     or a while statement then create a new scope*/
    if(root->kind == k_statementKindIfStatement){
        SymbolTable * newScope = scopeSymbolTable(table);

        //and then call the same statement for the body;
        validateSymbols(root->val.ifStatement.body, newScope);
    }

    if(root->kind == k_statementKindWhileStatement){
        SymbolTable * newScope = scopeSymbolTable(table);

        validateSymbols(root->val.whileStatement.body, newScope);
    }

    //if its an initialisation then check if it is valid
    if(root->kind == k_statementKindInitialisation){
        checkInitialisationValidity(root, table);  //check if its valid and that the variable hasnt been defined already
    }

    //check its valid and that the variable has been defined already with the right type as the expression
    if(root->kind == k_statementKindAssignment){
        checkAssignmentValidity(root, table); 
    }

    //check if its valid and that the variable hasnt been defined already
    if(root->kind == k_statementKindDeclaration){
        checkDeclarationValidity(root, table);
    }

    if(root->kind == k_statementKindPrintStatement){
        checkPrintValidity(root, table);
    }

    if(root->kind == k_statementKindReadStatement){
        checkReadValidity(root, table);
    }

    validateSymbols(root->next, table);


}

void checkInitialisationValidity(STATEMENT * statment, SymbolTable * table){

    //check if its been declared first ie already in the table;
    char * identifier =  statment->val.initialisation.identifier;

    Symbol * symbol = getSymbol(table, identifier);

    if(symbol){
        printf("The variable %s has already been defined\n", identifier);
    }else{
        //then we need to put the symbol into the table
        SymbolData * data = malloc(sizeof(SymbolData));
        InitialisationSymbol * init = malloc(sizeof(InitialisationSymbol));
        init->type = statment->val.initialisation.type;
        init->identifier = statment->val.initialisation.identifier;
        init->expressionValue = statment->val.initialisation.expression;
        data->data.initialisationSymbol =  init;
        putSymbol(table, identifier, k_symbolKindInitialisation, data);
    }
}


void checkDeclarationValidity(STATEMENT * statment, SymbolTable * table){

    char * identifier = statment->val.declaration.identifier;

    Symbol * symbol = getSymbol(table, identifier);

    if(symbol){
        printf("The variable %s has already been defined\n", identifier);
    }else{
         //then we need to put the symbol into the table
        SymbolData * data = malloc(sizeof(SymbolData));
        DeclarationSymbol * init = malloc(sizeof(DeclarationSymbol));
        init->type = statment->val.declaration.type;
        init->identifier = statment->val.declaration.identifier;
        data->data.declarationSymbol =  init;
        putSymbol(table, identifier, k_symbolKindDeclaration, data);

    }

}

void checkAssignmentValidity(STATEMENT * statment, SymbolTable * table){

    char * identifier = statment->val.assignment.identifier;

    Symbol * symbol = getSymbol(table, identifier);

    if(symbol == NULL){
        printf("The variable %s has not been defined yet \n", identifier);
    }else{

        //first check if there are the same type :TODO


         //then we need to put the symbol into the table
        SymbolData * data = malloc(sizeof(SymbolData));
        AssignmentSymbol  * init = malloc(sizeof(AssignmentSymbol));
        init->expressionValue = statment->val.assignment.expression;
        init->identifier = statment->val.assignment.identifier;
        data->data.assignmentSymbol =  init;
        putSymbol(table, identifier, k_symbolKindAssignment, data);

    }

}

void checkPrintValidity(STATEMENT * statment, SymbolTable * table){

}
void checkReadValidity(STATEMENT * statment, SymbolTable * table){

}
