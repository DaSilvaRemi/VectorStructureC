//
// Created by remid on 18/11/2021.
//
#include "vector.h"

/**
 * Alloc in memory a vector with a tab.
 *
 * @param n Number of 0.0 set in the tab
 *
 * @return A pointer on struct vector or NULL if have error.
 *
 * @throw MallocException Display CMD message if we can't allocate memory
 */
p_s_vector vector_alloc(size_t n, t_data_alloc alloc_func, t_data_free free_func, t_data_cpy cpy_func)
{
    // Allocate vector
    p_s_vector vector = (p_s_vector)malloc(sizeof(s_vector));

    // If vector is NULL then return NULL
    if (vector == NULL)
    {
        printf("Error to allocating memory\n");
        return NULL;
    }

    // Allocate Tab
    size_t capacity = n + 16;
    vector->tab = (void **)malloc(sizeof(void *) * capacity);

    // If tab is NULL then return NULL
    if (vector->tab == NULL)
    {
        printf("Error to allocating memory\n");
        free(vector);
        return NULL;
    }

    // Define STRUCT values
    vector->size = n;
    vector->capacity = capacity;
    vector->alloc_func = alloc_func;
    vector->free_func = free_func;
    vector->cpy_func = cpy_func;

    // Define n NULL
    for (size_t i = 0; i < vector->capacity; i++)
    {
        vector->tab[i] = (*vector->alloc_func)();
    }

    return vector;
}

/**
 * Free the pointer dynamically allocate
 *
 * @param p_vector A pointer on struct vector
 */
void vector_free(p_s_vector p_vector)
{
    if (p_vector == NULL)
    {
        printf("Error you passing a pointer set to null\n");
        return;
    }
    // Free tab, pointer and set it to NULL
    vector_free_tab(p_vector);
    free(p_vector);
    p_vector = NULL;
}

/**
 * @brief Free the tab
 *
 * @param p_vector A pointer on struct vector
 */
void vector_free_tab(p_s_vector p_vector)
{
    if (p_vector == NULL)
    {
        printf("Error you passing a p_vector set to null\n");
        return;
    }
    else if (p_vector->tab == NULL)
    {
        printf("Error you passing a p_vector->tab set to null\n");
        return;
    }

    for (size_t i = 0; i < p_vector->capacity; ++i)
    {
        (*p_vector->free_func)(p_vector->tab[i]);
    }

    free(p_vector->tab);
    p_vector->tab = NULL;
}

/**
 * Get element at position i
 *
 * @param p_vector A pointer on struct vector
 * @param i The index of the element à récupérer
 *
 * @return Value at the index i
 *
 * @throw ErrorLimit Display CMD message if user try to get with i >= size
 */
int vector_get(p_s_vector p_vector, size_t i, void *p_data)
{
    // Verify If user doesn't erase from the size of the tab.
    if (i >= vector_size(p_vector))
    {
        printf("Error limit of the array is [%d; %lu[\n", 0, (unsigned long)vector_size(p_vector));
        return -1;
    }
    else if (p_data == NULL)
    {
        printf("Error p_data it's a NULL value\n");
        return -1;
    }

    (*p_vector->cpy_func)(p_vector->tab[i], p_data);
    return 0;
}

/**
 * Modify element at i position
 *
 * @param p_vector A pointer on struct vector
 * @param i The index of the element à modifier
 * @param v Value to set at index i
 *
 * @throw ErrorLimit Display CMD message if user try to modify with i >= size
 */
void vector_set(p_s_vector p_vector, size_t i, void *v)
{
    // Verify If user doesn't erase from the size of the tab.
    if (i >= vector_size(p_vector))
    {
        printf("Error limit of the array is [%d; %lu[\n", 0, (unsigned long)vector_size(p_vector));
        return;
    }

    (*p_vector->cpy_func)(p_vector->tab[i], v);
}

