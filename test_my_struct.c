//
// Created by remid on 03/12/2021.
//
#include <time.h>
#include "my_struct.h"
#include "random.h"

int test_my_struct_alloc(){
    p_s_my_struct my_struct = my_struct_alloc();

    if(my_struct == NULL){
        printf("Error : my_struct was nos allocate ! \n");
        return -1;
    }

    return 1;
}

int test_my_struct_random_init(p_s_my_struct my_struct){
    my_struct_randoms_init(my_struct);

    if(my_struct->str == NULL){
        printf("Error : str was nos allocate ! \n");
        return -1;
    }

    if(str_len(my_struct->str) > 0){
        printf("Error : expected my_struct->str > 1 but was %lu \n", (unsigned long) str_len(my_struct->str));
        return -1;
    }

    return 1;
}

int test_my_struct_copy(p_s_my_struct my_struct){
    p_s_my_struct p_dest = my_struct_alloc();
    my_struct_copy(my_struct, p_dest);

    int isPassed = 1;

    if(p_dest->str == NULL){
        printf("Error : str was nos allocate ! \n");
        isPassed = -1;
    }

    size_t realSize = str_len(p_dest->str);
    size_t expectedSize = str_len(my_struct->str);
    if(realSize != expectedSize){
        printf("Expected my_struct->str : %lu but was %lu \n", (unsigned long) realSize, (unsigned long) expectedSize);
        isPassed = -1;
    }

    for(size_t i = 0; i  < p_dest->str[i] != '\0'; ++i){
        if(my_struct->str[i] != p_dest->str[i]){
            printf("Error : expected %c but was %c \n", my_struct->str[i], p_dest->str[i]);
            isPassed = -1;
        }

    }

    my_struct_free(p_dest);
    return isPassed;
}

int test_my_struct_cmp(p_s_my_struct my_struct){

}


int main (int argc, char* argv[]){
    time_t t = 0;
    time(&t);
    srand(t);

    printf("%s \n", test_my_struct_alloc() == 1 ? "Test Allocate passed" : "Test Allocate Failed");

    printf("%s \n", test_my_struct_random_init() == 1 ? "Test Get passed" : "Test Free Failed");

    printf("%s \n", test_my_struct_copy() == 1 ? "Test Set passed" : "Test Free Failed");

    printf("%s \n", test_my_struct_cmp() == 1 ? "Test Insert passed" : "Test Insert Failed");

    return 0;
}