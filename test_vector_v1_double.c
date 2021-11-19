//
// Created by remid on 18/11/2021.
//
#include "vector_v1_double.h"
#include <stdio.h>

int test_vector_v1_double_alloc()
{
    p_s_vector_v1_double vector = vector_v1_double_alloc(0);
    int isPassed = 0;

    if (vector != NULL && vector->size == 10 && vector->capacity == vector->size * 2 && vector->tab != NULL)
    {
        isPassed = 1;
    }

    vector = vector_v1_double_alloc(0);

    if (vector != NULL && vector->size == 10 && vector->capacity == vector->size * 2 && vector->tab != NULL)
    {
        isPassed = 1;
    }
    vector_v1_double_free(vector);
    return isPassed;
}

int test_vector_v1_double_free()
{
    p_s_vector_v1_double vector = vector_v1_double_alloc(10);
    vector_v1_double_free(vector);

    if (vector == NULL)
    {
        return 1;
    }

    return 0;
}

int test_vector_v1_double_get()
{
    p_s_vector_v1_double vector = vector_v1_double_alloc(10);
    double isPassed = 1;

    double result = vector_v1_double_get(vector, 10);

    if (result != -1)
    {
        isPassed = 0;
    }

    result = vector_v1_double_get(vector, 1);

    if (result != 0.0)
    {
        isPassed = 0;
    }

    result = vector_v1_double_get(vector, 9);

    if (result != 0.0)
    {
        isPassed = 0;
    }

    vector_v1_double_free(vector);
    return isPassed;
}

int test_vector_v1_double_set()
{
    p_s_vector_v1_double vector = vector_v1_double_alloc(10);
    double isPassed = 1;

    vector_v1_double_set(vector, 10, 10);
    double result = vector_v1_double_get(vector, 10);

    if (result != -1)
    {
        isPassed = 0;
    }

    vector_v1_double_set(vector, 1, 4.5);
    result = vector_v1_double_get(vector, 1);

    if (result != 4.5)
    {
        isPassed = 0;
    }

    vector_v1_double_set(vector, 9, 7.5);
    result = vector_v1_double_get(vector, 9);

    if (result != 7.5)
    {
        isPassed = 0;
    }

    vector_v1_double_free(vector);
    return isPassed;
}

int test_vector_v1_double_insert()
{
    p_s_vector_v1_double vector = vector_v1_double_alloc(10);
    double result = 0.0;
    double j = 1.0;
    size_t i = 11;

    for (i = 11; i < vector->capacity; ++i, ++j)
    {
        vector_v1_double_insert(vector, i, j);

        if (vector->size != i)
        {
            printf("Error : expected size %lu but was %lu \n", (unsigned long)i, (unsigned long)vector->size);
            return -1;
        }

        result = vector_v1_double_get(vector, i);
        if (result != j)
        {
            printf("Error : expected %f but was %f \n", j, result);
            return -1;
        }
    }

    ++i;
    ++j;
    size_t expectedCapacity = vector->capacity + 10;

    vector_v1_double_insert(vector, i, j);

    if (vector->capacity != expectedCapacity)
    {
        printf("Error : expected capacity %lu but was %lu \n", (unsigned long)expectedCapacity, (unsigned long)vector->capacity);
        return -1;
    }

    if (vector->size != i)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)i, (unsigned long)vector->size);
        return -1;
    }

    result = vector_v1_double_get(vector, i);
    if (result != j)
    {
        printf("Error : expected %f but was %f \n", j, result);
        return -1;
    }

    vector_v1_double_free(vector);
    return 1;
}

int test_vector_v1_double_erase()
{
    p_s_vector_v1_double vector = vector_v1_double_alloc(10);
    double result = 0.0;
    size_t i = vector->size - 1;

    for (; i >= 0; --i)
    {
        vector_v1_double_erase(vector, i);

        if (vector->size != i)
        {
            printf("Error : expected size %lu but was %lu \n", (unsigned long)i, (unsigned long)vector->size);
            return -1;
        }

        result = vector_v1_double_get(vector, i);
        if (result != -1)
        {
            printf("Error : expected %f but was %f \n", -1, result);
            return -1;
        }
    }

    vector_v1_double_free(vector);
    return 1;
}

