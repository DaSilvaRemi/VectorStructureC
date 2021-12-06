//
// Created by remid on 03/12/2021.
//

#ifndef _MY_STRUCT_H
#define _MY_STRUCT_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct struct_my_struct{
    unsigned char * str;
    double nb;
};

typedef struct struct_my_struct s_my_struct
typedef s_my_struct* p_s_my_struct

p_s_my_struct my_struct_alloc();
void my_struct_free(p_s_my_struct p_vector);
void my_struct_randoms_init(p_s_my_struct p_vector);
void my_struct_copy(p_s_my_struct p_dest, p_s_my_struct p_src);
int my_struct_cmp(p_s_my_struct p_vector_a, p_s_my_struct p_vector_b);
size_t str_len(unsigned char* s);

#endif //_MY_STRUCT_H