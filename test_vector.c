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
    p_s_vector vector = vector_alloc(expected_size, (t_data_alloc)my_struct_alloc, (t_data_free)my_struct_free, (t_data_cpy)my_struct_copy);

    //Test NULL values
    if (vector == NULL)
    {
        printf("Error : vector was nos allocate ! \n");
        return -1;
    }

    if (vector->tab == NULL)
    {
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
    vector = vector_alloc(expected_size, (t_data_alloc)my_struct_alloc, (t_data_free)my_struct_free, (t_data_cpy)my_struct_copy);

    //Test NULL values
    if (vector == NULL)
    {
        printf("Error : vector was nos allocate ! \n");
        return -1;
    }

    if (vector->tab == NULL)
    {
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

    expected_capacity = expected_size + 16;
    capacity = vector_capacity(vector);
    if (expected_capacity != capacity)
    {
        printf("Error : expected capacity %lu but was %lu \n", (unsigned long)expected_capacity, (unsigned long)capacity);
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
    p_s_vector vector = vector_alloc(10, (t_data_alloc)my_struct_alloc, (t_data_free)my_struct_free, (t_data_cpy)my_struct_copy);
    int is_passed = 1;
    void *p_result = (void *)my_struct_alloc();
    double result = 0;
    double expected_result = -1;

    result = vector_get(vector, 30, p_result);

    //Test get over the size, display error
    if (result != expected_result)
    {
        printf("Error : expected %lf but was %lf \n", expected_result, result);
        is_passed = 0;
    }

    expected_result = ((p_s_my_struct)p_result)->nb;

    //Test get value
    vector_get(vector, 1, p_result);

    result = ((p_s_my_struct)p_result)->nb;

    if (result != expected_result)
    {
        printf("Error : expected %lf but was %lf \n", result, expected_result);
        is_passed = 0;
    }

    my_struct_free((p_s_my_struct)p_result);
    vector_free(vector);
    vector = NULL;
    p_result = NULL;
    return is_passed;
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
    void *p_result = (void *)my_struct_alloc();
    double expected_result = -1;
    double result = 0;

    p_s_vector vector = vector_alloc(i, (t_data_alloc)my_struct_alloc, (t_data_free)my_struct_free, (t_data_cpy)my_struct_copy);
    int is_passed = 1;

    //Test set value over tab, display error
    i += 26;
    vector_set(vector, i, p_result);
    result = vector_get(vector, i, p_result);

    if (result != expected_result)
    {
        printf("Error : expected %lf but was %lf \n", expected_result, result);
        is_passed = -1;
    }

    my_struct_free((p_s_my_struct)p_result);

    //Test set random value
    i = 2;
    p_result = (void *)my_struct_alloc();
    expected_result = ((p_s_my_struct)p_result)->nb;

    vector_set(vector, i, p_result);
    vector_get(vector, i, p_result);

    result = ((p_s_my_struct)p_result)->nb;

    if (result != expected_result)
    {
        printf("Error : expected %lf but was %lf \n", expected_result, result);
        is_passed = -1;
    }

    my_struct_free(p_result);

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

    p_s_vector vector = vector_alloc(10, (t_data_alloc)my_struct_alloc, (t_data_free)my_struct_free, (t_data_cpy)my_struct_copy);
    size_t i = 5;
    size_t real_size = vector_size(vector);
    size_t expected_size = real_size + 1;
    void *p_result = (void *)my_struct_alloc();
    void *p_result_2 = (void *)my_struct_alloc();
    double result = 0.0;
    double expected_result = ((p_s_my_struct)p_result)->nb;
    double expected_result_2 = ((p_s_my_struct)p_result_2)->nb;

    vector_set(vector, i, p_result_2);
    vector_insert(vector, i, p_result);
    real_size = vector_size(vector);

    //Test insert in the middle of the tab
    if (real_size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)real_size);
        is_passed = -1;
    }

    vector_get(vector, i, p_result_2);
    result = ((p_s_my_struct)p_result_2)->nb;
    if (result != expected_result_2)
    {
        printf("Error : expected %lf but was %lf \n", expected_result_2, result);
        is_passed = -1;
    }

    vector_get(vector, i + 1, p_result);
    result = ((p_s_my_struct)p_result)->nb;
    if (result != expected_result)
    {
        printf("Error : expected %lf but was %lf \n", expected_result, result);
        is_passed = -1;
    }

    my_struct_free(p_result);
    p_result = (void *)my_struct_alloc();

    //Test insert in the end of the tab
    i = vector_size(vector);
    expected_result = ((p_s_my_struct)p_result)->nb;
    expected_size = i + 1;

    vector_insert(vector, i, p_result);

    real_size = vector_size(vector);
    if (real_size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)real_size);
        is_passed = -1;
    }

    vector_get(vector, i, p_result);
    result = ((p_s_my_struct)p_result)->nb;
    if (result != expected_result)
    {
        printf("Error : expected %lf but was %lf \n", expected_result, result);
        is_passed = -1;
    }

    //Test insert over the size limit
    i = vector_size(vector) * 2;
    expected_size = vector_size(vector) + 1;
    vector_insert(vector, i, p_result);

    real_size = vector_size(vector);
    if (real_size == expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)real_size);
        is_passed = -1;
    }

    my_struct_free(p_result);
    my_struct_free(p_result_2);
    p_result = NULL;
    p_result_2 = NULL;

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
    p_s_vector vector = vector_alloc(10, (t_data_alloc)my_struct_alloc, (t_data_free)my_struct_free, (t_data_cpy)my_struct_copy);
    void *p_result = (void *)my_struct_alloc();
    double result = 0;
    double expected_result = ((p_s_my_struct)p_result)->nb;

    /*Test erase in the middle of the tab*/
    size_t i = 5;
    size_t real_size = vector_size(vector);
    size_t expected_size = real_size - 1;

    //Set a value in the middle of the tab
    vector_set(vector, i, p_result);
    --i;
    //Set other value in middle - 1 of the tab
    void *tmp_expected_result = (void *)my_struct_alloc();
    vector_set(vector, i, tmp_expected_result);

    //Erase the middle - 1 value to verify if middle value didn't deleted
    vector_erase(vector, i);
    real_size = vector_size(vector);

    //Check Size
    if (real_size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)real_size);
        is_passed = -1;
    }

    //Check value
    vector_get(vector, i, p_result);

    result = ((p_s_my_struct)p_result)->nb;
    if (result != expected_result)
    {
        printf("Error : expected %lf but was %lf \n", expected_result, result);
        is_passed = -1;
    }

    /*Test erase in the start of the tab*/
    my_struct_free((p_s_my_struct)p_result);

    p_result = my_struct_alloc();
    i = 0;
    expected_size = vector_size(vector) - 1;
    expected_result = ((p_s_my_struct)p_result)->nb;

    vector_set(vector, i, tmp_expected_result);
    vector_set(vector, i + 1, p_result);
    vector_erase(vector, i);

    real_size = vector_size(vector);
    if (real_size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)real_size);
        is_passed = -1;
    }

    vector_get(vector, i, p_result);
    result = ((p_s_my_struct)p_result)->nb;
    if (result != expected_result)
    {
        printf("Error : expected %lf but was %lf \n", expected_result, result);
        is_passed = -1;
    }

    my_struct_free((p_s_my_struct)p_result);
    my_struct_free((p_s_my_struct)tmp_expected_result);
    p_result = NULL;
    tmp_expected_result = NULL;

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
    p_s_vector vector = vector_alloc(10, (t_data_alloc)my_struct_alloc, (t_data_free)my_struct_free, (t_data_cpy)my_struct_copy);
    void *p_result = (void *)my_struct_alloc();
    double result = 0;
    double expected_result = ((p_s_my_struct)p_result)->nb;
    size_t expected_size = vector_size(vector) + 1;

    //Test add after last element
    vector_push_back(vector, p_result);
    if (vector->size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)vector->size);
        is_passed = -1;
    }

    --expected_size;

    //Test values
    vector_get(vector, expected_size, p_result);
    result = ((p_s_my_struct)p_result)->nb;

    if (result != expected_result)
    {
        printf("Error : expected %lf but was %lf \n", expected_result, result);
        is_passed = -1;
    }

    my_struct_free((p_s_my_struct)p_result);
    p_result = NULL;

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
    p_s_vector vector = vector_alloc(10, (t_data_alloc)my_struct_alloc, (t_data_free)my_struct_free, (t_data_cpy)my_struct_copy);
    size_t size = vector_size(vector);
    size_t i = size - 1;
    size_t expected_size = i;
    void *p_result = (void *)my_struct_alloc();
    int is_passed = 1;
    double result = 0;
    double expected_result = ((p_s_my_struct)p_result)->nb;

    //Test erase last element
    void *tmp_expected_result = (void *)my_struct_alloc();
    vector_set(vector, i, tmp_expected_result);
    vector_set(vector, --i, p_result);
    vector_pop_back(vector);
    size = vector_size(vector);

    //Test size
    if (size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)size);
        is_passed = -1;
    }

    //Test value in the limit
    vector_get(vector, i, p_result);
    result = ((p_s_my_struct)p_result)->nb;
    if (result != expected_result)
    {
        printf("Error : expected %lf but was %lf \n", expected_result, result);
        is_passed = -1;
    }

    my_struct_free((p_s_my_struct)p_result);
    my_struct_free((p_s_my_struct)tmp_expected_result);
    p_result = NULL;
    tmp_expected_result = NULL;

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
    p_s_vector vector = vector_alloc(10, (t_data_alloc)my_struct_alloc, (t_data_free)my_struct_free, (t_data_cpy)my_struct_copy);
        
    size_t real_size = vector_size(vector);
    size_t expected_size = 0;
    void *p_result = (void *)my_struct_alloc();
    double result = 0;
    double expected_result = 0;
    int is_passed = 1;

    for (size_t i = 0; i < real_size; i++)
    {
        vector_set(vector, i, p_result);
    }

    vector_clear(vector);
    real_size = vector_size(vector);

    if (real_size != expected_size)
    {
        printf("Error : expected size %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)real_size);
        is_passed = -1;
    }

    //Test INSERT and GET after CLEAR
    my_struct_free((p_s_my_struct)p_result);

    for (size_t i = 0; i < real_size; i++)
    {
        real_size = vector_size(vector);
        expected_size = real_size + 1;

        p_result = (void *)my_struct_alloc();
        expected_result = ((p_s_my_struct)p_result)->nb;
        vector_insert(vector, i, p_result);
        vector_get(vector, i, p_result);

        if (real_size != expected_size)
        {
            printf("Error : expected %lu but was %lu \n", (unsigned long)expected_size, (unsigned long)real_size);
            is_passed = -1;
        }

        result = ((p_s_my_struct)p_result)->nb;
        if (result != expected_result)
        {
            printf("Error : expected %lf but was %lf \n", expected_result, result);
            is_passed = -1;
        }
    }

    vector_free(vector);
    return 1;
}

