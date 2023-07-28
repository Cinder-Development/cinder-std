/* Copyright (C) 2023 Cinder Development.
   This file is part of the Cinder Standard Library and
   was written by ephf 2023.

   This project is licensed under the MIT License.
   See the LICENSE file for details */

#include <string.h>
#include <stdlib.h>

#include "../iterator/iterator.h"

#ifndef VECTOR_H
#define VECTOR_H

/* Type for vector */
#define vector_t(type) type*
/* Type for vector */
#define Vector(type) vector_t(type)

/* Default type for vector */
typedef vector_t(void) vector_t;
/* Default type for vector */
typedef vector_t Vector;

/* Meta data stored before a vector pointer */
typedef struct {
    int capacity;   
    int unit_size;  
    int size;       
} vector_meta_t;
/* Meta data stored before a vector pointer */
typedef vector_meta_t VectorMeta;

/* Allocates memory for a new vector which elements are the size of `unit_size`
Use `vnew(type, int capacity)` for ease

DYNAMIC ALLOCATION use `vfree(vector_t vector)` */
vector_t _vnew(size_t unit_size, int capacity);
/* Allocates memory for a new vector which elements are of `type`

DYNAMIC ALLOCATION use `vfree(vector_t vector)` */
#define vnew(type, capacity) _vnew(sizeof(type), capacity)
/* Allocates memory for a new vector which elements are the size of `unit_size`
Use `newVector(type, int capacity)` for ease

DYNAMIC ALLOCATION use `freeVector(Vector vector)` */
#define _newVector(unit_size, capacity) _vnew(unit_size, capacity)
/* Allocates memory for a new vector which elements are of `type`

DYNAMIC ALLOCATION use `freeVector(Vector vector)` */
#define newVector(type, capacity) vnew(type, capacity)

/* Gets the meta data of vector `vector` */
#define vmeta(vector) ((vector_meta_t*) (vector) - 1)
/* Gets the meta data of vector `vector` */
#define vectorMeta(vector) vmeta(vector)

/* Gets the size of a vector */
#define vsize(vector) (vmeta(vector)->size)
/* Gets the size of a vector */
#define vectorSize(vector) vsize(vector)

/* Resizes vector `vector` to the given capacity `capacity`
Use `vresize(vector_t vector, int capacity)` for ease */
int _vresize(vector_t* vector, int capacity);
/* Resizes vector `vector` to the given capacity `capacity` */
#define vresize(vector, capacity) _vresize((vector_t) &(vector), capacity)
/* Resizes vector `vector` to the given capacity `capacity`
Use `resizeVector(Vector vector, int capacity)` for ease */
#define _resizeVector(vector, capacity) _vresize(vector, capacity)
/* Resizes vector `vector` to the given capacity `capacity` */
#define resizeVector(vector, capacity) vresize(vector, capacity)

/* Pushes a value `item` to the end of vector `vector`
Use `vpush(vector_t vector, any item)` for ease */
int _vpush(vector_t* vector, void* item);
/* Pushes a value `item` to the end of vector `vector` */
#define vpush(vector, item) _vpush((vector_t*) &(vector), (void*) ({ typeof(item) $ = item; &$; }))
/* Pushes a value `item` to the end of vector `vector`
Use `pushVector(Vector vector, Any item)` for ease */
#define _pushVector(vector, item) _vpush(vector, item)
/* Pushes a value `item` to the end of vector `vector` */
#define pushVector(vector, item) vpush(vector, item)

/* Pops a value from the end of vector `vector` */
void vpop(vector_t vector);
/* Pops a value from the end of vector `vector` */
#define popVector(vector) vpop(vector)

/* Puts a value `item` at the beginning of vector `vector`, then shifts the remaining items down
Use `vunshift(vector_t vector, any item)` for ease */
int _vunshift(vector_t* vector, void* item);
/* Puts a value `item` at the beginning of vector `vector`, then shifts the remaining items down */
#define vunshift(vector, item) _vunshift((vector_t*) &(vector), (void*) ({ typeof(item) $ = item; &$; }))
/* Puts a value `item` at the beginning of vector `vector`, then shifts the remaining items down
Use `unshiftVector(Vector vector, Any item)` for ease */
#define _unshiftVector(vector, item) _vunshift(vector, item)
/* Puts a value `item` at the beginning of vector `vector`, then shifts the remaining items down */
#define unshiftVector(vector, item) vunshift(vector, item)

/* Removes the first item of vector `vector`, then shifts the remaining items down */
void vshift(vector_t vector);
/* Removes the first item of vector `vector`, then shifts the remaining items down */
#define shiftVector(vector) vshift(vector)

/* Frees vector `vector` */
void vfree(vector_t vector);
/* Frees vector `vector` */
#define freeVector(vector) vfree(vector)

// TODO: vforeach, viter

#endif 