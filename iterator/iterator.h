/* Copyright (C) 2023 Cinder Development.
   This file is part of the Cinder Standard Library and
   was written by ephf 2023.

   This project is licensed under the MIT License.
   See the LICENSE file for details */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/* Type for iterator */
typedef struct iterator_t {
    int unit_size;
    int size;
    void* data;
    void* state;
    void* (*next)(struct iterator_t*);
    int res_size;
    bool dyn;
} iterator_t;
/* Type for iterator */
typedef iterator_t Iterator;

void* __iter_default_next(iterator_t* iter);

#define __iter_expand(...) __VA_ARGS__

#define __iter_combine_ab(a, b) a ## b
#define __iter_combine(a, b) __iter_combine_ab(a, b)

#define __iter_traverse(...) for(int __i = 0; __next = __iter.next(&__iter); __i++) { __VA_ARGS__ __iter_traverse_end
#define __iter_traverse_vd(type, var) __iter_traverse(\
        typedef type __itype;\
        __itype var = *(__itype*) __next;)
#define __iter_traverse_end(body) body }

#define __iter_ddecl(type, var) type var

#define __iter_try_clone if(__iter.next != &__iter_default_next) {\
            char __ibuffer[__iter.unit_size * __iter.size];\
            __iter_traverse (memcpy((void*) __ibuffer + __i * __iter.unit_size, __next, __iter.unit_size);) ()\
            __iter.data = __iter.state = (void*) __ibuffer; __iter.next = &__iter_default_next; __iter.res_size = sizeof(__ibuffer);\
        } else __iter.res_size = 0;

#define __iter_start(unit_size, size, data, next) ({ iterator_t __iter = { unit_size, size, data,\
    NULL, next, 0, false }; void* __next; __iter.state = (&__iter)
#define __iter_inter(...) data; __VA_ARGS__ char __iter_combine(__reserve_buffer, __COUNTER__)[__iter.res_size]; __iter.state = (&__iter)
#define __iter_end(...) data; __VA_ARGS__ })

#define __iter_into_iterator_t(iter) iter

/* Starts an iterator based on array `array` */
#define iter(array) __iter_start(sizeof(*array), sizeof(array) / sizeof(*array), (void*) array, &__iter_default_next)
/* Starts an iterator based on array `array` and returns an iterator_t */
#define into_iter(array) iter(array)->ito(iterator_t)
/* Starts an iterator based on array `array` and returns an iterator_t */
#define intoIter(array) into_iter(array)

/* Maps each value of the current iterator from variable `vardata` using snippet `logic` */
#define imap(vardata, logic) __iter_inter({\
        __iter_ddecl vardata;\
        typedef typeof((logic)) __iltype;\
        char __ibuffer[sizeof(__iltype) * __iter.size];\
        __iter_traverse_vd vardata ({\
            __iltype __logic = (logic);\
            memcpy((void*) __ibuffer + __i * sizeof(__iltype), (void*) &__logic, sizeof(__iltype));\
        })\
        __iter = (iterator_t) { sizeof(__iltype), __iter.size, (void*) __ibuffer, NULL, &__iter_default_next, sizeof(__ibuffer), false };\
    })

/* Slices the current iterator from index `start` for `n` values */
#define islice(start, n) __iter_inter({\
        __iter_try_clone\
        int __start = (start < 0 ? __iter.size + start : start);\
        int __n = n == 0 ? __iter.size - __start : n < 0 ? __iter.size - __start + n : n;\
        __iter.size = __n; __iter.data += __start * __iter.unit_size;\
    })

/* Filters each value of the current iterator from variable `vardata` using snippet `logic` */
#define ifilter(vardata, logic) __iter_inter({\
        __iter_try_clone\
        int __offset = 0;\
        __iter_traverse_vd vardata ({\
            if(!(logic)) __offset++;\
            else memcpy(__iter.data + (__i - __offset) * __iter.unit_size, __iter.data + __i * __iter.unit_size, __iter.unit_size);\
        })\
        __iter.size -= __offset; __iter.res_size = 0;\
    })

/* Reverses the elements in the current iterator */
#define ireverse() __iter_inter({\
        char __ibuffer[__iter.unit_size * __iter.size];\
        __iter_traverse (memcpy((void*) __ibuffer + (__iter.size - __i - 1) * __iter.unit_size, __next, __iter.unit_size);) ()\
        __iter.data = __ibuffer; __iter.res_size = sizeof(__ibuffer);\
    })

