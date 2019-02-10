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

//mode = 0 means in symbol mode, mode = 1 means in typecheck mode
void validateSymbols(STATEMENT * root, SymbolTable * table, int mode, int identation){

    if(root == NULL){
        return;
    }

    char * tab = "   ";
    for(int i = 0; i < identation; i++){
        printf("%s", tab);
    }

    /*if the statement is an if else statement, else if statement, else statement
     or a while statement then create a new scope*/
    if(root->kind == k_statementKindIfStatement){

        //check if the expression right
        EXP * expression = root->val.ifStatement.conditionExpression;
        Type type = getType(expression, table);

        if(mode == 0){
            printf("{\n");
        }

        if(type != k_typeBoolean && mode == 1){
            printf("\nError: The condition in the if statement is not valid\n");
            exit(0);
        }else{

           SymbolTable * newScope = scopeSymbolTable(table);

          //and then call the same statement for the body;
          validateSymbols(root->val.ifStatement.body, newScope, mode, identation + 1);

          if(mode == 0){
             printf("\n");
             for(int i = 0; i < identation; i++){
               printf("%s", tab);
             }
             printf("}\n");
          }

       }
    }

    else if(root->kind == k_statementKindWhileStatement){
        EXP * expression = root->val.whileStatement.conditionExpression;
        Type type = getType(expression, table);

         if(mode == 0){
            printf("{\n");
        }

        if(type != k_typeBoolean && mode == 1){
            printf("\nError: The condition in the while statement is not valid\n");
            exit(0);
        }else{


        SymbolTable * newScope = scopeSymbolTable(table);

        validateSymbols(root->val.whileStatement.body, newScope, mode, identation + 1);

        if(mode == 0){
            printf("\n");
            for(int i = 0; i < identation; i++){
               printf("%s", tab);
             }
             printf("}\n");
        }

      }
    }

    //if its an initialisation then check if it is valid
    else if(root->kind == k_statementKindInitialisation){
        checkInitialisationValidity(root, table, mode, identation);  //check if its valid and that the variable hasnt been defined already
    }

    //check its valid and that the variable has been defined already with the right type as the expression
    else if(root->kind == k_statementKindAssignment){
        checkAssignmentValidity(root, table, mode, identation); 
    }

    //check if its valid and that the variable hasnt been defined already
    else if(root->kind == k_statementKindDeclaration){
        checkDeclarationValidity(root, table, mode, identation);
    }

    else if(root->kind == k_statementKindPrintStatement){
        //only prints an expression or a string variable
         Type type = getType(root->val.print, table);

         if(type == k_typeInvalid && mode == 1){
              printf("\nInvalid expression in the print statement\n");
              exit(0);
         }

    }

    else if(root->kind == k_statementKindReadStatement){
        //get if the symbol has been defined 
        Symbol * symbol = getSymbol(table , root->val.read);

        //if symbol is not defined then return
        if(symbol == NULL && mode == 1){
            printf("\nThe variable %s in the read statement is not defined\n", root->val.read);
            exit(0);
        }

    }

    validateSymbols(root->next, table, mode, identation);


}

void checkInitialisationValidity(STATEMENT * statment, SymbolTable * table, int mode, int identation){

    //check if its been declared first ie already in the table;
    char * identifier =  statment->val.initialisation.identifier;

    Symbol * symbol = getSymbol(table, identifier);

     char * tab = "   ";
    for(int i = 0; i < identation; i++){
        printf("%s", tab);
    }

    if(symbol != NULL && mode == 1){
        printf("\nThe variable %s has already been defined\n", identifier);
        exit(0);
    }else{
        //check if there are the same type
        char * type = statment->val.initialisation.type;
        Type enumType = getType(statment->val.initialisation.expression, table);

        if(enumType == k_typeBoolean && strcmp(type, "boolean") != 0 && mode == 1){
            printf("\nError: cannot assign boolean to a non boolean %s \n ", identifier);
            exit(0);
        }
        if(enumType == k_typeInteger && strcmp(type, "int") != 0  && mode == 1){
            printf("\nError: cannot assign int to a non integer %s \n ", identifier);
            exit(0);
        }
        if(enumType == k_typeString && strcmp(type, "string") != 0 && mode == 1){
            printf("\nError: cannot assign string to a non string %s \n ", identifier);
            exit(0);
        }
        if(enumType == k_typeFloat && strcmp(type, "float") != 0 && mode == 1){
            printf("Error: cannot assign float to a non float %s \n ", identifier);
            exit(0);
        }
        if(enumType == k_typeInvalid && mode == 1){
            printf("\nInvalid expression");
            exit(0);
        }

        //then we need to put the symbol into the table
        SymbolData * data = malloc(sizeof(SymbolData));
        InitialisationSymbol * init = malloc(sizeof(InitialisationSymbol));
        init->type = statment->val.initialisation.type;
        init->identifier = statment->val.initialisation.identifier;
        init->expressionValue = statment->val.initialisation.expression;
        data->data.initialisationSymbol =  init;
        putSymbol(table, identifier, k_symbolKindInitialisation, data);

        char * temE = getStringType(enumType);

        if(mode == 0){
            printf("%s : %s\n", identifier, temE);
        }
    }
}


