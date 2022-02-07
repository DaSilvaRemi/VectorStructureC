//
// Created by remid on 03/12/2021.
//
#include <time.h>
#include "my_struct.h"
#include "random.h"

/**
 * T.U. on my_struct_alloc
 *
 * @return 1 if passed -1 otherwise
 */
int test_my_struct_alloc()
{
    p_s_my_struct my_struct = my_struct_alloc();
    int is_passed = 1;

    if (my_struct == NULL)
    {
        printf("Error : my_struct was not allocate ! \n");
        is_passed = -1;
    }

    my_struct_free(my_struct);
    my_struct = NULL;
    return is_passed;
}

/**
 * T.U. on my_struct_randoms_init
 *
 * @return 1 if passed -1 otherwise
 */
int test_my_struct_random_init(p_s_my_struct my_struct)
{
    // Free my_struct->str because it was already allocate
    free(my_struct->str);
    my_struct_randoms_init(my_struct);

    if (my_struct->str == NULL)
    {
        printf("Error : str was nos allocate ! \n");
        return -1;
    }

    if (strlen((const char *)my_struct->str) == 0)
    {
        printf("Error : expected my_struct->str >= 1 but was %lu \n", (unsigned long)strlen((const char *)my_struct->str));
        return -1;
    }

    return 1;
}

/**
 * T.U. on my_struct_copy
 *
 * @return 1 if passed -1 otherwise
 */
int test_my_struct_copy(p_s_my_struct my_struct)
{
    p_s_my_struct p_dest = my_struct_alloc();
    my_struct_copy(my_struct, p_dest);

    int is_passed = 1;

    if (p_dest->str == NULL)
    {
        printf("Error : str was nos allocate ! \n");
        is_passed = -1;
    }
    // Check the size of both structure
    size_t realSize = strlen((const char *)p_dest->str);
    size_t expectedSize = strlen((const char *)my_struct->str);
    if (realSize != expectedSize)
    {
        printf("Expected my_struct->str : %lu but was %lu \n", (unsigned long)realSize, (unsigned long)expectedSize);
        is_passed = -1;
    }

    // Check the content of the string
    for (size_t i = 0; p_dest->str[i] != '\0'; ++i)
    {
        if (my_struct->str[i] != p_dest->str[i])
        {
            printf("Error : expected %c but was %c \n", my_struct->str[i], p_dest->str[i]);
            is_passed = -1;
        }
    }

    // Check the number value
    if (my_struct->nb != p_dest->nb)
    {
        printf("Error : expected %lf but was %lf \n", my_struct->nb, p_dest->nb);
        is_passed = -1;
    }

    my_struct_free(p_dest);
    p_dest = NULL;
    return is_passed;
}

/**
 * T.U. on my_struct_cmp
 *
 * @return 1 if passed -1 otherwise
 */
int test_my_struct_cmp(p_s_my_struct my_struct)
{
    p_s_my_struct p_cmp = my_struct_alloc();

    int is_passed = 1;
    int result = my_struct_cmp(my_struct, p_cmp);

    // Check if we have a result
    if (result != -1 && result != 1 && result != 0)
    {
        printf("Error : expected [-1 or 0 or 1] but was %d \n", result);
        is_passed = -1;
    }

    my_struct_free(p_cmp);
    p_cmp = NULL;
    return is_passed;
}

/**
 * @brief The main program
 *
 * @param argc Number of argument
 * @param argv The arguments
 * @return int The error
 */
int main(int argc, char *argv[])
{
    time_t t = 0;
    time(&t);
    srand(t);

    p_s_my_struct my_struct = my_struct_alloc();

    printf("%s \n", test_my_struct_alloc() == 1 ? "Test Allocate passed" : "Test Allocate Failed");

    printf("%s \n", test_my_struct_random_init(my_struct) == 1 ? "Test Init passed" : "Test Init Failed");

    printf("%s \n", test_my_struct_copy(my_struct) == 1 ? "Test Copy passed" : "Test Copy Failed");

    printf("%s \n", test_my_struct_cmp(my_struct) == 1 ? "Test CMP passed" : "Test CMP Failed");

    my_struct_free(my_struct);

    return 0;
}