//
// Created by remid on 18/11/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int test_vector_alloc()
{
    size_t expected_size = 0;
    p_s_vector vector = vector_alloc(expected_size);

    if(vector == NULL){
        printf("Error : vector was nos allocate ! \n");
        return -1;
    }

    if(vector->tab == NULL){
        printf("Error : vector->tab was nos allocate ! \n");
        return -1;
    }

    int isPassed = 1;

    size_t size = vector_size(vector);
    if (expected_size != size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)size);
        isPassed = -1;
    }

    expected_size = 10;
    vector_free(vector);
    vector = vector_alloc(expected_size);

    if(vector == NULL){
        printf("Error : vector was nos allocate ! \n");
        return -1;
    }

    if(vector->tab == NULL){
        printf("Error : vector->tab was nos allocate ! \n");
        return -1;
    }

    size = vector_size(vector);
    if (expected_size != size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)size);
        isPassed = -1;
    }

    vector_free(vector);
    return isPassed;
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
    size_t i = 10;
    double expected_result = 10.0;

    p_s_vector vector = vector_alloc(i);
    double isPassed = 1;

    vector_set(vector, i, expected_result);
    double result = vector_get(vector, i);
    expected_result = -1;

    if (result != expected_result)
    {
        printf("Error : expected %f but was %f \n", expected_result, result);
        isPassed = -1;
    }

    expected_result = 4.5;
    i = 2;
    vector_set(vector, i, expected_result);
    result = vector_get(vector, i);

    if (result != expected_result)
    {
        printf("Error : expected %f but was %f \n", expected_result, result);
        isPassed = -1;
    }

    expected_result = 7.5;
    i = 9;
    vector_set(vector, i , expected_result);
    result = vector_get(vector, i );

    if (result != expected_result)
    {
        printf("Error : expected %f but was %f \n", expected_result, result);
        isPassed = -1;
    }

    vector_free(vector);
    return isPassed;
}

int test_vector_insert()
{
    int isPassed = 1;

    p_s_vector vector = vector_alloc(10);
    size_t i = 5;
    size_t expected_size = vector_size(vector) + 1;
    double result = 0.0;
    double j = 1.0;

    vector_set(vector, i, j * 2);
    vector_insert(vector, i, j);
    size_t real_size = vector_size(vector);

    //Test insert in the middle of the tab
    if (real_size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long) real_size);
        isPassed = -1;
    }

    result = vector_get(vector, i);
    if (result != j)
    {
        printf("Error : expected %f but was %f \n", j, result);
        isPassed = -1;
    }

    result = vector_get(vector, i + 1);
    if (result != j * 2)
    {
        printf("Error : expected %f but was %f \n", j * 2, result);
        isPassed = -1;
    }

    //Test insert in the end of the tab
    i = vector_size(vector);
    j = 10.0;
    expected_size = i + 1;

    vector_insert(vector, i, j);
    real_size = vector_size(vector);
    if (real_size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)real_size);
        isPassed = -1;
    }

    result = vector_get(vector, i);
    if (result != j)
    {
        printf("Error : expected %f but was %f \n", j, result);
        isPassed = -1;
    }

    //Test insert other size limit
    i = vector_size(vector) * 2;
    expected_size = vector_size(vector) + 1;
    vector_insert(vector, i, j);

    real_size = vector_size(vector);
    if (real_size == expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)real_size);
        isPassed = -1;
    }

    vector_free(vector);
    return isPassed;
}

int test_vector_erase()
{
    int isPassed = 1;
    p_s_vector vector = vector_alloc(10);
    double result = 0.0;

    //Test erase in the middle of the tab
    size_t i = 6;
    double j = 4.0;
    size_t real_size = vector_size(vector);
    size_t expected_size = real_size - 1;

    vector_set(vector, i, j);
    --i;
    vector_set(vector, i, 5.0);
    vector_erase(vector, i);
    real_size = vector_size(vector);

    if (real_size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)real_size);
        isPassed = -1;
    }

    result = vector_get(vector, i);
    if (result != j)
    {
        printf("Error : expected %f but was %f \n", j, result);
        isPassed = -1;
    }

    //Test erase in the start of the tab
    i = 0;
    j = 10.0;
    expected_size = vector_size(vector) - 1;

    vector_set(vector, i, j);
    vector_set(vector, i + 1, 4.0);
    vector_erase(vector, i);

    real_size = vector_size(vector);
    if (real_size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)real_size);
        isPassed = -1;
    }

    result = vector_get(vector, i);
    if (result == j)
    {
        printf("Error : expected %f but was %f \n", 4.0, result);
        isPassed = -1;
    }

    vector_free(vector);
    return isPassed;
}