/**
 * T.U. on vector_empty
 *
 * @return 1 if passed -1 otherwise
 */
int test_vector_empty()
{
    int is_passed = 1;
    p_s_vector vector = vector_alloc(0, (t_data_alloc)my_struct_alloc, (t_data_free)my_struct_free, (t_data_cpy)my_struct_copy);

    if (vector_empty(vector) != 1)
    {
        is_passed = -1;
    }

    vector_free(vector);
    return is_passed;
}

/**
 * T.U. on vector_size
 *
 * @return 1 if passed -1 otherwise
 */
int test_vector_size()
{
    p_s_vector vector = vector_alloc(0, (t_data_alloc)my_struct_alloc, (t_data_free)my_struct_free, (t_data_cpy)my_struct_copy);
    int result = vector_size(vector);
    int expected_result = 0;
    int is_passed = 1;

    if (result != expected_result)
    {
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
int test_vector_capacity()
{
    int is_passed = 1;

    p_s_vector vector = vector_alloc(0, (t_data_alloc)my_struct_alloc, (t_data_free)my_struct_free, (t_data_cpy)my_struct_copy);
    void *p_result = (void *)my_struct_alloc();
    size_t result = vector_capacity(vector);
    size_t expected_result = 16;

    /* TEST GET CAPACITY AFTER ALLOCATION */

    if (result != expected_result)
    {
        printf("Error : expected capacity %lu but was %lu \n", (unsigned long) expected_result, (unsigned long) result);
        is_passed = -1;
    }

    /* TEST INCREASE CAPACITY WITH INSERT */

    for (int i = 0; i < 17; ++i)
    {
        vector_insert(vector, i, p_result);
    }

    result = vector_capacity(vector);
    expected_result = 32;
    if (result != expected_result)
    {
        printf("Error : expected capacity %lu but was %lu \n", (unsigned long) expected_result, (unsigned long) result);
        is_passed = -1;
    }

    /* TEST LOWER CAPACITY WITH ERASE */

    for (int i = 0; i < 9; ++i)
    {
        vector_pop_back(vector);
    }

    result = vector_capacity(vector);
    expected_result = 8;
    if (result != expected_result)
    {
        printf("Error : expected capacity %lu but was %lu \n", (unsigned long) expected_result, (unsigned long) result);
        is_passed = -1;
    }

    my_struct_free((p_s_my_struct)p_result);
    vector_free(vector);
    return is_passed;
}

int main(int argc, char *argv[])
{
    printf("%s \n", test_vector_alloc() == 1 ? "Test Allocate passed" : "Test Allocate Failed");

    printf("%s \n", test_vector_get() == 1 ? "Test Get passed" : "Test Get Failed");

    printf("%s \n", test_vector_set() == 1 ? "Test Set passed" : "Test Set Failed");

    printf("%s \n", test_vector_insert() == 1 ? "Test Insert passed" : "Test Insert Failed");

    printf("%s \n", test_vector_erase() == 1 ? "Test Erase passed" : "Test Erase Failed");

    printf("%s \n", test_vector_push_back() == 1 ? "Test Push Back passed" : "Test Push Back Failed");

    printf("%s \n", test_vector_pop_back() == 1 ? "Test Pop Back passed" : "Test Pop Back Failed");

    printf("%s \n", test_vector_clear() == 1 ? "Test Clear passed" : "Test Clear Failed");

    printf("%s \n", test_vector_empty() == 1 ? "Test Empty passed" : "Test Empty Failed");

    printf("%s \n", test_vector_size() == 1 ? "Test Size passed" : "Test Size Failed");

    printf("%s \n", test_vector_capacity() == 1 ? "Test Capacity passed" : "Test Capacity Failed");

    return 0;
}