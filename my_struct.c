//
// Created by remid on 03/12/2021.
//
#include "my_struct.h"

/**
 * @brief Allocate the structure
 *
 * @return p_s_my_struct A pointer to my_struct type
 */
p_s_my_struct my_struct_alloc()
{
    // Allocate struct
    p_s_my_struct my_struct = (p_s_my_struct)malloc(sizeof(s_my_struct));

    // If struct is NULL then return NULL
    if (my_struct == NULL)
    {
        printf("Error : my_struct was nos allocate ! \n");
        return NULL;
    }

    my_struct->str = NULL;
    my_struct->nb = 0.0;
    my_struct_randoms_init(my_struct);

    return my_struct;
}

/**
 * @brief Free the struct
 *
 * @param p_my_struct A pointer to the struct
 */
void my_struct_free(p_s_my_struct p_my_struct)
{
    free(p_my_struct->str);
    free(p_my_struct);
    p_my_struct = NULL;
}

/**
 * @brief Init randomyly a struct
 *
 * @param p_my_struct A pointer to the struct
 */
void my_struct_randoms_init(p_s_my_struct p_my_struct)
{
    size_t size = random_size_t(10, 50);

    p_my_struct->str = (unsigned char *)malloc(sizeof(unsigned char) * size);

    // If struct is NULL then return NULL
    if (p_my_struct->str == NULL)
    {
        printf("Error : str was nos allocate ! \n");
        return;
    }

    random_init_string(p_my_struct->str, size);
    p_my_struct->nb = random_double(0, 50);
}

/**
 * @brief Copy a structure
 *
 * @param p_dest The struct will receive the data
 * @param p_src The struct will give the data
 */
void my_struct_copy(p_s_my_struct p_dest, p_s_my_struct p_src)
{
    if (p_src == NULL)
    {
        printf("p_src was NULL\n");
        return;
    }
    else if (p_dest == NULL)
    {
        printf("p_dest was NULL\n");
        return;
    }
    else if (p_src->str == NULL)
    {
        printf("Error p_src->str was null !\n");
        return;
    }

    p_dest->nb = p_src->nb;
    p_dest->str = realloc(p_dest->str, sizeof(unsigned char *) * strlen((const char *)p_src->str));

    if (p_dest->str == NULL)
    {
        printf("Error : str was not allocate ! \n");
        return;
    }

    size_t i = 0;
    while (p_src->str[i] != '\0')
    {
        p_dest->str[i] = p_src->str[i];
        ;
        ++i;
    }

    p_dest->str[i] = '\0';
}

/**
 * @brief Compare both structure
 *
 * @param p_struct_a The first struct to compare
 * @param p_struct_b The second struct to compare
 * @return int 0 If is Equal, -1 If the first structure is before the second, 1 If the first structure is after the second and 404 if an error was occured
 */
int my_struct_cmp(p_s_my_struct p_struct_a, p_s_my_struct p_struct_b)
{
    // Check if the user doesn't pass NULL value
    if (p_struct_a == NULL || p_struct_b == NULL)
    {
        printf("p_struct_a && p_struct_b was NULL");
        return 404;
    }
    else if (p_struct_a->str == NULL || p_struct_b->str == NULL)
    {
        printf("Error str was null !!!");
        return 404;
    }

    // Compare both number
    if (p_struct_a->nb > p_struct_b->nb)
    {
        return 1;
    }
    else if (p_struct_a->nb < p_struct_b->nb)
    {
        return -1;
    }
    else
    {
        // If both number are equal so we compare the string
        int result = strcmp((char const *)p_struct_a->str, (char const *)p_struct_b->str);
        return result > 0 ? 1 : result < 0 ? -1: 0;
    }
}