/* Copyright (C) 2023 Cinder Development.
   This file is part of the Cinder Standard Library and
   was written by ephf 2023.

   This project is licensed under the MIT License.
   See the LICENSE file for details */

#include "vector.h"

vector_t _vnew(size_t unit_size, int capacity) {
    vector_meta_t* meta = malloc(sizeof(vector_meta_t) + unit_size * capacity);
    if(!meta) return NULL;
    *meta = (vector_meta_t) { capacity, unit_size, 0 };
    return (vector_t) (meta + 1);
}

int _vresize(vector_t* vector, int capacity) {
    vector_meta_t* meta = vmeta(*vector);
    meta = realloc(meta, sizeof(vector_meta_t) + meta->unit_size * capacity);
    if(meta == NULL) return 1;
    *vector = (vector_t) (meta + 1);
    return 0;
}

int _vpush(vector_t* vector, void* item) {
    vector_meta_t* meta = vmeta(*vector);
    meta->size++;
    if(meta->size > meta->capacity) if(_vresize(vector, meta->capacity * 2)) return 1;
    memcpy(*vector + (meta->size - 1) * meta->unit_size, item, meta->unit_size);
    return 0;
}

void vpop(vector_t vector) {
    vmeta(vector)->size--;
}

int _vunshift(vector_t* vector, void* item) {
    vector_meta_t* meta = vmeta(*vector);
    meta->size++;
    if(meta->size > meta->capacity) if(_vresize(vector, meta->capacity * 2)) return 1;
    memcpy(*vector + meta->unit_size, *vector, meta->unit_size * meta->capacity);
    memcpy(*vector, item, meta->unit_size);
    return 0;
}

void vshift(vector_t vector) {
    vector_meta_t* meta = vmeta(vector);
    meta->size--;
    memcpy(vector, vector + meta->unit_size, meta->unit_size * meta->capacity);
}

void vfree(vector_t vector) {
    free((vector_meta_t*) vector - 1);
}