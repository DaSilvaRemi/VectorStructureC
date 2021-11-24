//
// Created by remid on 18/11/2021.
//
#include <stdio.h>
#include "vector.h"

int test_vector_alloc()
{
    p_s_vector vector = vector_alloc(0);
    int isPassed = 0;

    if (vector != NULL && vector->tab != NULL && vector_size(vector) == 0)
    {
        isPassed = 1;
    }

    vector = vector_alloc(10);

    if (vector != NULL && vector->tab != NULL && vector->size == 10)
    {
        isPassed = 1;
    }
    vector_free(vector);
    return isPassed;
}

int test_vector_free()
{
    p_s_vector vector = vector_alloc(10);
    vector_free(vector);

    if (vector == NULL)
    {
        return 1;
    }

    return 0;
}

int test_vector_get()
{
    p_s_vector vector = vector_alloc(10);
    double isPassed = 1;

    double result = vector_get(vector, 10);

    if (result != -1)
    {
        isPassed = 0;
    }

    result = vector_get(vector, 1);

    if (result != 0.0)
    {
        isPassed = 0;
    }

    result = vector_get(vector, 9);

    if (result != 0.0)
    {
        isPassed = 0;
    }

    vector_free(vector);
    return isPassed;
}

int test_vector_set()
{
    p_s_vector vector = vector_alloc(10);
    double isPassed = 1;

    vector_set(vector, 10, 10);
    double result = vector_get(vector, 10);

    if (result != -1)
    {
        isPassed = 0;
    }

    vector_set(vector, 1, 4.5);
    result = vector_get(vector, 1);

    if (result != 4.5)
    {
        isPassed = 0;
    }

    vector_set(vector, 9, 7.5);
    result = vector_get(vector, 9);

    if (result != 7.5)
    {
        isPassed = 0;
    }

    vector_free(vector);
    return isPassed;
}

int test_vector_insert()
{
    p_s_vector vector = vector_alloc(10);
    double result = 0.0;
    double j = 1.0;
    size_t i = 5;
    size_t expected_size = vector_size(vector) + 1;
    vector_insert(vector, i, j);

    if (vector->size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)vector->size);
        return -1;
    }

    result = vector_get(vector, i);
    if (vector_get(vector, i) != j)
    {
        printf("Error : expected %f but was %f \n", j, result);
        return -1;
    }
    i = vector_size(vector) * 2;
    expected_size = vector_size(vector) + 1;

    vector_insert(vector, i, j);

    if (vector->size == expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size - 1, (unsigned long)vector->size);
        return -1;
    }

    vector_free(vector);
    return 1;
}

int test_vector_erase()
{
    p_s_vector vector = vector_alloc(10);
    double result = 0.0;
    size_t expected_size = vector->size - 1;

    vector_set(vector, 6, 4.0);
    vector_erase(vector, 5);
    if (vector->size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)vector->size);
        return -1;
    }

    result = vector_get(vector, 5);
    if (result != 4.0)
    {
        printf("Error : expected %d but was %f \n", 4.0, result);
        return -1;
    }

    vector_free(vector);
    return 1;
}

int test_vector_push_back()
{
    p_s_vector vector = vector_alloc(10);
    double result = 0.0;
    double j = 5.0;
    size_t expected_size = vector_size(vector) + 1;

    toString(vector);
    vector_push_back(vector, j);
    if (vector->size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)vector->size);
        return -1;
    }
    toString(vector);
    result = vector_get(vector, expected_size--);
    if (result != j)
    {
        printf("Error : expected %f but was %f \n", j, result);
        return -1;
    }

    vector_free(vector);
    return 1;
}

int test_vector_pop_back()
{
    p_s_vector vector = vector_alloc(10);
    double result = 0.0;
    size_t i = vector->size - 1;

    for (; i != 0; --i)
    {
        vector_pop_back(vector);

        if (vector->size != i)
        {
            printf("Error : expected size %lu but was %lu \n", (unsigned long)i, (unsigned long)vector->size);
            return -1;
        }

        result = vector_get(vector, i);
        if (result != -1)
        {
            printf("Error : expected %d but was %f \n", -1, result);
            return -1;
        }
    }
    vector_pop_back(vector);
    if (vector->size != i)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long) i, (unsigned long)vector->size);
        return -1;
    }

    vector_free(vector);
    return 1;
}

int test_vector_clear()
{
    p_s_vector vector = vector_alloc(10);
    vector_clear(vector);

    int isPassed = 1;
    
    if(vector->size != 10){
        isPassed = 0;
    }

    vector_free(vector);
    return isPassed;
}

int test_vector_empty(){
    p_s_vector vector = vector_alloc(0);
    vector_clear(vector);
    
    if(vector_empty(vector) != 1){
        return 0;
    }

    vector_free(vector);
    return 1;
}

int test_vector_size(){
    p_s_vector vector = vector_alloc(0);
    vector_clear(vector);
    
    if(vector_empty(vector) != 1){
        return 0;
    }

    vector_free(vector);
    return 1;
}

int main(int argc, char *argv[])
{
    //printf("%s \n", test_vector_alloc() == 1 ? "Test Allocate passed" : "Test Allocate Failed");

    //printf("%s \n", test_vector_free() == 1 ? "Test Free passed" : "Test Free Failed");

   // printf("%s \n", test_vector_get() == 1 ? "Test Get passed" : "Test Free Failed");

    //printf("%s \n", test_vector_set() == 1 ? "Test Set passed" : "Test Free Failed");

    //printf("%s \n", test_vector_insert() == 1 ? "Test Insert passed" : "Test Insert Failed");

    //printf("%s \n", test_vector_erase() == 1 ? "Test Erase passed" : "Test Erase Failed");

    printf("%s \n", test_vector_push_back() == 1 ? "Test Push Back passed" : "Test Push Back Failed");

    //printf("%s \n", test_vector_pop_back() == 1 ? "Test Pop Back passed" : "Test Pop Back Failed");

    //printf("%s \n", test_vector_clear() == 1 ? "Test Clear passed" : "Test Clear Failed");

    //printf("%s \n", test_vector_empty() == 1 ? "Test Empty passed" : "Test Empty Failed");

    //printf("%s \n", test_vector_size() == 1 ? "Test Size passed" : "Test Size Failed");

    return 0;
}