//
// Created by remid on 18/11/2021.
//

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

typedef void *(*t_data_alloc)();
typedef void (*t_data_free)(void *p_data);
typedef void (*t_data_cpy)(void *p_data_dst, void *p_data_src);

struct struct_vector
{
    void **tab;
    size_t size;
    size_t capacity;
    t_data_alloc alloc_func;
    t_data_free free_func;
    t_data_cpy cpy_func;
};

typedef struct struct_vector s_vector;
typedef s_vector *p_s_vector;

p_s_vector vector_alloc(size_t n, t_data_alloc alloc_func, t_data_free free_func, t_data_cpy cpy_func);
void vector_free(p_s_vector p_vector);
void vector_free_tab(p_s_vector p_vector);
int vector_get(p_s_vector p_vector, size_t i, void *p_data);
void vector_set(p_s_vector p_vector, size_t i, void *v);
void vector_insert(p_s_vector p_vector, size_t i, void *v);
void vector_erase(p_s_vector p_vector, size_t i);
void vector_push_back(p_s_vector p_vector, void *v);
void vector_pop_back(p_s_vector p_vector);
void vector_clear(p_s_vector p_vector);
int vector_empty(p_s_vector p_vector);
size_t vector_capacity(p_s_vector p_vector);
size_t vector_size(p_s_vector p_vector);
void toString(p_s_vector p_vector);

#endif //_VECTOR_H_