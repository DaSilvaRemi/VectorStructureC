//
// Created by remid on 03/12/2021.
//
#include <time.h>
#include "my_struct.h"
#include "random.h"

int test_my_struct_alloc(){
    p_s_my_struct my_struct = my_struct_alloc();

    if(my_struct == NULL){
        printf("my_struct was null !");
        return -1;
    }

    return 1;
}

int test_my_struct_random_init(p_s_my_struct p_vector){
    my_struct_randoms_init(p_vector);

    if(p_vector->str == NULL){
        printf("p_vector->str was null !");
        return -1;
    }

    if(str_len(p_vector->str) > 0){
        printf("Expected p_vector->str > 1 but was %lu ", (unsigned long) str_len(p_vector->str));
        return -1;
    }

    return 1;
}

int test_my_struct_copy(p_s_my_struct p_vector){

}

int test_my_struct_cmp(p_s_my_struct p_vector){

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