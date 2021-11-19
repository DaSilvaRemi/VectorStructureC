//
// Created by remid on 18/11/2021.
//

#ifndef _VECTOR_DOUBLE_H
#define _VECTOR_DOUBLE_H

typedef struct s_vector_v1_double
{
    double *tab;
    size_t size;
    size_t max_size;
    size_t capacity;
} s_vector_v1_double;

typedef struct s_vector_v1_double *p_s_vector_v1_double;

p_s_vector_v1_double vector_v1_double_alloc(size_t n);
void vector_v1_double_free(p_s_vector_v1_double p_vector);
double vector_v1_double_get(p_s_vector_v1_double p_vector, size_t i);
void vector_v1_double_set(p_s_vector_v1_double p_vector, size_t i, double v);
void vector_v1_double_insert(p_s_vector_v1_double p_vector, size_t i, double v);
void vector_v1_double_erase(p_s_vector_v1_double p_vector, size_t i);
void vector_v1_push_back(p_s_vector_v1_double p_vector, double v);
void vector_v1_pop_back(p_s_vector_v1_double p_vector);
void vector_v1_clear(p_s_vector_v1_double p_vector);
int vector_v1_empty(p_s_vector_v1_double p_vector);
size_t vector_v1_size(p_s_vector_v1_double p_vector);
void toString(p_s_vector_v1_double p_vector);

#endif //_VECTOR_DOUBLE_H