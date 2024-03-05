#ifndef VECTOR_H
#define VECTOR_H
#define VECTOR_INCOMPLETE
#include "../lexerDef.h"

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