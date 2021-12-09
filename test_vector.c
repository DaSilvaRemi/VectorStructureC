//
// Created by remid on 18/11/2021.
//
#include <stdio.h>
#include "vector.h"
#include "random.h"
#include "my_struct.h"

/**
 * T.U. on vector_alloc
 *
 * @return 1 if passed -1 otherwise
 */
int test_vector_alloc()
{
    size_t expected_size = 0;
    p_s_vector vector = vector_alloc(expected_size, (t_data_alloc) my_struct_alloc, (t_data_free) my_struct_free, (t_data_cpy) my_struct_copy);

    //Test NULL values
    if(vector == NULL){
        printf("Error : vector was nos allocate ! \n");
        return -1;
    }

    if(vector->tab == NULL){
        printf("Error : vector->tab was nos allocate ! \n");
        return -1;
    }

    int is_passed = 1;

    //Test size 0
    size_t size = vector_size(vector);
    if (expected_size != size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)size);
        is_passed = -1;
    }

    //Test capacity 16
    size_t expected_capacity = expected_size + 16;
    size_t capacity = vector_capacity(vector);
    if (expected_capacity != capacity)
    {
        printf("Error : expected capacity %lu but was %lu \n", (unsigned long)expected_capacity, (unsigned long)capacity);
        is_passed = -1;
    }

    expected_size = 10;
    vector_free(vector);
    vector = vector_alloc(expected_size, (t_data_alloc) my_struct_alloc, (t_data_free) my_struct_free, (t_data_cpy) my_struct_copy);

    //Test NULL values
    if(vector == NULL){
        printf("Error : vector was nos allocate ! \n");
        return -1;
    }

    if(vector->tab == NULL){
        free(vector);
        printf("Error : vector->tab was nos allocate ! \n");
        return -1;
    }

    //Test size 10
    size = vector_size(vector);
    if (expected_size != size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)size);
        is_passed = -1;
    }

    //Test size 10
    size = vector_size(vector);
    if (expected_size != size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)size);
        is_passed = -1;
    }

    vector_free(vector);
    return is_passed;
}

/**
 * T.U. on vector_get
 *
 * @remark One of the test display error, it's not a problem it's a normal behaviour
 *
 * @return 1 if passed -1 otherwise
 */
int test_vector_get()
{
    p_s_vector vector = vector_alloc(10, (t_data_alloc) my_struct_alloc, (t_data_free) my_struct_free, (t_data_cpy) my_struct_copy);
    int is_passed = 1;
    void * result = (void *) random_size_t(0, 10);

    vector_get(vector, 30, result);
    void* expected_result = NULL;

    //Test get over the size, display error
    if (result != expected_result)
    {
        printf("Error : expected %p but was %p \n", expected_result, result);
        is_passed = 0;
    }

    //Test get value
    /*vector_get(vector, 1, expected_result);
    my_struct_randoms_init(((p_s_my_struct) expected_result));
    vector_set(vector, 1, expected_result);
    vector_get(vector, 1, result);

    if (result != expected_result)
    {
        printf("Error : expected %p but was %p \n", expected_result, result);
        is_passed = 0;
    }

    vector_free(vector);
    return is_passed;*/
}

/**
 * T.U. on vector_set
 *
 * @remark One of the test display error, it's not a problem it's a normal behaviour
 *
 * @return 1 if passed -1 otherwise
 */
int test_vector_set()
{
    size_t i = 10;
    void* expected_result = (void *) -1;
    void * result = NULL;

    p_s_vector vector = vector_alloc(i, (t_data_alloc) my_struct_alloc, (t_data_free) my_struct_free, (t_data_cpy) my_struct_copy);
    int is_passed = 1;

    //Test set value over tab, display error
    i += 26;
    vector_set(vector, i, &expected_result);
    vector_get(vector, i, result);

    if (result != expected_result)
    {
        printf("Error : expected %p but was %p \n", expected_result, result);
        is_passed = -1;
    }

    //Test set random value
    expected_result = (void *) random_size_t(0, 10);
    i = 2;
    vector_set(vector, i, expected_result);
    vector_get(vector, i, result);

    if (result != expected_result)
    {
        printf("Error : expected %p but was %p \n", expected_result, result);
        is_passed = -1;
    }

    //Test set other random value
    expected_result = (void *) random_size_t(0, 10);
    i = 9;
    vector_set(vector, i , expected_result);
    vector_get(vector, i, result);

    if (result != expected_result)
    {
        printf("Error : expected %p but was %p \n", expected_result, result);
        is_passed = -1;
    }

    vector_free(vector);
    return is_passed;
}

/**
 * T.U. on vector_insert
 *
 * @remark One of the test display error, it's not a problem it's a normal behaviour
 *
 * @return 1 if passed -1 otherwise
 */
