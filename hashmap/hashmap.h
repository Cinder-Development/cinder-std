/* Copyright (C) 2023 Cinder Development.
   This file is part of the Cinder Standard Library and
   was written by ephf 2023.

   This project is licensed under the MIT License.
   See the LICENSE file for details */

#include "../linked_list/linked_list.h"
#include "../vector/vector.h"

#include <stdlib.h>

#ifndef HASHMAP_H
#define HASHMAP_H

/* Type for hash map */
#define hashmap_t(type) vector_t(void*)
/* Type for hash map */
#define HashMap(type) Vector(type)

/* Default type for hash map */
typedef hashmap_t(void) hashmap_t;
/* Default type for hash map */
typedef HashMap(void) HashMap;

/* Converts string `key` into a number 0 - `capacity` */
int hmhash(char* key, int capacity);
/* Converts string `key` into a number 0 - `capacity` */
#define hashmapHash(key, capacity) hmhash(key, capacity)

/* Creates a new hashmap with capacity `capacity` and a resize requirement `resize_requirement`

DYNAMIC ALLOCATION use `hmfree(hashmap_t map)` */
hashmap_t hmnew(int capacity, int resize_requirement);
/* Creates a new hashmap with capacity `capacity` and a resize requirement `resize_requirement`

DYNAMIC ALLOCATION use `freeHashmap(HashMap map)` */
#define newHashmap(capacity, resize_requirement) hmnew(capacity, resize_requirement)

/* Inserts an element `value` into hash map `map` at key `key`
Use `hminsert(hashmap_t map, char* key, any value)` for ease */
int _hminsert(hashmap_t map, char* key, void* value, int value_size);
/* Inserts an element `value` into hash map `map` at key `key` */
#define hminsert(map, key, value) _hminsert((hashmap_t) map, key, (void*) ({ typeof(value) $ = value; &$; }), sizeof(value))
/* Inserts an element `value` into hash map `map` at key `key`
Use `hashmapInsert(HashMap map, char* key, any value)` for ease */
#define _hashmapInsert(map, key, value, value_size) _hminsert(map, key, value, value_size)
/* Inserts an element `value` into hash map `map` at key `key` */
#define hashmapInsert(map, key, value) hminsert(map, key, value)

/* Gets the element at key `key` from hash map `map`
Use `hmget(hashmap_t map, char* key, type, type if_null)` for ease */
void* _hmget(hashmap_t map, char* key);
/* Gets the element at key `key` from hash map `map` or value `if_null` if value does not exist in the map */
#define hmget(map, key, type, if_null) ({ type* __value = _hmget((hashmap_t) map, key); (__value ? *__value : (if_null)); })
/* Gets the element at key `key` from hash map `map`
Use `hashmapGet(HashMap map, char* key, type, type if_null)` for ease */
#define _hashmapGet(map, key) _hmget(map, key)
/* Gets the element at key `key` from hash map `map` or value `if_null` if value does not exist in the map */
#define hashmapGet(map, key, type, if_null) hmget(map, key, type, if_null)

/* Removes the element at key `key` from hash map `map` */
int hmremove(hashmap_t map, char* key);
/* Removes the element at key `key` from hash map `map` */
#define removeFromHashmap(map, key) hmremove(map, key)

/* Frees hash map `map` */
void hmfree(hashmap_t map);
/* Frees hash map `map` */
#define freeHashmap(map) hmfree(map)

// TODO: map resizing, entries

#endif