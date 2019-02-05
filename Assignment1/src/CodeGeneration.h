#ifndef _CODE_GENERATION_H_
#define _CODE_GENERATION_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pretty.h"
#include "SymbolTable.h"
#include "tree.h"


void codeGenerate(STATEMENT * statement , int indentation);


#endif