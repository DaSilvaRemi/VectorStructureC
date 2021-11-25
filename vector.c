//
// Created by remid on 18/11/2021.
//
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "vector.h"

/**
 * Alloue dynamiquement un vecteur de capacity n + 10
 *
 * @params n Nombre de case qu'on doit initialiser à 0.0
 */
p_s_vector vector_alloc(size_t n)
{
    size_t max_size = sizeof(s_vector);
    size_t sizeOfTab = sizeof(double) * n;

    p_s_vector vector = (p_s_vector) malloc(max_size);

    if (vector == NULL)
    {
        printf("Error to allocating memory\n");
        return NULL;
    }

    vector->size = n;
    vector->tab = (double *) malloc(sizeOfTab);

    if (vector->tab == NULL)
    {
        printf("Error to allocating memory\n");
        free(vector);
        return NULL;
    }

    for (size_t i = 0; i < vector->size; i++)
    {
        vector->tab[i] = 0.0;
    }
    return vector;
}

/**
 * Libère le pointeur alloué dynamiquement
 *
 * @params p_vector Un pointeur sur une structure vecteur
 */
void vector_free(p_s_vector p_vector)
{
    free(p_vector->tab);
    free(p_vector);
    p_vector = NULL;
}

/**
 * Libère le pointeur alloué dynamiquement
 *
 * @params p_vector Un pointeur sur une structure vecteur
 */
double vector_get(p_s_vector p_vector, size_t i)
{
    if (i >= vector_size(p_vector))
    {
        printf("Error limit of the array is [%d; %lu[\n", 0, (unsigned long)vector_size(p_vector));
        return -1;
    }

    return p_vector->tab[i];
}

void vector_set(p_s_vector p_vector, size_t i, double v)
{
    if (i >= vector_size(p_vector))
    {
        printf("Error limit of the array is [%d; %lu[\n", 0, (unsigned long)vector_size(p_vector));
        return;
    }

    p_vector->tab[i] = v;
}

void vector_insert(p_s_vector p_vector, size_t i, double v)
{
    if (i > vector_size(p_vector))
    {
        printf("Error limit of the array is [%d; %lu[\n", 0, (unsigned long)vector_size(p_vector));
        return;
    }

    ++p_vector->size;

    p_vector->tab = realloc(p_vector->tab, sizeof(double) * vector_size(p_vector));
    if (p_vector->tab == NULL)
    {
        printf("Error to realloc p_vector->tab !");
        return;
    }

    size_t sizeEndArray = vector_size(p_vector) - i;

    double *tmpEndArray = (double *)malloc(sizeof(double) * sizeEndArray);
    if (tmpEndArray == NULL)
    {
        printf("Error to allocating tmpEndArray\n");
        return;
    }

    for (size_t j = 0; j < sizeEndArray; ++j)
    {
        tmpEndArray[j] = vector_get(p_vector, j + i);
    }
    vector_set(p_vector, i, v);

    for (size_t j = 0; j < sizeEndArray - 1; ++j)
    {
        vector_set(p_vector, j + i + 1, tmpEndArray[j]);
    }

    free(tmpEndArray);
    tmpEndArray = NULL;
}

void vector_erase(p_s_vector p_vector, size_t i)
{
    if (i >vector_size(p_vector))
    {
        printf("Error limit of the array is [%d; %lu[\n", 0, (unsigned long)vector_size(p_vector));
        return;
    }

    if (vector_empty(p_vector) == 1)
    {
        printf("Error the array it's empty !\n");
        return;
    }

    size_t iNext = i + 1;
    size_t sizeEndArray = vector_size(p_vector) - iNext;

    double *tmpEndArray = (double *)malloc(sizeof(double) * sizeEndArray);
    if (tmpEndArray == NULL)
    {
        printf("Error to allocating memory\n");
        return;
    }

    for (size_t j = 0; j < sizeEndArray; ++j)
    {
        tmpEndArray[j] = vector_get(p_vector, j + iNext);
    }

    for (size_t j = 0; j < sizeEndArray; ++j)
    {
        vector_set(p_vector, j + i, tmpEndArray[j]);
    }
    free(tmpEndArray);
    tmpEndArray = NULL;

    p_vector->tab = realloc(p_vector->tab, sizeof(double) * vector_size(p_vector) - 1);
    if(p_vector->tab == NULL){
        printf("Error to realloc p_vector->tab\n");
        return;
    }

    --p_vector->size;
}

void vector_push_back(p_s_vector p_vector, double v)
{
    vector_insert(p_vector, vector_size(p_vector), v);
}

void vector_pop_back(p_s_vector p_vector)
{
    vector_erase(p_vector, vector_size(p_vector) - 1);
}

void vector_clear(p_s_vector p_vector)
{
    p_vector->size = 0;
    p_vector->tab = realloc(p_vector->tab, sizeof(double) * p_vector->size);

    if (p_vector->tab == NULL)
    {
        printf("Error to realloc p_vector->tab for cleaning\n");
        return;
    }
}

int vector_empty(p_s_vector p_vector)
{
    return vector_size(p_vector) == 0 ? 1 : 0;
}

size_t vector_size(p_s_vector p_vector)
{
    return p_vector->size;
}

void toString(p_s_vector p_vector)
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
    printf("};\n");
}