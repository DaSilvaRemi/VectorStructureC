//
// Created by remid on 30/11/2021.
//
#include "random.h"

/**
 * Generate a random double number between [a; b[
 *
 * @param a The start of the limit
 * @param b The end of the limit
 * @return int random double
 */
double random_double(double a, double b)
{
    return a + ((((double)rand()) / (double)RAND_MAX) * (b - a));
}

/**
 * Generate a random float number between [a; b[
 *
 * @param a The start of the limit
 * @param b The end of the limit
 * @return int random float
 */
float random_float(float a, float b)
{
    return a + ((((float)rand()) / (float)RAND_MAX) * (b - a));
}

/**
 * Generate a random size_t number between [a; b[
 *
 * @param a The start of the limit
 * @param b The end of the limit
 * @return int random size_t
 */
size_t random_size_t(size_t a, size_t b)
{
    return (size_t)random_float((float)a, (float)b);
}

/**
 * Generate a random int number between [a; b[
 *
 * @param a The start of the limit
 * @param b The end of the limit
 * @return int random int
 */
int random_int(int a, int b)
{
    return (int)random_float((float)a, (float)b);
}

/**
 * Generate a random uchar between [a; b[
 *
 * @param a The start of the limit
 * @param b The end of the limit
 * @return int random uchar
 */
unsigned char random_uchar(unsigned char a, unsigned char b)
{
    return (unsigned char)random_int(a, b);
}

/**
 * Generate a string with random char
 *
 * @param c a string
 * @param n the size of the string
 */
void random_init_string(unsigned char *c, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        c[i] = random_uchar('A', 'Z');
    }
    c[n - 1] = '\0';
}