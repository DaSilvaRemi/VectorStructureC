//
// Created by remid on 18/11/2021.
//
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "vector_v1_double.h"

p_s_vector_v1_double vector_v1_double_alloc(size_t n)
{
    size_t max_size = sizeof(p_s_vector_v1_double);
    size_t capacity = n + 10;
    size_t sizeOfTab = sizeof(double) * max_size;

    p_s_vector_v1_double vector = (p_s_vector_v1_double) malloc(max_size);

    if (vector == NULL)
    {
        printf("Error to allocating memory");
        return NULL;
    }

    vector->size = n;
    vector->max_size = max_size + sizeOfTab;
    vector->capacity = capacity;
    vector->tab = (double *)malloc(sizeOfTab);

    if (vector->tab == NULL)
    {
        printf("Error to allocating memory");
        return NULL;
    }

    for (size_t i = 0; i < vector->size; i++)
    {
        vector->tab[i] = 0.0;
    }
    return vector;
}

void vector_v1_double_free(p_s_vector_v1_double p_vector)
{
    free(p_vector->tab);
    free(p_vector);
    p_vector = NULL;
}

double vector_v1_double_get(p_s_vector_v1_double p_vector, size_t i)
{
    if (i < 0 && i >= p_vector->size)
    {
        printf("Error limit of the array is [%d; %lu[", 0, (unsigned long)p_vector->size);
        return -1;
    }

    return p_vector->tab[i];
}

void vector_v1_double_set(p_s_vector_v1_double p_vector, size_t i, double v)
{
    if (i < 0 && i >= p_vector->size)
    {
        printf("Error limit of the array is [%d; %lu[", 0, (unsigned long)p_vector->size);
        return;
    }

    p_vector->tab[i] = v;
}

void vector_v1_double_insert(p_s_vector_v1_double p_vector, size_t i, double v)
{
    if (i < 0 && i > p_vector->size)
    {
        printf("Error limit of the array is [%d; %lu[", 0, (unsigned long)p_vector->size);
        return;
    }

    if (p_vector->size + 1 >= p_vector->capacity)
    {
        size_t newCapacity = p_vector->capacity * 2;
        p_vector->tab = realloc(p_vector->tab, sizeof(double) * newCapacity);

        if (p_vector->tab == NULL)
        {
            printf("Error to realloc memory");
            return;
        }

        p_vector->capacity = newCapacity;
    }

    size_t sizeEndArray = p_vector->size - i;

    double *tmpEndArray = (double *)malloc(sizeof(double) * sizeEndArray);
    if (tmpEndArray == NULL)
    {
        printf("Error to allocating memory");
        return;
    }

    for (size_t j = 0; j < sizeEndArray; ++j)
    {
        tmpEndArray[j] = vector_v1_double_get(p_vector, j + i);
    }

    vector_v1_double_set(p_vector, i, v);

    for (size_t j = 0; j < sizeEndArray; ++j)
    {
        vector_v1_double_set(p_vector, j + i + 1, tmpEndArray[j]);
    }

    ++p_vector->size;
}

void vector_v1_double_erase(p_s_vector_v1_double p_vector, size_t i)
{
    if (i < 0 && i > p_vector->size)
    {
        printf("Error limit of the array is [%d; %lu[", 0, (unsigned long)p_vector->size);
        return;
    }
    else if (vector_v1_empty(p_vector) == 1)
    {
        printf("Error the array it's empty !");
        return;
    }

    size_t iNext = i + 1;
    size_t sizeEndArray = p_vector->size - iNext;

    double *tmpEndArray = (double *)malloc(sizeof(double) * sizeEndArray);
    if (tmpEndArray == NULL)
    {
        printf("Error to allocating memory");
        return;
    }

    for (size_t j = 0; j < sizeEndArray; ++j)
    {
        tmpEndArray[j] = vector_v1_double_get(p_vector, j + iNext);
    }

    for (size_t j = 0; j < sizeEndArray; ++j)
    {
        vector_v1_double_set(p_vector, j + i, tmpEndArray[j]);
    }

    --p_vector->size;
}

void vector_v1_push_back(p_s_vector_v1_double p_vector, double v)
{
    vector_v1_double_insert(p_vector, p_vector->size, v);
}

void vector_v1_pop_back(p_s_vector_v1_double p_vector)
{
    vector_v1_double_erase(p_vector, p_vector->size - 1);
}

void vector_v1_clear(p_s_vector_v1_double p_vector)
{
    vector_v1_double_free(p_vector);
    p_vector = vector_v1_double_alloc(0);

    if (p_vector == NULL)
    {
        printf("Error to realloc memory");
        return;
    }
    p_vector->size = 0;
}

int vector_v1_empty(p_s_vector_v1_double p_vector)
{
    return p_vector->size >= 0 ? 1 : 0;
}

size_t vector_v1_size(p_s_vector_v1_double p_vector)
{
    return p_vector->size;
}

void toString(p_s_vector_v1_double p_vector)
{
    printf("p_vector{\n tab : [");

    for (size_t i = 0; i < p_vector->size; i++)
    {
        printf("%f", p_vector->tab[i]);

        if (i < p_vector->size - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
    printf("size : %lu\n", (unsigned long)p_vector->size);
    printf("max_size : %lu\n", (unsigned long)p_vector->max_size);
    printf("capacity : %lu\n", (unsigned long)p_vector->capacity);
    printf("};\n");
}