/**
 * Insert an element at i index.
 * Extend size et shift to the right all elements which start at indice i. To insert the new element before actual
 * element at i.
 *
 * @example We defined a tab with a size of 3 : [0.0, 1, 0.0]
 * We insert 4.0 at position 1, the tab will be [0.0, 4.0, 1.0, 0.0]
 *
 * @param p_vector A pointer on struct vector
 * @param i The index of the element à insérer
 * @param v Value to set at i index
 *
 * @throw ErrorLimit Display CMD message if user try to insert with i > size
 * @throw ErrorEmptyArray Display CMD message if the tab is empty
 * @throw MallocException Display CMD message if we can't allocate memory
 * @throw ReallocException Display CMD message if we can't reallocate memory
 */
void vector_insert(p_s_vector p_vector, size_t i, void *v)
{
    // Verify If user doesn't insert over the size of the tab.
    if (i > vector_size(p_vector))
    {
        printf("Error limit of the array is [%d; %lu[\n", 0, (unsigned long)vector_size(p_vector));
        return;
    }

    // We extend the size to add element
    ++p_vector->size;

    if (vector_size(p_vector) >= vector_capacity(p_vector))
    {
        p_vector->capacity *= 2;
        // We reallocate memory of the tab with new capacity
        p_vector->tab = realloc(p_vector->tab, sizeof(void *) * p_vector->capacity);

        // If p_vector->tab was NULL we display error
        if (p_vector->tab == NULL)
        {
            printf("Error to realloc p_vector->tab !\n");
            return;
        }

        for (size_t i = p_vector->size; i < p_vector->capacity; i++)
        {
            p_vector->tab[i] = (*p_vector->alloc_func)();
        }
    }

    // We define a limit [i; size[
    size_t size_end_array = vector_size(p_vector) - i;

    // We allocate a temp vector to get the end of the tab
    p_s_vector tmp_vector = vector_alloc(sizeEndArray, p_vector->alloc_func, p_vector->free_func, p_vector->cpy_func);

    // If tmpEndArray was NULL we display error
    if (tmp_vector == NULL)
    {
        printf("Error to allocating tmp_vector\n");
        return;
    }

    // Get the elements in limit of [i; size[
    for (size_t j = 0; j < size_end_array; ++j)
    {
        vector_set(tmp_vector, j, p_vector->tab[j + i]);
    }

    // Define new value at i index
    vector_set(p_vector, i, v);

    // Insert elements in ]i; size[ limit
    for (size_t j = 0; j < size_end_array - 1; ++j)
    {
        vector_set(p_vector, j + i + 1, tmp_vector->tab[j]);
    }

    // Free tmp_vector and set it to NULL
    vector_free(tmp_vector);
}

/**
 * Erase element at position i.
 * Reduce tab size and allocate memory size.
 *
 * @example We defined a tab with a size of 3 : [0.0, 1, 0.0]
 * We suppr the element at the position 1. Tab values will be [0.0, 1.0] and the size will be 2.
 *
 * @param p_vector A pointer on struct vector
 * @param i The index of the element to erase
 *
 * @throw ErrorLimit Display CMD message if user try to erase with i >= size
 * @throw ErrorEmptyArray Display CMD message if the tab is empty
 * @throw MallocException Display CMD message if we can't allocate memory
 * @throw ReallocException Display CMD message if we can't reallocate memory
 */
void vector_erase(p_s_vector p_vector, size_t i)
{
    // Verify If user doesn't erase from the size of the tab.
    if (i >= vector_size(p_vector))
    {
        printf("Error limit of the array is [%d; %lu[\n", 0, (unsigned long)vector_size(p_vector));
        return;
    }

    // If tab is empty we display error
    if (vector_empty(p_vector) == 1)
    {
        printf("Error the array it's empty !\n");
        return;
    }

    // We define ]i; size[ limit
    size_t i_next = i + 1;
    size_t size_end_array = vector_size(p_vector) - i_next;

    // Allocate temp tab
    p_s_vector tmp_vector = vector_alloc(sizeEndArray, p_vector->alloc_func, p_vector->free_func, p_vector->cpy_func);

    // If tmp_vector was NULL we display error
    if (tmp_vector == NULL)
    {
        printf("Error to allocating memory\n");
        return;
    }

    // Get elements in ]i; size[ limit
    for (size_t j = 0; j < size_end_array; ++j)
    {
        vector_set(tmp_vector, j, p_vector->tab[j + i_next]);
    }

    // Set elements in [i; size[ limit, to erase the element at i
    for (size_t j = 0; j < size_end_array; ++j)
    {
        // We use j at offset, because tmp_vector and p_vector->tab doesn't have the same size
        vector_set(p_vector, j + i, tmp_vector->tab[j]);
    }

    // Free tmp_vector and set it to NULL
    vector_free(tmp_vector);

    // Reduce the size
    --p_vector->size;

    if (vector_size(p_vector) <= vector_capacity(p_vector) / 4)
    {
        for (size_t i = p_vector->size; i < p_vector->capacity; ++i)
        {
            (*p_vector->free_func)(p_vector->tab[i]);
        }

        p_vector->capacity /= 4;

        // Reallocate the memory with a reduced size tab
        p_vector->tab = realloc(p_vector->tab, sizeof(double) * p_vector->capacity);

        // If p_vector->tab was NULL we display error
        if (p_vector->tab == NULL)
        {
            printf("Error to realloc p_vector->tab after erase\n");
            return;
        }
    }
}

