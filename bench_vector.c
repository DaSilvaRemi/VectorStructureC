//
// Created by remid on 30/11/2021.
//
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "random.h"
#include "vector.h"

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

void insert_erase_head(p_s_vector p_vector, size_t n){
    for(size_t i = 0; i < n; ++i){
        vector_insert(p_vector, 0, random_double(0, 50));
        vector_erase(p_vector, 0);
    }
}

void insert_erase_tail(p_s_vector p_vector, size_t n){
    for(size_t i = 0; i < n; ++i){
        vector_push_back(p_vector, random_double(0, 50));
        vector_pop_back(p_vector);
    }
}

void read_write_random(p_s_vector p_vector, size_t n){
    for(size_t i = 0; i < n; ++i){
        vector_set(p_vector, random_size_t(0, vector_size(p_vector)), random_double(0, 50));
        vector_get(p_vector, random_size_t(0, vector_size(p_vector)));
    }
}

void read_write_sequential(p_s_vector p_vector, size_t n){
    for(size_t i = 0; i < n; ++i){
        for(size_t j = 0; j < vector_size(p_vector); ++j){
            vector_set(p_vector, j, random_double(0, 50));
            vector_get(p_vector, j);
        }
    }
}

void bubble_sort(p_s_vector p_vector, size_t n){
    for(size_t i = 0; i < n; ++i){
        vector_set(p_vector, i, random_double(0, 50));
    }

    for(size_t i = vector_size(p_vector); i > 0; --i){
        for(size_t j = 0; j < i - 1; ++j){
            double a = vector_get(p_vector, j + 1);
            double b = vector_get(p_vector, j);
            if(a < b){
                vector_set(p_vector, j + 1, b);
                vector_set(p_vector, j, a);
            }
        }
    }
}


void execute_test_type(char* test_type, p_s_vector p_vector, size_t n){
    if(strcmp(test_type, "insert_erase_random") == 0){
        insert_erase_random(p_vector, n);
    }else if(strcmp(test_type, "insert_erase_head") == 0){
        insert_erase_head(p_vector, n);
    }else if(strcmp(test_type, "insert_erase_tail") == 0){
        insert_erase_tail(p_vector, n);
    }else if(strcmp(test_type, "read_write_random") == 0){
        read_write_random(p_vector, n);
    }else if(strcmp(test_type, "read_write_sequential") == 0){
        read_write_sequential(p_vector, n);
    }else if(strcmp(test_type,"bubble_sort") == 0){
        bubble_sort(p_vector, n);
    }else{
        perror("Error option unknow !");
    }
}

void get_formated_args(char *argv[], char** test_type, size_t* init_size, size_t* n){
    *test_type = argv[1];
    sscanf(argv[2], "%zu", init_size);
    sscanf(argv[3], "%zu", n);
}

void init_random(){
    time_t t = 0;
    time(&t);
    srand(t);
}

int main(int argc, char *argv[]){
    if(argc < 4){
        printf("Error we expected 3 arguments but you send %d", argc);
        return -1;
    }

    init_random();

    char* test_type;
    size_t init_size;
    size_t n;

    get_formated_args(argv, &test_type, &init_size, &n);
    p_s_vector p_vector = allocate_random_vector(init_size);
    execute_test_type(test_type, p_vector, n);
    toString(p_vector);

    return 0;
}