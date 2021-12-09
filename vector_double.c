//
// Created by remid on 18/11/2021.
//
#include "vector.h"

#ifdef V2

/**
 * Alloc in memory a vector with a tab.
 *
 * @param n Number of 0.0 set in the tab
 *
 * @return A pointer on struct vector or NULL if have error.
 *
 * @throws MallocException Display CMD message if we can't allocate memory
 */
p_s_vector vector_alloc(size_t n)
{
    //Allocate vector
    p_s_vector vector = (p_s_vector)malloc(sizeof(s_vector));

    //If vector is NULL then return NULL
    if (vector == NULL)
    {
        printf("Error to allocating memory\n");
        return NULL;
    }

    //Allocate Tab
    size_t capacity = n + 16;
    vector->tab = (double *)malloc(sizeof(double) * capacity);

    //If tab is NULL then return NULL
    if (vector->tab == NULL)
    {
        printf("Error to allocating memory\n");
        free(vector);
        return NULL;
    }

    vector->size = n;
    vector->capacity = capacity;

    //Define n 0.0
    for (size_t i = 0; i < vector->size; i++)
    {
        vector_set(vector, i, 0.0);
    }

    return vector;
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
 * @throws ErrorLimit Display CMD message if user try to insert with i > size
 * @throws ErrorEmptyArray Display CMD message if the tab is empty
 * @throws MallocException Display CMD message if we can't allocate memory
 * @throws ReallocException Display CMD message if we can't reallocate memory
 */
void vector_insert(p_s_vector p_vector, size_t i, double v)
{
    //Verify If user doesn't insert over the size of the tab.
    if (i > vector_size(p_vector))
    {
        printf("Error limit of the array is [%d; %lu[\n", 0, (unsigned long)vector_size(p_vector));
        return;
    }

    //We extend the size to add element
    ++p_vector->size;

    if (vector_size(p_vector) >= vector_capacity(p_vector))
    {
        p_vector->capacity *= 2;
        //We reallocate memory of the tab with new capacity
        p_vector->tab = realloc(p_vector->tab, sizeof(double) * p_vector->capacity);

        //If p_vector->tab was NULL we display error
        if (p_vector->tab == NULL)
        {
            printf("Error to realloc p_vector->tab !");
            return;
        }
    }

    //We define a limit [i; size[
    size_t sizeEndArray = vector_size(p_vector) - i;

    //We allocate a temp tab to get the end of the tab
    double *tmpEndArray = (double *)malloc(sizeof(double) * sizeEndArray);

    //If tmpEndArray was NULL we display error
    if (tmpEndArray == NULL)
    {
        printf("Error to allocating tmpEndArray\n");
        return;
    }

    //Get the elements in limit of [i; size[
    for (size_t j = 0; j < sizeEndArray; ++j)
    {
        tmpEndArray[j] = vector_get(p_vector, j + i);
    }

    //Define new value at i index
    vector_set(p_vector, i, v);

    //Insert elements in ]i; size[ limit
    for (size_t j = 0; j < sizeEndArray - 1; ++j)
    {
        vector_set(p_vector, j + i + 1, tmpEndArray[j]);
    }

    //Free tmpEndArray and set it to NULL
    free(tmpEndArray);
    tmpEndArray = NULL;
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
 * @throws ErrorLimit Display CMD message if user try to erase with i >= size
 * @throws ErrorEmptyArray Display CMD message if the tab is empty
 * @throws MallocException Display CMD message if we can't allocate memory
 * @throws ReallocException Display CMD message if we can't reallocate memory
 */
void vector_erase(p_s_vector p_vector, size_t i)
{
    //Verify If user doesn't erase from the size of the tab.
    if (i >= vector_size(p_vector))
    {
        printf("Error limit of the array is [%d; %lu[\n", 0, (unsigned long)vector_size(p_vector));
        return;
    }

    //If tab is empty we display error
    if (vector_empty(p_vector) == 1)
    {
        printf("Error the array it's empty !\n");
        return;
    }

    //We define ]i; size[ limit
    size_t iNext = i + 1;
    size_t sizeEndArray = vector_size(p_vector) - iNext;

    //Allocate temp tab
    double *tmpEndArray = (double *)malloc(sizeof(double) * sizeEndArray);

    //If tmpEndArray was NULL we display error
    if (tmpEndArray == NULL)
    {
        printf("Error to allocating memory\n");
        return;
    }

    //Get elements in ]i; size[ limit
    for (size_t j = 0; j < sizeEndArray; ++j)
    {
        tmpEndArray[j] = vector_get(p_vector, j + iNext);
    }

    //Set elements in [i; size[ limit, to errase the element at i
    for (size_t j = 0; j < sizeEndArray; ++j)
    {
        //We use j at offset, because tmpEndArray and p_vector->tab doesn't have the same size
        vector_set(p_vector, j + i, tmpEndArray[j]);
    }

    //Free tmpEndArray and set it to NULL
    free(tmpEndArray);
    tmpEndArray = NULL;

    //Reduce the size
    --p_vector->size;

    if (vector_size(p_vector) <= vector_capacity(p_vector) / 4)
    {
        p_vector->capacity /= 4;

        //Reallocate the memory with a reduced size tab
        p_vector->tab = realloc(p_vector->tab, sizeof(double) * p_vector->capacity);

        //If p_vector->tab was NULL we display error
        if (p_vector->tab == NULL)
        {
            printf("Error to realloc p_vector->tab\n");
            return;
        }
    }
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

/**
 * Display vector struct with it values in CMD.
 *
 * @param p_vector A pointer on struct vector
 */
void toString(p_s_vector p_vector)
{
    printf("p_vector{\n tab : [");

    size_t size = vector_size(p_vector);
    for (size_t i = 0; i < size; i++)
    {
        printf("%f", vector_get(p_vector, i));

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
#else

/**
 * Alloc in memory a vector with a tab.
 *
 * @param n Number of 0.0 set in the tab
 *
 * @return A pointer on struct vector or NULL if have error.
 *
 * @throws MallocException Display CMD message if we can't allocate memory
 */
p_s_vector vector_alloc(size_t n)
{
    //Allocate vector
    p_s_vector vector = (p_s_vector)malloc(sizeof(s_vector));

    //If vector is NULL then return NULL
    if (vector == NULL)
    {
        printf("Error to allocating memory\n");
        return NULL;
    }

    //Allocate Tab
    vector->tab = (double *)malloc(sizeof(double) * n);

    //If tab is NULL then return NULL
    if (vector->tab == NULL)
    {
        printf("Error to allocating memory\n");
        free(vector);
        return NULL;
    }

    vector->size = n;

    //Define n 0.0
    for (size_t i = 0; i < vector->size; i++)
    {
        vector_set(vector, i, 0.0);
    }

    return vector;
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
 * @throws ErrorLimit Display CMD message if user try to insert with i > size
 * @throws ErrorEmptyArray Display CMD message if the tab is empty
 * @throws MallocException Display CMD message if we can't allocate memory
 * @throws ReallocException Display CMD message if we can't reallocate memory
 */
void vector_insert(p_s_vector p_vector, size_t i, double v)
{
    //Verify If user doesn't insert over the size of the tab.
    if (i > vector_size(p_vector))
    {
        printf("Error limit of the array is [%d; %lu[\n", 0, (unsigned long)vector_size(p_vector));
        return;
    }

    //We extend the size to add element
    ++p_vector->size;

    //We reallocate memory of the tab with new size
    p_vector->tab = realloc(p_vector->tab, sizeof(double) * vector_size(p_vector));

    //If p_vector->tab was NULL we display error
    if (p_vector->tab == NULL)
    {
        printf("Error to realloc p_vector->tab !");
        return;
    }

    //We define a limit [i; size[
    size_t sizeEndArray = vector_size(p_vector) - i;

    //We allocate a temp tab to get the end of the tab
    double *tmpEndArray = (double *)malloc(sizeof(double) * sizeEndArray);

    //If tmpEndArray was NULL we display error
    if (tmpEndArray == NULL)
    {
        printf("Error to allocating tmpEndArray\n");
        return;
    }

    //Get the elements in limit of [i; size[
    for (size_t j = 0; j < sizeEndArray; ++j)
    {
        tmpEndArray[j] = vector_get(p_vector, j + i);
    }

    //Define new value at i index
    vector_set(p_vector, i, v);

    //Insert elements in ]i; size[ limit
    for (size_t j = 0; j < sizeEndArray - 1; ++j)
    {
        vector_set(p_vector, j + i + 1, tmpEndArray[j]);
    }

    //Free tmpEndArray and set it to NULL
    free(tmpEndArray);
    tmpEndArray = NULL;
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
 * @throws ErrorLimit Display CMD message if user try to erase with i >= size
 * @throws ErrorEmptyArray Display CMD message if the tab is empty
 * @throws MallocException Display CMD message if we can't allocate memory
 * @throws ReallocException Display CMD message if we can't reallocate memory
 */
void vector_erase(p_s_vector p_vector, size_t i)
{
    //Verify If user doesn't erase from the size of the tab.
    if (i >= vector_size(p_vector))
    {
        printf("Error limit of the array is [%d; %lu[\n", 0, (unsigned long)vector_size(p_vector));
        return;
    }

    //If tab is empty we display error
    if (vector_empty(p_vector) == 1)
    {
        printf("Error the array it's empty !\n");
        return;
    }

    //We define ]i; size[ limit
    size_t iNext = i + 1;
    size_t sizeEndArray = vector_size(p_vector) - iNext;

    //Allocate temp tab
    double *tmpEndArray = (double *)malloc(sizeof(double) * sizeEndArray);

    //If tmpEndArray was NULL we display error
    if (tmpEndArray == NULL)
    {
        printf("Error to allocating memory\n");
        return;
    }

    //Get elements in ]i; size[ limit
    for (size_t j = 0; j < sizeEndArray; ++j)
    {
        tmpEndArray[j] = vector_get(p_vector, j + iNext);
    }

    //Set elements in [i; size[ limit, to errase the element at i
    for (size_t j = 0; j < sizeEndArray; ++j)
    {
        //We use j at offset, because tmpEndArray and p_vector->tab doesn't have the same size
        vector_set(p_vector, j + i, tmpEndArray[j]);
    }

    //Free tmpEndArray and set it to NULL
    free(tmpEndArray);
    tmpEndArray = NULL;

    //Reallocate the memory with a reduced size tab
    p_vector->tab = realloc(p_vector->tab, sizeof(double) * vector_size(p_vector) - 1);

    //If p_vector->tab was NULL we display error
    if (p_vector->tab == NULL)
    {
        printf("Error to realloc p_vector->tab\n");
        return;
    }

    //Reduce the size
    --p_vector->size;
}

/**
 * Display vector struct with it values in CMD.
 *
 * @param p_vector A pointer on struct vector
 */
void toString(p_s_vector p_vector)
{
    printf("p_vector{\n tab : [");

    size_t size = vector_size(p_vector);
    for (size_t i = 0; i < size; i++)
    {
        printf("%f", vector_get(p_vector, i));

        if (i < size - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
    printf("size : %lu\n", (unsigned long)size);
    printf("};\n");
}
#endif

/**
 * Get element à la position i
 *
 * @param p_vector A pointer on struct vector
 * @param i The index of the element à récupérer
 *
 * @return Value at the index i
 *
 * @throws ErrorLimit Display CMD message if user try to get with i >= size
 */
double vector_get(p_s_vector p_vector, size_t i)
{
    //Verifie si l'utilisateur ne récupère pas après l'indice max
    if (i >= vector_size(p_vector))
    {
        printf("Error limit of the array is [%d; %lu[\n", 0, (unsigned long)vector_size(p_vector));
        return -1;
    }

    return p_vector->tab[i];
}

/**
 * Modify element at i position
 *
 * @param p_vector A pointer on struct vector
 * @param i The index of the element à modifier
 * @param v Value to set at index i
 *
 * @throws ErrorLimit Display CMD message if user try to modify with i >= size
 */
void vector_set(p_s_vector p_vector, size_t i, double v)
{
    //Verify If user doesn't erase from the size of the tab.
    if (i >= vector_size(p_vector))
    {
        printf("Error limit of the array is [%d; %lu[\n", 0, (unsigned long)vector_size(p_vector));
        return;
    }

    p_vector->tab[i] = v;
}

/**
 * Free the pointer dynamically allocate
 *
 * @param p_vector A pointer on struct vector
 */
void vector_free(p_s_vector p_vector)
{
    //Free tab, pointer and set it to NULL
    free(p_vector->tab);
    free(p_vector);
    p_vector = NULL;
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
void vector_push_back(p_s_vector p_vector, double v)
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
    //Last element index was defined by size - 1;
    vector_erase(p_vector, vector_size(p_vector) - 1);
}

/**
 * Erase all elements of tab with reallocating memory.
 * Set the size to 0.
 *
 * @param p_vector A pointer on struct vector
 *
 * @throws MallocException Display CMD message if we can't allocate memory
 */
void vector_clear(p_s_vector p_vector)
{
    //Set size to 0, free old tab and allocate memory
    free(p_vector->tab);
    p_vector->tab = malloc(sizeof(double) * 0);

    //If tab is empty we display error
    if (p_vector->tab == NULL)
    {
        printf("Error to alloc p_vector->tab for cleaning\n");
        return;
    }
    p_vector->size = 0;
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