/**
 * Add element at the end.
 *
 * Take i = tab size to insert, @see vector_insert for insert and resize.
 * The size will automatiqualy resize to insert at new size - 1 which is the old size.
 *
 * @example We defined a tab with a size of 3 : [0.0, 1.0, 0.0].
 * We insert 4.0 in the end so at position 3.
 * The values of the tab will be [0.0, 0.0, 1.0, 4.0], the size will be 4.
 *
 * @param p_vector A pointer on struct vector
 * @param v The value to insert
 */
void vector_push_back(p_s_vector p_vector, void *v)
{
    vector_insert(p_vector, vector_size(p_vector), v);
}

/**
 * Erase the last element.
 *
 * Take i = tab size -1 to erase, @see vector_erase to suppress and reducing size.
 *
 * @example We defined a tab with a size of 3 : [0.0, 4.0, 0.0].
 * We delete the last element. The value of tab will be [0.0, 4.0] and the size will be 2.
 *
 * @param p_vector A pointer on struct vector
 */
void vector_pop_back(p_s_vector p_vector)
{
    // Last element index was defined by size - 1;
    vector_erase(p_vector, vector_size(p_vector) - 1);
}

/**
 * Return if the tab is empty if the size is equal to 0.
 *
 * @param p_vector A pointer on struct vector
 *
 * @return 1 if tab is empty else 0
 */
int vector_empty(p_s_vector p_vector)
{
    return vector_size(p_vector) == 0 ? 1 : 0;
}

/**
 * Erase all elements of tab with reallocating memory.
 * Set the size to 0.
 *
 * @param p_vector A pointer on struct vector
 *
 * @throw MallocException Display CMD message if we can't allocate memory
 */
void vector_clear(p_s_vector p_vector)
{
    vector_free_tab(p_vector);

    p_vector->size = 0;
    p_vector->capacity = 16;

    p_vector->tab = (void **)malloc(sizeof(void *) * p_vector->capacity);

    if (p_vector->tab == NULL)
    {
        printf("Error to alloc p_vector->tab for cleaning\n");
        return;
    }

    for (size_t i = 0; i < p_vector->capacity; i++)
    {
        p_vector->tab[i] = (*p_vector->alloc_func)();
    }
}

/**
 * Display vector struct with it values in CMD.
 *
 * @param p_vector A pointer on struct vector
 */
void toString(p_s_vector p_vector)
{
    printf("p_vector{\n tab : [\n");

    void *element = NULL;

    size_t size = vector_size(p_vector);
    for (size_t i = 0; i < size; i++)
    {
        element = p_vector->tab[i];
        printf("%p", element);

        if (i < size - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
    printf("size : %lu\n", (unsigned long)size);
    printf("capacity : %lu\n", (unsigned long)vector_capacity(p_vector));
    printf("};\n");
}

/**
 * Return the size of the tab
 *
 * @param p_vector A pointer on struct vector
 *
 * @returns The size of the tab
 */
size_t vector_size(p_s_vector p_vector)
{
    return p_vector->size;
}

/**
 * Get the capacity of the vector
 *
 * @param p_vector A pointer in the vector
 * @return The capacity of the vector
 */
size_t vector_capacity(p_s_vector p_vector)
{
    return p_vector->capacity;
}
