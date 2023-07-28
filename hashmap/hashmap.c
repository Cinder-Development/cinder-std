/* Copyright (C) 2023 Cinder Development.
   This file is part of the Cinder Standard Library and
   was written by ephf 2023.

   This project is licensed under the MIT License.
   See the LICENSE file for details */

#include "hashmap.h"

int hmhash(char* key, int capacity) {
    int n = 17;
    for(; *key; key++) n = (n * (*key) * 3) % capacity + 1;
    return (n < 0 ? -n : n) - 1;
}

hashmap_t hmnew(int capacity, int resize_requirement) {
    hashmap_t map = _vnew(sizeof(void*) * 2, capacity);
    if(!map) return NULL;
    for(int i = 0; i < capacity; i++) {
        map[i * 2] = NULL;
        map[i * 2 + 1] = map + i * 2;
    }
    vmeta(map)->unit_size = resize_requirement;
    return map;
}

int _hminsert(hashmap_t map, char* key, void* value, int value_size) {
    linked_list_t link = malloc(sizeof(void*) * 2 + value_size);
    if(!link) return 1;
    link[0] = NULL; link[1] = key; memcpy(link + 2, value, value_size);
    linked_list_t anchor = map + hmhash(key, vmeta(map)->capacity) * 2;
    ((linked_list_t) anchor[1])[0] = link;
    anchor[1] = link;
    return 0;
}

void* _hmget(hashmap_t map, char* key) {
    llforeach(map + hmhash(key, vmeta(map)->capacity) * 2, char** ckey, { if(!strcmp(*ckey, key)) { return (void*) (ckey + 1); } });
    return NULL;
}

int hmremove(hashmap_t map, char* key) {
    linked_list_t anchor = map + hmhash(key, vmeta(map)->capacity) * 2, prev = anchor;
    llforeach(anchor, char** ckey, { if(!strcmp(*ckey, key)) { llremove(prev, (void*) (ckey - 1)); return 1; } else prev = (void**) ckey - 1; });
    return 0;
}

void hmfree(hashmap_t map) {
    for(int i = 0; i < vmeta(map)->capacity; i++) llforeach(map + i * 2, void** optr, free(optr - 1));
    vfree(map);
}