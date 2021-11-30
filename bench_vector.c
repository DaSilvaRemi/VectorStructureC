//
// Created by remid on 30/11/2021.
//
#include <stdio.h>
#include <string.h>
#include "vector.h"
#include "random.h"

p_s_vector allocate_random_vector(size_t init_size){
    p_s_vector p_vector = vector_alloc(init_size);
    if(p_vector == NULL){

    }

    for(size_t i = 0; i < init_size; i++){
        vector_set(p_vector, i, random_double(0, 50));
    }

    return p_vector;
}

void insert_erase_random(p_s_vector p_vector, size_t n){
    for(size_t i = 0; i < n; ++i){
        vector_insert(p_vector, random_size_t(0, vector_size(p_vector)), random_double(0, 50));
        vector_erase(p_vector, random_size_t(0, vector_size(p_vector)));
    }
}

void execute_test_type(char* test_type){
    if(strcmp(test_type, "insert_erase_random") == 0){

    }else if(strcmp( test_type, "insert erase head") == 0){

    }else if(strcmp(test_type, "insert erase tail") == 0){

    }else if(strcmp(test_type, "read write random") == 0){

    }else if(strcmp(test_type, "read write sequential") == 0){

    }else if(strcmp(test_type,"bubble sort") == 0){

    }else{
        perror("Error option unknow !");
    }
}

void get_formated_args(int argc, char *argv[], char* test_type, size_t* init_size, size_t* n){
    test_type = argv[1];
    sscanf(argv[2], "%zu", init_size);
    sscanf(argv[3], "%zu", n);
}

int main(int argc, char *argv[]){
    if(argc < 4){
        printf("Error we expected 3 arguments but you send %d", argc);
        return -1;
    }

    char* test_type;
    size_t init_size;
    size_t n;

    get_formated_args(argc, argv, test_type, &init_size, &n);
    p_s_vector p_vector = allocate_random_vector(init_size);
    toString(p_vector);

    return 0;
}