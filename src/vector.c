#include "vector.h"

void vector_initialize(vector *vec, int capacity) {
    vec->size = 0;
    vec->capacity = capacity;
    vec->data = malloc(capacity * sizeof(int));
}

void vector_push_back(vector *vec, int value) {
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        vec->data = realloc(vec->data, vec->capacity * sizeof(int));
    }
    vec->data[vec->size++] = value;
}

void vector_pop_back(vector *vec) {
    if (vec->size > 0) {
        vec->size--;
    }
}

void vector_clear(vector *vec) {
    vec->size = 0;
}

void vector_destroy(vector *vec) {
    free(vec->data);
    free(vec);
}

void vector_erase(vector *vec, int value) {
    int i, j;
    for (i = 0, j = 0; i < vec->size; i++) {
        if (vec->data[i] != value) {
            vec->data[j++] = vec->data[i];
        }
    }
    vec->size = j;
}