int test_vector_push_back()
{
    int isPassed = 1;
    p_s_vector vector = vector_alloc(10);
    double result = 0.0;
    double j = 5.0;
    size_t expected_size = vector_size(vector) + 1;

    vector_push_back(vector, j);
    if (vector->size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)vector->size);
        isPassed = -1;
    }

    --expected_size;

    result = vector_get(vector, expected_size);
    if (result != j)
    {
        printf("Error : expected %f but was %f \n", j, result);
        isPassed = -1;
    }

    vector_free(vector);
    return isPassed;
}

int test_vector_pop_back()
{
    p_s_vector vector = vector_alloc(10);
    size_t size = vector_size(vector);
    size_t i = size - 1;
    size_t expected_size = i;
    double j = 5.0;
    double result = 0.0;
    int isPassed = 1;

    vector_set(vector, i, j);
    vector_set(vector, --i, j);
    vector_pop_back(vector);
    size = vector_size(vector);

    if (size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)size);
        isPassed = -1;
    }

    result = vector_get(vector, i + 1);
    if (result != -1)
    {
        printf("Error : expected %d but was %f \n", -1, result);
        isPassed = -1;
    }

    result = vector_get(vector, i);
    if (result != j)
    {
        printf("Error : expected %f but was %f \n", j, result);
        isPassed = -1;
    }

    vector_free(vector);
    return isPassed;
}

int test_vector_clear()
{
    p_s_vector vector = vector_alloc(10);
    size_t size = vector_size(vector);
    double j = 1.0;
    int isPassed = 1;

    for(size_t i = 0; i < size; i++){
        vector_set(vector, i, j);
        ++j;
    }

    vector_clear(vector);
    size = vector_size(vector);

    if(size != 0){
        printf("Error : expected size %d but was %lu \n", 0, (unsigned long)size);
        isPassed = -1;
    }

    double result = 0.0;
    double expected = result;
    for(size_t i = 0; i < size; i++){
        result = vector_get(vector, i);
        if(result != expected){
            printf("Error : expected %f but was %f \n", expected, result);
            isPassed = -1;
        }
    }

    expected = 10.0;
    vector_push_back(vector, expected);
    size_t expected_size = 1;
    size_t real_size = vector_size(vector);

    if(real_size != expected_size){
        printf("Error : expected %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)real_size);
        isPassed = -1;
    }

    result = vector_get(vector, 0);

    if(result != expected){
        printf("Error : expected %f but was %f \n", expected, result);
        isPassed = -1;
    }

    vector_free(vector);
    return isPassed;
}

int test_vector_empty(){
    p_s_vector vector = vector_alloc(0);
    int isPassed = 1;
    
    if(vector_empty(vector) != 1){
        return -1;
    }

    vector_free(vector);
    return 1;
}

int test_vector_size(){
    p_s_vector vector = vector_alloc(0);

    int result = vector_empty(vector);
    int expected_result = 1;
    if(result != expected_result){
        printf("Error : expected %d but was %d \n", expected_result, result);
        return -1;
    }

    vector_free(vector);
    return 1;
}

int main(int argc, char *argv[])
{
    printf("%s \n", test_vector_alloc() == 1 ? "Test Allocate passed" : "Test Allocate Failed");

    printf("%s \n", test_vector_get() == 1 ? "Test Get passed" : "Test Free Failed");

    printf("%s \n", test_vector_set() == 1 ? "Test Set passed" : "Test Free Failed");

    printf("%s \n", test_vector_insert() == 1 ? "Test Insert passed" : "Test Insert Failed");

    printf("%s \n", test_vector_erase() == 1 ? "Test Erase passed" : "Test Erase Failed");

    printf("%s \n", test_vector_push_back() == 1 ? "Test Push Back passed" : "Test Push Back Failed");

    printf("%s \n", test_vector_pop_back() == 1 ? "Test Pop Back passed" : "Test Pop Back Failed");

    printf("%s \n", test_vector_clear() == 1 ? "Test Clear passed" : "Test Clear Failed");

    printf("%s \n", test_vector_empty() == 1 ? "Test Empty passed" : "Test Empty Failed");

    printf("%s \n", test_vector_size() == 1 ? "Test Size passed" : "Test Size Failed");

    return 0;
}