int test_vector_insert()
{
    int is_passed = 1;

    p_s_vector vector = vector_alloc(10, (t_data_alloc) my_struct_alloc, (t_data_free) my_struct_free, (t_data_cpy) my_struct_copy);
    size_t i = 5;
    size_t expected_size = vector_size(vector) + 1;
    void* result = NULL;
    void* expected_result = (void *) random_size_t(0, 10);
    void* expected_result_2 = (void *) random_size_t(0, 10);

    vector_set(vector, i, expected_result);
    vector_insert(vector, i, expected_result_2);
    size_t real_size = vector_size(vector);

    //Test insert in the middle of the tab
    if (real_size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long) real_size);
        is_passed = -1;
    }

    vector_get(vector, i, result);
    if (result != expected_result_2)
    {
        printf("Error : expected %p but was %p \n", expected_result_2, result);
        is_passed = -1;
    }

    vector_get(vector, i + 1, result);
    if (result != expected_result)
    {
        printf("Error : expected %p but was %p \n", expected_result, result);
        is_passed = -1;
    }

    //Test insert in the end of the tab
    i = vector_size(vector);
    expected_result = (void *) random_size_t(0, 10);
    expected_size = i + 1;

    vector_insert(vector, i, expected_result);
    real_size = vector_size(vector);
    if (real_size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)real_size);
        is_passed = -1;
    }

    vector_get(vector, i, result);
    if (result != expected_result)
    {
        printf("Error : expected %p but was %p \n", expected_result, result);
        is_passed = -1;
    }

    //Test insert over the size limit
    i = vector_size(vector) * 2;
    expected_size = vector_size(vector) + 1;
    vector_insert(vector, i, &expected_result);

    real_size = vector_size(vector);
    if (real_size == expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)real_size);
        is_passed = -1;
    }

    vector_free(vector);
    return is_passed;
}

/**
 * T.U. on vector_erase
 *
 * @return 1 si réussi -1 sinon
 */
int test_vector_erase()
{
    int is_passed = 1;
    p_s_vector vector = vector_alloc(10, (t_data_alloc) my_struct_alloc, (t_data_free) my_struct_free, (t_data_cpy) my_struct_copy);
    void* result = NULL;
    void* expected_result = (void *) random_size_t(0, 10);

    //Test erase in the middle of the tab
    size_t i = 5;
    size_t real_size = vector_size(vector);
    size_t expected_size = real_size - 1;

    vector_set(vector, i, expected_result);
    --i;
    void* tmp_expected_result = (void *) random_size_t(0, 10);
    vector_set(vector, i, tmp_expected_result);
    vector_erase(vector, i);
    real_size = vector_size(vector);

    if (real_size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)real_size);
        is_passed = -1;
    }

    vector_get(vector, i, result);
    if (result != expected_result)
    {
        printf("Error : expected %p but was %p \n", expected_result, result);
        is_passed = -1;
    }

    //Test erase in the start of the tab
    i = 0;
    expected_result = (void *) random_size_t(0, 10);
    expected_size = vector_size(vector) - 1;

    vector_set(vector, i, expected_result);
    expected_result = (void *) random_size_t(0, 10);
    vector_set(vector, i + 1, expected_result);
    vector_erase(vector, i);

    real_size = vector_size(vector);
    if (real_size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)real_size);
        is_passed = -1;
    }

    vector_get(vector, i, result);
    if (result != expected_result)
    {
        printf("Error : expected %p but was %p \n", expected_result, result);
        is_passed = -1;
    }

    vector_free(vector);
    return is_passed;
}

/**
 * T.U. on vector_push_back
 *
 *
 * @return 1 if passed -1 otherwise
 */
int test_vector_push_back()
{
    int is_passed = 1;
    p_s_vector vector = vector_alloc(10, (t_data_alloc) my_struct_alloc, (t_data_free) my_struct_free, (t_data_cpy) my_struct_copy);
    void * expected_result = (void *) random_size_t(0, 10);
    void * result = NULL;
    size_t expected_size = vector_size(vector) + 1;

    //Test add after last element
    vector_push_back(vector, expected_result);
    if (vector->size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)vector->size);
        is_passed = -1;
    }

    --expected_size;

    //Test values
    vector_get(vector, expected_size, result);
    if (result != expected_result)
    {
        printf("Error : expected %p but was %p \n", expected_result, result);
        is_passed = -1;
    }

    vector_free(vector);
    return is_passed;
}

/**
 * T.U. on vector_pop_back
 *
 * @remark One of the test display error, it's not a problem it's a normal behaviour
 *
 * @return 1 if passed -1 otherwise
 */
int test_vector_pop_back()
{
    //Define default var
    p_s_vector vector = vector_alloc(10, (t_data_alloc) my_struct_alloc, (t_data_free) my_struct_free, (t_data_cpy) my_struct_copy);
    size_t size = vector_size(vector);
    size_t i = size - 1;
    size_t expected_size = i;
    void* expected_result = (void *) random_size_t(0, 10);
    void* result = NULL;
    int is_passed = 1;

    //Test erase last element
    vector_set(vector, i, expected_result);
    vector_set(vector, --i, expected_result);
    vector_pop_back(vector);
    size = vector_size(vector);

    //Test size
    if (size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)size);
        is_passed = -1;
    }

    //Test value in the limit
    vector_get(vector, i, result);
    if (result != expected_result)
    {
        printf("Error : expected %p but was %p \n", expected_result, result);
        is_passed = -1;
    }

    vector_free(vector);
    return is_passed;
}

