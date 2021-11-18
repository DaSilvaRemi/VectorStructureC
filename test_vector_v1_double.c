//
// Created by remid on 18/11/2021.
//
#include "vector_v1_double.h"
#include <stdio.h>

int test_vector_v1_double_alloc(){
    p_s_vector_v1_double vector = vector_v1_double_alloc(0);
    int isPassed = 0;

    if(vector != NULL && vector->size == 10 && vector->capacity == vector->size * 2 && vector->tab != NULL){
        isPassed = 1;
    }

    vector = vector_v1_double_alloc(0);

    if(vector != NULL && vector->size == 10 && vector->capacity == vector->size * 2 && vector->tab != NULL){
        isPassed = 1;
    }
    vector_v1_double_free(p_s_vector_v1_double);
    return isPassed;
}

int test_vector_v1_double_free(){
    p_s_vector_v1_double vector = vector_v1_double_alloc(10);
    vector_v1_double_free(vector);

    if(vector == NULL){
        return 1;
    }

    return 0;
}

int test_vector_v1_double_get(){
    p_s_vector_v1_double vector = vector_v1_double_alloc(10);
    double isPassed = 1;

    double result = vector_v1_double_get(*p_s_vector_v1_double, 10);

    if(result != -1){
        isPassed = 0;
    }

    result = vector_v1_double_get(*p_s_vector_v1_double, 1);

    if(result != 0.0){
        isPassed = 0;
    }

    result = vector_v1_double_get(*p_s_vector_v1_double, 9);

    if(result != 0.0){
        isPassed = 0;
    }

    vector_v1_double_free(vector);
    return isPassed;
}

int test_vector_v1_double_set(){
    p_s_vector_v1_double vector = vector_v1_double_alloc(10);
    double isPassed = 1;

    vector_v1_double_set(*p_s_vector_v1_double, 10, 10);
    result = vector_v1_double_get(*p_s_vector_v1_double, 10);

    if(result != -1){
        isPassed = 0;
    }

    vector_v1_double_set(*p_s_vector_v1_double, 1, 4.5);
    result = vector_v1_double_get(*p_s_vector_v1_double, 1);

    if(result != 4.5){
        isPassed = 0;
    }

    vector_v1_double_set(*p_s_vector_v1_double, 9, 7.5);
    result = vector_v1_double_get(*p_s_vector_v1_double, 9);

    if(result != 7.5){
        isPassed = 0;
    }

    vector_v1_double_free(vector);
    return isPassed;
}

int test_vector_v1_double_insert(){
    p_s_vector_v1_double vector = vector_v1_double_alloc(10);
    double isPassed = 1;

    vector_v1_double_free(vector);
    return isPassed;
}

int main(int argc, char *argv[]){
    p_s_vector_v1_double p_vector;

    char* result = test_vector_v1_double_alloc() == 1 ? "Test Allocate passed" : "Test Allocate Failed";
    printf("%s \n", result);

    char* result = test_vector_v1_double_free() == 1 ? "Test Free passed" : "Test Free Failed";
    printf("%s \n", result);

    char* result = test_vector_v1_double_get() == 1 ? "Test Get passed" : "Test Free Failed";
    printf("%s \n", result);

    char* result = test_vector_v1_double_set() == 1 ? "Test Set passed" : "Test Free Failed";
    printf("%s \n", result);
}