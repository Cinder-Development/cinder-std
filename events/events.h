/* Copyright (C) 2023 Cinder Development.
   This file is part of the Cinder Standard Library and
   was written by ephf 2023.

   This project is licensed under the MIT License.
   See the LICENSE file for details */

#include "../hashmap/hashmap.h"

#ifndef EVENTS_H
#define EVENTS_H

/* Type for event emitter */
#define event_emitter_t(type) hashmap_t
/* Type for event emitter */
#define EventEmitter(type) hashmap_t

/* Default type for event emitter */
typedef hashmap_t event_emitter_t;
/* Default type for event emitter */
typedef hashmap_t EventEmitter;

/* Creates a new event emitter

DYNAMIC ALLOCATION use `eefree(hashmap_t map)` */
#define eenew(capacity) hmnew(capacity, 0)
/* Creates a new event emitter

DYNAMIC ALLOCATION use `freeEventEmitter(EventEmitter map)` */
#define newEventEmitter(capacity) eenew(capacity)

/* Calls all listeners on event emitter `emitter` for event `event` with input `data` */
#define eeemit(emitter, event, data) ({\
        linked_list_t __listeners = hmget(emitter, event, linked_list_t, NULL);\
        if(__listeners) llforeach(__listeners, void (**handler)(typeof(data)), (*handler)(data));\
    })
/* Calls all listeners on event emitter `emitter` for event `event` with input `data` */
#define eedispatch_event(emitter, event, data) eeemit(emitter, event, data)
/* Calls all listeners on event emitter `emitter` for event `event` with input `data` */
#define eventEmitterEmit(emitter, event, data) eeemit(emitter, event, data)
/* Calls all listeners on event emitter `emitter` for event `event` with input `data` */
#define eventEmitterDispatchEvent(emitter, event, data) eeemit(emitter, event, data)

/* Adds listener `listener` on event emitter `emitter` for event `event` */
int eeon(event_emitter_t emitter, char* event, void* listener);
/* Adds listener `listener` on event emitter `emitter` for event `event` */
#define eeadd_listener(emitter, event, listener) eeon(emitter, event, listener)
/* Adds listener `listener` on event emitter `emitter` for event `event` */
#define eventEmitterOn(emitter, event, listener) eeon(emitter, event, listener)
/* Adds listener `listener` on event emitter `emitter` for event `event` */
#define eventEmitterAddListener(emitter, event, listener) eeon(emitter, event, listener)

// TODO: remove listeners, eefree (requires entries)

#endif