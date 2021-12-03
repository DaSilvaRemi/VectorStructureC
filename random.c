//
// Created by remid on 30/11/2021.
//
#include "random.h"


double random_double(double a, double b){
    return a + ((((double) rand()) / (double) RAND_MAX) * (b - a));
}

float random_float(float a, float b){
    return a + ((((float) rand()) / (float) RAND_MAX) * (b - a));
}

size_t random_size_t(size_t a, size_t b) {
    return (size_t) random_float((float) a, (float) b);
}

int random_int(int a, int b) {
    return (int) random_float((float) a, (float) b);
}

unsigned char random_uchar(unsigned char a, unsigned char b) {
    return (unsigned char) random_int(a, b);
}

void random_init_string(unsigned char* c, size_t n) {
    for(size_t i = 0; i < n; i++){
        c[i] = random_uchar('A', 'Z');
    }
    c[n-1] = '\0';
}