/**
 * T.U. on vector_clear
 *
 * @return 1 if passed -1 otherwise
 */
int test_vector_clear()
{
    p_s_vector vector = vector_alloc(10, (t_data_alloc) my_struct_alloc, (t_data_free) my_struct_free, (t_data_cpy) my_struct_copy);
    size_t size = vector_size(vector);
    void* expected_result = NULL;
    int is_passed = 1;

    for(size_t i = 0; i < size; i++){
        expected_result = (void * ) random_size_t(0, 10);
        vector_set(vector, i, expected_result);
    }

    vector_clear(vector);
    size = vector_size(vector);

    if(size != 0){
        printf("Error : expected size %d but was %lu \n", 0, (unsigned long)size);
        is_passed = -1;
    }

    //Test to add after clear
    void* result = NULL;

    for(size_t i = 0; i < size; i++){
        expected_result = (void *) random_size_t(0, 10);
        vector_insert(vector, i, expected_result);
        vector_get(vector, i, result);
        if(result != expected_result){
            printf("Error : expected %p but was %p \n",expected_result, result);
            is_passed = -1;
        }
    }

    //Test get value after clear and insert
    expected_result = (void *) random_size_t(0, 10);
    vector_push_back(vector, expected_result);
    size_t expected_size = 1;
    size_t real_size = vector_size(vector);
    vector_get(vector, 0, result);

    if(real_size != expected_size){
        printf("Error : expected %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)real_size);
        is_passed = -1;
    }

    if(result != expected_result){
        printf("Error : expected %p but was %p \n", expected_result, result);
        is_passed = -1;
    }

    vector_free(vector);
    return is_passed;
}

/**
 * T.U. on vector_empty
 *
 * @return 1 if passed -1 otherwise
 */
int test_vector_empty(){
    p_s_vector vector = vector_alloc(0, (t_data_alloc) my_struct_alloc, (t_data_free) my_struct_free, (t_data_cpy) my_struct_copy);

    if(vector_empty(vector) != 1){
        return -1;
    }

    vector_free(vector);
    return 1;
}

/**
 * T.U. on vector_size
 *
 * @return 1 if passed -1 otherwise
 */
int test_vector_size(){
    p_s_vector vector = vector_alloc(0, (t_data_alloc) my_struct_alloc, (t_data_free) my_struct_free, (t_data_cpy) my_struct_copy);
    int result = vector_size(vector);
    int expected_result = 0;
    int is_passed = 1;

    if(result != expected_result){
        printf("Error : expected size %d but was %d \n", expected_result, result);
        is_passed = -1;
    }

    vector_free(vector);
    return is_passed;
}

/**
 * T.U. on vector_capacity
 *
 * @return 1 if passed -1 otherwise
 */
int test_vector_capacity(){
    p_s_vector vector = vector_alloc(0, (t_data_alloc) my_struct_alloc, (t_data_free) my_struct_free, (t_data_cpy) my_struct_copy);

    int result = vector_capacity(vector);
    int expected_result = 16;
    int is_passed = 1;
    if(result != expected_result){
        printf("Error : expected capacity %d but was %d \n", expected_result, result);
        return -1;
    }

    for (int i = 0; i < 17; ++i) {
        void * v = (void *) random_size_t(0, 10);
        vector_insert(vector, i, v);
    }

    result = vector_capacity(vector);
    expected_result = 32;
    if(result != expected_result){
        printf("Error : expected capacity %d but was %d \n", expected_result, result);
        is_passed = -1;
    }

    vector_free(vector);
    return is_passed;
}

int main(int argc, char *argv[])
{
    //printf("%s \n", test_vector_alloc() == 1 ? "Test Allocate passed" : "Test Allocate Failed");

    printf("%s \n", test_vector_get() == 1 ? "Test Get passed" : "Test Get Failed");

    //printf("%s \n", test_vector_set() == 1 ? "Test Set passed" : "Test Set Failed");

    //printf("%s \n", test_vector_insert() == 1 ? "Test Insert passed" : "Test Insert Failed");

    //printf("%s \n", test_vector_erase() == 1 ? "Test Erase passed" : "Test Erase Failed");

    //printf("%s \n", test_vector_push_back() == 1 ? "Test Push Back passed" : "Test Push Back Failed");

    //printf("%s \n", test_vector_pop_back() == 1 ? "Test Pop Back passed" : "Test Pop Back Failed");

    //printf("%s \n", test_vector_clear() == 1 ? "Test Clear passed" : "Test Clear Failed");

    //printf("%s \n", test_vector_empty() == 1 ? "Test Empty passed" : "Test Empty Failed");

    //printf("%s \n", test_vector_size() == 1 ? "Test Size passed" : "Test Size Failed");

    //printf("%s \n", test_vector_capacity() == 1 ? "Test Capacity passed" : "Test Capacity Failed");

    return 0;
}