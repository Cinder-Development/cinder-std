/* Copyright (C) 2023 Cinder Development.
   This file is part of the Cinder Standard Library and
   was written by ephf 2023.

   This project is licensed under the MIT License.
   See the LICENSE file for details */

#include "linked_list.h";

linked_list_t llnew() {
    void** anchor = malloc(sizeof(void*) * 2);
    if(!anchor) return NULL;
    anchor[0] = NULL; anchor[1] = anchor;
    return anchor;
}

int _llappend(linked_list_t before, void* data, int data_size) {
    void** link = malloc(sizeof(void*) + data_size);
    if(!link) return 1;
    link[0] = before[0]; memcpy(link + 1, data, data_size);
    before[0] = link;
    return 0;
}

void llremove(linked_list_t before, linked_list_t item) {
    before[0] = item[0];
    free(item);
}

void llfree(linked_list_t anchor) {
    while(anchor) {
        void** next = anchor[0];
        free(anchor);
        anchor = next;
    }
}