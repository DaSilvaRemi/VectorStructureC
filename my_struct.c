//
// Created by remid on 03/12/2021.
//
#include "my_struct.h"

p_s_my_struct my_struct_alloc(){
    //Allocate struct
    p_s_my_struct my_struct = (p_s_my_struct) malloc(sizeof(s_my_struct));

    //If struct is NULL then return NULL
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
        printf("Error : str was nos allocate ! \n");
        return;
    }

    random_init_string(p_vector->str, size);
    p_vector->nb = random_double(0, 50);
}

void my_struct_copy(p_s_my_struct p_dest, p_s_my_struct p_src){
    if(p_src == NULL || p_dest == NULL){
        printf("p_dest && p_dest was NULL");
    }

    if(p_src->str == NULL){
        printf("Error p_src->str was null !!!");
    }

    p_dest->nb = p_src->nb;
    p_dest->str = realloc(p_dest->str, sizeof(unsigned char*) * strlen((const char*) p_src->str));

    if(p_dest->str == NULL){
        printf("Error : str was nos allocate ! \n");
        return;
    }

    size_t i = 0;
    while(p_src->str[i] != '\0'){
        p_dest->str[i] = p_src->str[i];;
        ++i;
    }

    p_dest->str[i] = '\0';
}

int my_struct_cmp(p_s_my_struct p_struct_a, p_s_my_struct p_struct_b){
    if(p_struct_a == NULL || p_struct_b == NULL){
        printf("p_struct_a && p_struct_b was NULL");
    }else if(p_struct_a->str == NULL || p_struct_b->str == NULL){
        printf("Error str was null !!!");
    }


    if(p_struct_a->nb > p_struct_b->nb){
        return 1;
    }else if(p_struct_a->nb < p_struct_b->nb){
        return -1;
    }else{
        int result = strcmp((char const *) p_struct_a->str, (char const *) p_struct_b->str);
        return result > 0 ? 1 : result < 0 ? -1 : 0;
    }
}