void checkDeclarationValidity(STATEMENT * statment, SymbolTable * table, int mode, int identation){

    char * identifier = statment->val.declaration.identifier;

    Symbol * symbol = getSymbol(table, identifier);

     char * tab = "   ";
    for(int i = 0; i < identation; i++){
        printf("%s", tab);
    }

    if(symbol && mode == 1){
        printf("\nThe variable %s has already been defined\n", identifier);
    }else{
         //then we need to put the symbol into the table
        SymbolData * data = malloc(sizeof(SymbolData));
        DeclarationSymbol * init = malloc(sizeof(DeclarationSymbol));
        init->type = statment->val.declaration.type;
        init->identifier = statment->val.declaration.identifier;
        data->data.declarationSymbol =  init;
        putSymbol(table, identifier, k_symbolKindDeclaration, data);

        if(mode == 0){
            printf("%s : %s\n", identifier, (statment->val.declaration.type));
        }

    }

}

void checkAssignmentValidity(STATEMENT * statment, SymbolTable * table, int mode , int identation){

    char * identifier = statment->val.assignment.identifier;

    Symbol * symbol = getSymbol(table, identifier);


    if(symbol == NULL && mode == 1){
        printf("\nThe variable %s has not been defined yet \n", identifier);
        exit(0);
    }else{

        //first check if there are the same type :TODO
        Type type = k_typeInvalid;

        if(symbol->kind == k_symbolKindDeclaration){
            if(strcmp(symbol->data->data.declarationSymbol->type, "string") == 0){
                type =  k_typeString;
            }
            if(strcmp(symbol->data->data.declarationSymbol->type, "int") == 0){
                type =  k_typeInteger;
            }
            if(strcmp(symbol->data->data.declarationSymbol->type, "float") == 0){
                type =  k_typeFloat;
            }
            if(strcmp(symbol->data->data.declarationSymbol->type, "boolean") == 0){
                type =  k_typeBoolean;
            }
        }

        if(symbol->kind == k_symbolKindAssignment){
            type = getType(symbol->data->data.assignmentSymbol->expressionValue, table);
        }

        if(symbol->kind == k_symbolKindInitialisation){
            type = getType(symbol->data->data.initialisationSymbol->expressionValue, table);
        }

        if((type != getType(statment->val.assignment.expression, table) || type == k_typeInvalid) && mode == 1){
            printf("\ncannot assign %s of different type to expression\n", identifier);
            exit(0);
        }


         //then we need to put the symbol into the table
        SymbolData * data = malloc(sizeof(SymbolData));
        AssignmentSymbol  * init = malloc(sizeof(AssignmentSymbol));
        init->expressionValue = statment->val.assignment.expression;
        init->identifier = statment->val.assignment.identifier;
        data->data.assignmentSymbol =  init;
        putSymbol(table, identifier, k_symbolKindAssignment, data);

    }

}


