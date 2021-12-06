//
// Created by remid on 30/11/2021.
//
#include <stdio.h>
#include <time.h>
#include "random.h"

/**
 * T.U. on random_double
 *
 * @return 1 if passed -1 otherwise
 */
int test_random_double(){
    double a = 1.0;
    double b = 4.0;
    double random = random_double(a, b);

    if(random < a && random >= b){
        printf("Expected a random number in interval [%lf, %lf[ but was %lf", a, b, random);
        return -1;
    }

    a = 1.8;
    b = 4.8;
    random = random_double(a, b);

    if(random < a && random >= b){
        printf("Expected a random number in interval [%lf, %lf[ but was %lf", a, b, random);
        return -1;
    }

    return 1;
}

/**
 * T.U. on random_float
 *
 * @return 1 if passed -1 otherwise
 */
int test_random_float(){
    float a = 1.5f;
    float b = 4.5f;
    float random = random_float(a, b);

    if(random < a && random >= b){
        printf("Expected a random number in interval [%lf, %lf[ but was %lf", a, b, random);
        return -1;
    }

    a = 8.5f;
    b = 12.5f;
    random = random_double(a, b);

    if(random < a && random >= b){
        printf("Expected a random number in interval [%lf, %lf[ but was %lf", a, b, random);
        return -1;
    }

    return 1;
}

/**
 * T.U. on random_size_t
 *
 * @return 1 if passed -1 otherwise
 */
int test_random_size_t(){
    size_t a = 5;
    size_t b = 10;
    size_t random = random_size_t(a, b);

    if(random < a && random >= b){
        printf("Expected a random number in interval [%lu, %lu[ but was %lu", (unsigned long) a, (unsigned long) b, (unsigned long) random);
        return -1;
    }

    a = 8;
    b = 12;
    random = random_size_t(a, b);

    if(random < a && random >= b){
        printf("Expected a random number in interval [%lu, %lu[ but was %lu", (unsigned long) a, (unsigned long) b, (unsigned long) random);
        return -1;
    }

    return 1;
}

/**
 * T.U. on random_int
 *
 * @return 1 if passed -1 otherwise
 */
int test_random_int(){
    int a = 5;
    int b = 10;
    int random = random_int(a, b);

    if(random < a && random >= b){
        printf("Expected a random number in interval [%d, %d[ but was %d", a, b, random);
        return -1;
    }

    a = 8;
    b = 12;
    random = random_size_t(a, b);

    if(random < a && random >= b){
        printf("Expected a random number in interval [%d, %d[ but was %d", a, b, random);
        return -1;
    }

    return 1;
}

/**
 * T.U. on random_uchar
 *
 * @return 1 if passed -1 otherwise
 */
int test_random_uchar(){
    unsigned char a = 'a';
    unsigned char b = 'z';
    unsigned char random = random_uchar(a, b);

    if(random < a && random >= b){
        printf("Expected a random char in interval [%c, %c[ but was %c", a, b, random);
        return -1;
    }

    a = 'a';
    b = 'd';
    random = random_uchar(a, b);

    if(random < a && random >= b){
        printf("Expected a random number in interval [%c, %c[ but was %c", a, b, random);
        return -1;
    }

    return 1;
}

/**
 * T.U. on random_init_string
 *
 * @return 1 if passed -1 otherwise
 */
int test_random_init_string(){
    size_t n = 20;
    int isPassed = 1;
    unsigned char* string = (unsigned char*) malloc(sizeof(unsigned char) * n);
    unsigned char a = 'a';
    unsigned char b = 'z';
    random_init_string(string, n);

    for(size_t i = 0; string[i] != '\0'; ++i){
        if(string[i] < a && string[i] >= b){
            printf("Expected a random char in interval [%c, %c[ but was %c", a, b, string[i]);
            isPassed = -1;
        }
    }

    free(string);
    return isPassed;
}

int main(int argc, char *argv[]){
    time_t t = 0;
    time(&t);
    srand(t);

    printf("%s \n", test_random_double() == 1 ? "Test Random double passed" : "Test Random double Failed");

    printf("%s \n", test_random_float() == 1 ? "Test Random float passed" : "Test Random float Failed");

    printf("%s \n", test_random_size_t() == 1 ? "Test Random size_t passed" : "Test Random size_t Failed");

    printf("%s \n", test_random_int() == 1 ? "Test Random int passed" : "Test Random int Failed");

    printf("%s \n", test_random_uchar() == 1 ? "Test Random uchar passed" : "Test Random uchar Failed");

    printf("%s \n", test_random_init_string() == 1 ? "Test Random String passed" : "Test Random String Failed");

    return 0;
}