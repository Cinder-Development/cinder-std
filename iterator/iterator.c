/* Copyright (C) 2023 Cinder Development.
   This file is part of the Cinder Standard Library and
   was written by ephf 2023.

   This project is licensed under the MIT License.
   See the LICENSE file for details */

#include "iterator.h"

void* __iter_default_next(iterator_t* iter) {
    if(iter->state - iter->data >= iter->unit_size * iter->size) return NULL;
    void* next = iter->state;
    iter->state += iter->unit_size;
    return next;
}