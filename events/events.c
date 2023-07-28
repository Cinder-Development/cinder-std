/* Copyright (C) 2023 Cinder Development.
   This file is part of the Cinder Standard Library and
   was written by ephf 2023.

   This project is licensed under the MIT License.
   See the LICENSE file for details */

#include "events.h"

int eeon(event_emitter_t emitter, char* event, void* listener) {
    linked_list_t listeners = hmget(emitter, event, linked_list_t, NULL);
    if(!listeners) if(hminsert(emitter, event, listeners = llnew())) return 1;
    return llpush(listeners, listener) ? 2 : 0;
}