#include "vector.h"

// Initializes a vector
vector init_vector()
{
    vector v = (vector)malloc(sizeof(Vector));
    v->data = (token *)malloc(sizeof(Token) * 10);
    v->size = 0;
    v->capacity = 10;
    return v;
}

// Pushes data to the end of the vector
void push_back(vector v, token data)
{
    if (v->size == v->capacity)
    {
        v->capacity *= 2;
        v->data = (token *)realloc(v->data, sizeof(Token) * v->capacity);
    }
    v->data[v->size++] = data;
}

// Returns the element at index i
token get(vector v, int i)
{
    return v->data[i];
}