int test_vector_v1_push_back()
{
    p_s_vector_v1_double vector = vector_v1_double_alloc(10);
    double result = 0.0;
    size_t i = 0;
    double j = 0.0;

    for (; i < vector->capacity; ++i)
    {
        vector_v1_push_back(vector, j);

        if (vector->size != i)
        {
            printf("Error : expected size %lu but was %lu \n", (unsigned long)i, (unsigned long)vector->size);
            return -1;
        }

        result = vector_v1_double_get(vector, i);
        if (result != j)
        {
            printf("Error : expected %f but was %f \n", j, result);
            return -1;
        }
    }

    ++i;
    ++j;
    size_t expectedCapacity = vector->capacity + 10;

    vector_v1_push_back(vector, j);

    if (vector->capacity != expectedCapacity)
    {
        printf("Error : expected capacity %lu but was %lu \n", (unsigned long)expectedCapacity, (unsigned long)vector->capacity);
        return -1;
    }

    if (vector->size != i)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)i, (unsigned long)vector->size);
        return -1;
    }

    result = vector_v1_double_get(vector, i);
    if (result != j)
    {
        printf("Error : expected %f but was %f \n", j, result);
        return -1;
    }

    vector_v1_double_free(vector);
    return 1;
}

int test_vector_v1_pop_back()
{
    p_s_vector_v1_double vector = vector_v1_double_alloc(10);
    double result = 0.0;
    size_t i = vector->size - 1;

    for (; i >= 0; --i)
    {
        vector_v1_pop_back(vector);

        if (vector->size != i)
        {
            printf("Error : expected size %lu but was %lu \n", (unsigned long)i, (unsigned long)vector->size);
            return -1;
        }

        result = vector_v1_double_get(vector, i);
        if (result != -1)
        {
            printf("Error : expected %f but was %f \n", -1, result);
            return -1;
        }
    }
    vector_v1_pop_back(vector);
    if (vector->size != i)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long) i, (unsigned long)vector->size);
        return -1;
    }

    vector_v1_double_free(vector);
    return 1;
}

int test_vector_v1_clear()
{
    p_s_vector_v1_double vector = vector_v1_double_alloc(0);
    vector_v1_clear(vector);

    int isPassed = 1;
    
    if(vector->size != 10){
        isPassed = 0;
    }

    if(vector->capacity != 20){
        isPassed = 0;
    }

    vector_v1_double_free(vector);
    return isPassed;
}

int test_vector_v1_empty(){
    p_s_vector_v1_double vector = vector_v1_double_alloc(0);
    vector_v1_clear(vector);
    
    if(vector_v1_empty(vector) != 1){
        return 0;
    }

    vector_v1_double_free(vector);
    return 1;
}

int test_vector_v1_size(){
    p_s_vector_v1_double vector = vector_v1_double_alloc(0);
    vector_v1_clear(vector);
    
    if(vector_v1_empty(vector) != 1){
        return 0;
    }

    vector_v1_double_free(vector);
    return 1;
}

int main(int argc, char *argv[])
{
    char *result = test_vector_v1_double_alloc() == 1 ? "Test Allocate passed" : "Test Allocate Failed";
    printf("%s \n", result);

    char *result = test_vector_v1_double_free() == 1 ? "Test Free passed" : "Test Free Failed";
    printf("%s \n", result);

    char *result = test_vector_v1_double_get() == 1 ? "Test Get passed" : "Test Free Failed";
    printf("%s \n", result);

    char *result = test_vector_v1_double_set() == 1 ? "Test Set passed" : "Test Free Failed";
    printf("%s \n", result);

    char *result = test_vector_v1_double_insert() == 1 ? "Test Insert passed" : "Test Insert Failed";
    printf("%s \n", result);

    char *result = test_vector_v1_double_erase() == 1 ? "Test Erase passed" : "Test Erase Failed";
    printf("%s \n", result);

    char *result = test_vector_v1_push_back() == 1 ? "Test Push Back passed" : "Test Push Back Failed";
    printf("%s \n", result);

    char *result = test_vector_v1_pop_back() == 1 ? "Test Pop Back passed" : "Test Pop Back Failed";
    printf("%s \n", result);

    char *result = test_vector_v1_pop_back() == 1 ? "Test Pop Back passed" : "Test Pop Back Failed";
    printf("%s \n", result);

    char *result = test_vector_v1_clear() == 1 ? "Test Clear passed" : "Test Clear Failed";
    printf("%s \n", result);

    char *result = test_vector_v1_empty() == 1 ? "Test Empty passed" : "Test Empty Failed";
    printf("%s \n", result);

    char *result = vector_v1_size() == 1 ? "Test Empty passed" : "Test Empty Failed";
    printf("%s \n", result);

    char *result = test_vector_v1_empty() == 1 ? "Test Empty passed" : "Test Empty Failed";
    printf("%s \n", result);

    return 0;
}