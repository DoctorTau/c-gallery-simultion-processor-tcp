#ifndef VECTOR_STRUCT_H
#define VECTOR_STRUCT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct vector {
    int size;
    int capacity;
    int *data;
} vector;

void vector_initialize(vector *vec, int capacity);
void vector_push_back(vector *vec, int value);
void vector_pop_back(vector *vec);
void vector_clear(vector *vec);
void vector_destroy(vector *vec);
void vector_erase(vector *vec, int value);

#endif
