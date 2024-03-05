/*
Group Number - 10
ID:	2021A7PS1463P			Name: Dhyey Italiya
ID:	2021A7PS2434P			Name: LAKSHIT SETHI
ID:	2021A7PS0523P			Name: Abir Abhyankar 
ID:	2021A7PS2414P			Name: Saksham Verma
ID:	2021A7PS2412P			Name: Saurabh Bhandari
*/

#ifndef PARSER_H
#define PARSER_H
#include "utils.h"
#include "lexerDef.h"
#include "parserDef.h"

// Function to add a rule to the grammer
void add_grammer_rule(grammer *G, int start_variable, int no_of_tokens, int *ptokens);

// Function to initialize the grammer
void grammer_init(grammer *G);

// Function to compute first and follow sets
FirstAndFollow ComputeFirstAndFollowSets(grammer G);

// Function to create parse table
bool createParseTable(FirstAndFollow F, table *T);

// Function to parse the input source code
parseTree *parseInputSourceCode(table T, FirstAndFollow F, grammer *G, vector input);

// Function to print the parse tree
void printParseTree(parseTree *ptree, FILE *fp);
#endif