Type getType(EXP * exp, SymbolTable * table){

    if(exp->kind == k_expressionKindIdentifier){
        //need to look it up on the symbol table and find out if its defined and return its 
        char * type = malloc(sizeof(char));

        Symbol * symbol = getSymbol(table , exp->val.identifier);

        if(symbol == NULL){
           return k_typeInvalid;
        }


        if(symbol->kind == k_symbolKindAssignment){
            return getType(symbol->data->data.assignmentSymbol->expressionValue, table);
        }
        if(symbol->kind == k_symbolKindDeclaration){
            type  = symbol->data->data.declarationSymbol->type;
        }
        if(symbol->kind == k_symbolKindInitialisation){
            type = symbol->data->data.initialisationSymbol->type;
        }

        if(strcmp(type, "boolean") == 0){
            return k_typeBoolean;
        }
        if(strcmp(type, "int") == 0){
            return k_typeInteger;
        }

        if(strcmp(type, "float") == 0){
            return k_typeFloat;
        }

        if(strcmp(type, "string") == 0){
            return k_typeString;
        }

    }

    if(exp->kind == k_expressionKindStringLiteral){
        return k_typeString;
    }

    if(exp->kind == k_expressionKindBooleanLiteral){
        return k_typeBoolean;
    }

    if(exp->kind == k_expressionKindFloatLiteral){
        return k_typeFloat;
    }

    if(exp->kind == k_expressionKindIntLiteral){
        return k_typeInteger;
    }

    if((exp->kind == k_expressionKindAddition || exp->kind == k_expressionKindMultiplication 
        || exp->kind == k_expressionKindSubtraction || exp->kind == k_expressionKindDivision) &&  getType(exp->val.binary.lhs, table)  == getType(exp->val.binary.rhs, table)){


        Type type = getType(exp->val.binary.lhs, table);   
        if(type == k_typeInteger || type == k_typeFloat){
            return type;
        } 

        return k_typeInvalid;
    }

    if((exp->kind == k_expressionKindAddition || exp->kind == k_expressionKindMultiplication 
        || exp->kind == k_expressionKindSubtraction || exp->kind == k_expressionKindDivision) && getType(exp->val.binary.lhs, table)  != getType(exp->val.binary.rhs, table) ){

        //both sides need to be equal and they have to be either all float or integer
        Type left = getType(exp->val.binary.lhs, table);
        Type right = getType(exp->val.binary.rhs, table);

        if((left == k_typeInteger && right == k_typeFloat) || (right == k_typeFloat && left == k_typeInteger)){
            return k_typeFloat;
        }
        
        return k_typeInvalid;
        
    }

    if( exp->kind == k_expressionKindLessThan || exp->kind == k_expressionKindLessThanOrEqualTo ||
       exp->kind == k_expressionKindGreaterThan || exp->kind == k_expressionKindGreaterThanOrEqualTo){

        //both sides need to be equal and they have to be either all float or integer
        Type left = getType(exp->val.binary.lhs, table);
        Type right = getType(exp->val.binary.rhs, table);

        if(left == right && (left == k_typeInteger || left == k_typeFloat)){
            return k_typeBoolean;
        }else{
            return k_typeInvalid;
        } 
    }

    if( exp->kind == k_expressionKindBooleanOr || exp->kind == k_expressionKindBooleanAnd
         ){

        //both sides need to be equal and they have to be either all float or integer
        Type left = getType(exp->val.binary.lhs, table);
        Type right = getType(exp->val.binary.rhs, table);

        if(left == right && (left == k_typeBoolean)){
            return left;
        }else{
            return k_typeInvalid;
        } 
    }

    if( exp->kind == k_expressionKindDoubleEquals || exp->kind == k_expressionKindNotEqualTo
         ){

        //both sides need to be equal and they have to be either all float or integer
        Type left = getType(exp->val.binary.lhs, table);
        Type right = getType(exp->val.binary.rhs, table);

        if(left == right && (left == k_typeInteger || left == k_typeFloat || left == k_typeBoolean || left == k_typeString)){
            return k_typeBoolean;
        }else{
            return k_typeInvalid;
        } 
    }

    if( exp->kind == k_expressionKindUnaryMinus){

        //both sides need to be equal and they have to be either all float or integer
        Type left = getType(exp->val.binary.lhs, table);

        if((left == k_typeInteger || left == k_typeFloat)){
            return left;
        }else{
            return k_typeInvalid;
        } 
    }


    if( exp->kind == k_expressionKindUnaryNegate){

        //both sides need to be equal and they have to be either all float or integer
        Type left = getType(exp->val.binary.lhs, table);

        if((left == k_typeBoolean)){
            return left;
        }else{
            return k_typeInvalid;
        } 
    }

     return k_typeInvalid;

}
char * getStringType(Type type){
    char * temp =  malloc(sizeof(char));

    if(type == k_typeBoolean){
        temp = "bool";
    }
    else if(type == k_typeString){
        temp = "string";
    }
    else if(type == k_typeFloat){
        temp = "float";
    }
    else if(type == k_typeInteger){
        temp =  "int";
    }else{
        temp = NULL;
    }

    return temp;
}
