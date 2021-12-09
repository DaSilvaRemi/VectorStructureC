//
// Created by remid on 18/11/2021.
//

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#ifdef V2
struct struct_vector
{
    double *tab;
    size_t size;
    size_t capacity;
} ;

typedef struct struct_vector s_vector;
typedef s_vector* p_s_vector;

p_s_vector vector_alloc(size_t n);
void vector_insert(p_s_vector p_vector, size_t i, double v);
void vector_erase(p_s_vector p_vector, size_t i);
size_t vector_capacity(p_s_vector p_vector);
void toString(p_s_vector p_vector);

#else

struct struct_vector
{
    double *tab;
    size_t size;
} ;

typedef struct struct_vector s_vector;
typedef s_vector* p_s_vector;

p_s_vector vector_alloc(size_t n);
void vector_insert(p_s_vector p_vector, size_t i, double v);
void vector_erase(p_s_vector p_vector, size_t i);
void toString(p_s_vector p_vector);

#endif

double vector_get(p_s_vector p_vector, size_t i);
void vector_set(p_s_vector p_vector, size_t i, double v);
void vector_free(p_s_vector p_vector);
void vector_push_back(p_s_vector p_vector, double v);
void vector_pop_back(p_s_vector p_vector);
void vector_clear(p_s_vector p_vector);
int vector_empty(p_s_vector p_vector);
size_t vector_size(p_s_vector p_vector);

#endif //_VECTOR_H_