/* Zips other iterators into the current iterator, making each element a tuple of each value in each iterator */
#define izip(...) __iter_inter({\
        iterator_t __iters[] = { __VA_ARGS__ };\
        int __unit_size = __iter.unit_size;\
        for(int i = 0; i < sizeof(__iters) / sizeof(*__iters); i++) __unit_size += __iters[i].unit_size;\
        char __ibuffer[__unit_size * __iter.size];\
        __iter_traverse ({\
            int __offset = __iter.unit_size;\
            memcpy(__ibuffer + __i * __unit_size, __next, __iter.unit_size);\
            for(int __j = 0; __j < sizeof(__iters) / sizeof(*__iters); __j++) {\
                memcpy(__ibuffer + __i * __unit_size + __offset, __iters[__j].data + __i * __iters[__j].unit_size, __iters[__j].unit_size);\
                __offset += __iters[__j].unit_size;\
            }\
        }) ()\
        __iter = (iterator_t) { __unit_size, __iter.size, (void*) __ibuffer, NULL, &__iter_default_next, sizeof(__ibuffer), false };\
        for(int i = 0; i < sizeof(__iters) / sizeof(*__iters); i++) if(__iters[i].dyn) free(__iters[i].data);\
    })

/* Makes each element of the current iterator a tuple of the index and the element */
#define ienumerate() __iter_inter({\
        int __unit_size = __iter.unit_size + sizeof(int);\
        char __ibuffer[__unit_size * __iter.size];\
        __iter_traverse (memcpy((void*) __ibuffer + __i * __unit_size + sizeof(int), __iter.data + __i * __iter.unit_size, __iter.unit_size);\
           *(int*) (__ibuffer + __i * __unit_size) = __i;) ()\
        __iter = (iterator_t) { __unit_size, __iter.size, (void*) __ibuffer, NULL, &__iter_default_next, sizeof(__ibuffer), false };\
    })

#define __ireduce_a(a, b) a
#define __ireduce_b(a, b) b
/* Reduces the current iterator down from variables `accdata` and `vardata` using snippet `logic` */
#define ireduce(accdata, vardata, logic) __iter_end(\
        __ireduce_a accdata __ireduce_b accdata = *(__ireduce_a accdata*) __iter.next(&__iter);\
        __iter_traverse_vd vardata (__ireduce_b accdata = (logic);)\
        __ireduce_b accdata;\
    )

/* Reduces the current iterator down from the starting value `iv` and variables `accdata` and `vardata` using snippet `logic` */
#define ivreduce(iv, accdata, vardata, logic) __iter_end(\
        __ireduce_a accdata __ireduce_b accdata = iv;\
        __iter_traverse_vd vardata (__ireduce_b accdata = (logic);)\
        __ireduce_b accdata;\
    )

/* true if the latest `ifind` was successful and false if not */
static bool ITER_FOUND = false;

/* Finds a value from the current iterator from variable `vardata` using snippet `logic`
If a value is not found, `ITER_FOUND` will be set to false, the reverse is also true */
#define ifind(vardata, logic) __iter_end(\
        int __j = -1;\
        __iter_traverse_vd vardata (if((logic)) {\
            __j = __i; break;\
        })\
        (__j == -1 ? (__ireduce_a vardata) (ITER_FOUND = false) : ((ITER_FOUND = true), ((__ireduce_a vardata*) __iter.data)[__j]));\
    )

/* Returns true if any element in the current iterator is found from variable `vardata` using snippet `logic` */
#define iany(vardata, logic) __iter_end(\
        int __j = -1;\
        __iter_traverse_vd vardata (if((logic)) {\
            __j = __i; break;\
        })\
        __j != -1;\
    )

/* Counts the amount of elements in the current iterator found from variable `vardata` using snippet `logic` */
#define icount(vardata, logic) __iter_end(\
        int __count = 0;\
        __iter_traverse_vd vardata (if((logic)) __count++;)\
        __count;\
    )

/* Iterates through the current iterator from variable `vardata` using snippet `logic` */
#define iforeach(vardata, logic) __iter_end(__iter_traverse_vd vardata ((logic););)

#define __iter_malloc void* __ibuffer = malloc(__iter.unit_size * __iter.size);\
    __iter_traverse (memcpy(__ibuffer + __i * __iter.unit_size, __next, __iter.unit_size);) ()\
    __iter.data = __ibuffer; __iter.dyn = true;

/* Casts the current iterator to type `type`

DYNAMIC ALLOCATION use `free(void* ptr)` */
#define ias(type) __iter_end(__iter_malloc (type) __iter.data;)
/* Converts the current iterator to type `type`

DYNAMIC ALLOCATION */
#define ito(type) __iter_end(__iter_malloc __iter_into_ ## type(__iter);)