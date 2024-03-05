/*
Group Number - 10
ID:	2021A7PS1463P			Name: Dhyey Italiya
ID:	2021A7PS2434P			Name: LAKSHIT SETHI
ID:	2021A7PS0523P			Name: Abir Abhyankar 
ID:	2021A7PS2414P			Name: Saksham Verma
ID:	2021A7PS2412P			Name: Saurabh Bhandari
*/

#ifndef VECTOR_H
#define VECTOR_H
#define VECTOR_INCOMPLETE
#include "lexerDef.h"

typedef struct Vector
{
    token *data;
    int size;
    int capacity;
} Vector;

typedef Vector *vector;

// Initializes a vector
vector init_vector();

// Pushes data to the end of the vector
void push_back(vector v, token data);

// Returns the element at index i
token get(vector v, int index);
#undef VECTOR_INCOMPLETE
#endif