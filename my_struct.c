//
// Created by remid on 03/12/2021.
//
#include "my_struct.h"
#include "random.h"

p_s_my_struct my_struct_alloc(){
    //Allocate struct
    p_s_my_struct my_struct = (p_s_my_struct) malloc(sizeof(s_my_struct));

    //If struct is NULL then return NULL
    if (my_struct == NULL)
    {
        printf("Error to allocating memory\n");
        return NULL;
    }

    my_struct->str = NULL;
    my_struct->nb = 0.0;

    return my_struct;
}

void my_struct_free(p_s_my_struct p_vector){
    free(p_vector->str);
    free(p_vector);
    p_vector = NULL;
}

void my_struct_randoms_init(p_s_my_struct p_vector){
    size_t size = random_size_t(1, 50);
    p_vector->str = (unsigned char*) malloc(sizeof(unsigned char) * size);

    //If struct is NULL then return NULL
    if (p_vector->str == NULL)
    {
        printf("Error to allocating memory\n");
        return;
    }

    random_init_string(p_vector->str, size);
    p_vector->nb = random_double(0, 50);
}

void my_struct_copy(p_s_my_struct p_dest, p_s_my_struct p_src){
    p_dest->nb = p_src->nb;
    p_dest->str = realloc(p_dest->str, sizeof(char*) * str_len(p_src->str));

    if(p_dest->str == NULL){
        printf("Error to allocating memory\n");
        return;
    }

    size_t i = 0;
    while(p_src->str[i] != '\0'){
        p_dest->str[i] = p_src->str[i];;
        ++i;
    }

    p_dest->str[i] = '\0';
}

int my_struct_cmp(p_s_my_struct p_vector_a, p_s_my_struct p_vector_b){
    if(p_vector_a->nb > p_vector_b->nb){
        return 1;
    }else if(p_vector_a->nb < p_vector_b->nb){
        return -1;
    }else{
        size_t p_vector_a_str_len = str_len(p_vector_a->str);
        size_t p_vector_b_str_len = str_len(p_vector_b->str);

        return p_vector_a_str_len > p_vector_b_str_len ? 1 : p_vector_a_str_len < p_vector_b_str_len ? -1 : 0;
    }
}

size_t str_len(unsigned char* s){
    size_t i = 0;

    while(str[i] != '\0'){
        ++i;
    }

    return i;
}