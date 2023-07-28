/* Copyright (C) 2023 Cinder Development.
   This file is part of the Cinder Standard Library and
   was written by ephf 2023.

   This project is licensed under the MIT License.
   See the LICENSE file for details */

#ifndef TUPLE_H
#define TUPLE_H

#define __tup_eval1(...) __tup_eval2(__tup_eval2(__tup_eval2(__tup_eval2(__VA_ARGS__))))
#define __tup_eval2(...) __tup_eval3(__tup_eval3(__tup_eval3(__tup_eval3(__VA_ARGS__))))
#define __tup_eval3(...) __tup_eval4(__tup_eval4(__tup_eval4(__tup_eval4(__VA_ARGS__))))
#define __tup_eval4(...) __VA_ARGS__

/* Creates a struct containing each inputted type with names a-z */
#define tup(...) struct{__tup_eval1(__tup_eval(z, __VA_ARGS__))
/* Creates a struct containing each inputted type with names a-z */
#define Tuple tup

#define __tup_eval(...) __tup_check_end(__VA_ARGS__, _true)
#define __tup_eval_in() __tup_eval
#define __tup_if_true(...) }
#define __tup_if_false(a, b, ...) b __tup_let ## a;__tup_defer(__tup_eval_in)()(__tup_let ## a, __VA_ARGS__)

#define __tup_empty()
#define __tup_defer(id) id __tup_empty()

#define __tup_existsn(a, b, ...) __tup_if ## b
#define __tup_exists(...) __tup_existsn(__VA_ARGS__, _false)
#define __tup_check_end(a, b, ...) __tup_exists(__tup_end ## b)(a, b, __VA_ARGS__)
#define __tup_end_true ~, _true

#define __tup_leta b
#define __tup_letb c
#define __tup_letc d
#define __tup_letd e
#define __tup_lete f
#define __tup_letf g
#define __tup_letg h
#define __tup_leth i
#define __tup_leti j
#define __tup_letj k
#define __tup_letk l
#define __tup_letl m
#define __tup_letm n
#define __tup_letn o
#define __tup_leto p
#define __tup_letp q
#define __tup_letq r
#define __tup_letr s
#define __tup_lets t
#define __tup_lett u
#define __tup_letu v
#define __tup_letv w
#define __tup_letw x
#define __tup_letx y
#define __tup_lety z
#define __tup_letz a

#endif