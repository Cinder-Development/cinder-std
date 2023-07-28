/* Copyright (C) 2023 Cinder Development.
   This file is part of the Cinder Standard Library and
   was written by ephf 2023.

   This project is licensed under the MIT License.
   See the LICENSE file for details */

#include <stdlib.h>
#include <string.h>

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/* Type for linked list */
#define linked_list_t(type) void**
/* Type for linked list */
#define LinkedList(type) void**

/* Default type for linked list */
typedef linked_list_t(void) linked_list_t;
/* Default type for linked list */
typedef LinkedList(void) LinkedList;

/* Allocates memory for a new linked list

DYNAMIC ALLOCATION use `llfree(linked_list_t anchor)` */
linked_list_t llnew();
/* Allocates memory for a new linked list

DYNAMIC ALLOCATION use `freeLinkedList(linked_list_t anchor)` */
#define newLinkedList() llnew()

/* Adds an item `data` after `before`
Use `llappend(linked_list_t before, any data)` for ease */
int _llappend(linked_list_t before, void* data, int data_size);
/* Adds an item `data` after `before` */
#define llappend(before, data) _llappend((linked_list_t) (before), (void*) ({ typeof(data) $ = data; &$; }), sizeof(data))
/* Adds an item `data` after `before`
Use `appendAfterLinkedList(LinkedList before, Any data)` for ease */
#define _appendAfterLinkedList(before, data, data_size) _llappend(before, data, data_size)
/* Adds an item `data` after `before` */
#define appendAfterLinkedList(before, data) llappend(before, data)

/* Adds an item `data` to the end of linked list `anchor`
Use `llpush(linked_list_t anchor, any data)` */
#define _llpush(anchor, data, data_size) ({ int __err = _llappend((linked_list_t) (anchor)[1], data, data_size); (anchor)[1] = ((void**) (anchor)[1])[0]; __err; })
/* Adds an item `data` to the end of linked list `anchor` */
#define llpush(anchor, data) ({ int __err = llappend((anchor)[1], data); (anchor)[1] = ((void**) (anchor)[1])[0]; __err; })
/* Adds an item `data` to the end of linked list `anchor`
Use `pushLinkedList(LinkedList anchor, Any data)` */
#define _pushLinkedList(anchor, data, data_size) _llpush(anchor, data, data_size)
/* Adds an item `data` to the end of linked list `anchor` */
#define pushLinkedList(anchor, data) llpush(anchor, data)

/* Removes a link `item` after `before` */
void llremove(linked_list_t before, linked_list_t item);
/* Removes a link `item` after `before` */
#define removeFromLinkedList(before, item) llremove(before, item)

/* Frees linked list `anchor` */
void llfree(linked_list_t anchor);
/* Frees linked list `anchor` */
#define freeLinkedList(anchor) llfree(anchor)

/* Loops through linked list `anchor` setting a pointer to each value `var` and running snippet `body` */
#define llforeach(anchor, var, body) ({\
        void** __list = (anchor)[0];\
        while(__list) {\
            void** __next = __list[0];\
            var = (void*) (__list + 1);\
            (body);\
            __list = __next;\
        }\
    })
/* Loops through linked list `anchor` setting a pointer to each value `var` and running snippet `body` */
#define linkedListForEach(anchor, var, body) llforeach(anchor, var, body)

// TODO: lliter

#endif