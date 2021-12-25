//
// Created by remid on 30/11/2021.
//
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "random.h"
#include "vector.h"
#include "my_struct.h"

/**
 * @brief Allocate a vector
 * 
 * @param init_size The init_size
 * @return p_s_vector The vector allocated
 */
p_s_vector allocate_random_vector(size_t init_size){
    p_s_vector p_vector = vector_alloc(init_size, (t_data_alloc)my_struct_alloc, (t_data_free)my_struct_free, (t_data_cpy)my_struct_copy);
    
    if(p_vector == NULL){
        printf("Error to allocating memory\n");
        return NULL;
    }

    return p_vector;
}

/**
 * @brief Insert and Erase at random position
 * 
 * @param p_vector The pointer to the vector
 * @param n The n time which we will execute the case
 */
void insert_erase_random(p_s_vector p_vector, size_t n){
    void* p_my_struct = my_struct_alloc();

    for(size_t i = 0; i < n; ++i){
        vector_insert(p_vector, random_size_t(0, vector_size(p_vector)), p_my_struct);
        vector_erase(p_vector, random_size_t(0, vector_size(p_vector)));
    }

    my_struct_free(p_my_struct);
    p_my_struct = NULL;
}

/**
 * @brief Insert and Erase at head
 * 
 * @param p_vector The pointer to the vector
 * @param n The n time which we will execute the case
 */
void insert_erase_head(p_s_vector p_vector, size_t n){
    void* p_my_struct = my_struct_alloc();

    for(size_t i = 0; i < n; ++i){
        vector_insert(p_vector, 0, p_my_struct);
        vector_erase(p_vector, 0);
    }

    my_struct_free(p_my_struct);
    p_my_struct = NULL;
}

/**
 * @brief Insert and Erase at tail
 * 
 * @param p_vector The pointer to the vector
 * @param n The n time which we will execute the case
 */
void insert_erase_tail(p_s_vector p_vector, size_t n){
    void* p_my_struct = my_struct_alloc();

    for(size_t i = 0; i < n; ++i){
        vector_push_back(p_vector, p_my_struct);
        vector_pop_back(p_vector);
    }

    my_struct_free(p_my_struct);
    p_my_struct = NULL;
}

/**
 * @brief Read and Write at random position
 * 
 * @param p_vector The pointer to the vector
 * @param n The n time which we will execute the case
 */
void read_write_random(p_s_vector p_vector, size_t n){
    void* p_my_struct = (void*) my_struct_alloc();
    for(size_t i = 0; i < n; ++i){
        vector_set(p_vector, random_size_t(0, vector_size(p_vector)), p_my_struct);
        vector_get(p_vector, random_size_t(0, vector_size(p_vector)), p_my_struct);
    }
    my_struct_free(p_my_struct);
}

/**
 * @brief Read and Write at sequential position
 * 
 * @param p_vector The pointer to the vector
 * @param n The n time which we will execute the case
 */
void read_write_sequential(p_s_vector p_vector, size_t n){
    void* p_my_struct = (void*) my_struct_alloc();
    for(size_t i = 0; i < n; ++i){
        for(size_t j = 0; j < vector_size(p_vector); ++j){
            vector_set(p_vector, j, p_my_struct);
            vector_get(p_vector, j, p_my_struct);
        }
    }
    my_struct_free(p_my_struct);
    p_my_struct = NULL;
}

/**
 * @brief Bubble_sort the tab
 * 
 * @param p_vector The pointer to the vector
 * @param n The n time which we will execute the case
 */
void bubble_sort(p_s_vector p_vector, size_t n){
    void* p_my_struct = (void*) my_struct_alloc();
    for(size_t i = 0; i < n; ++i){
        for(size_t j = 0; j < vector_size(p_vector); ++j){
            vector_set(p_vector, j, p_my_struct);
        }
    }

    void* p_my_struct_a = (void*) my_struct_alloc();
    void* p_my_struct_b = (void*) my_struct_alloc();

    for(size_t i = vector_size(p_vector); i > 0; --i){
        for(size_t j = 0; j < i - 1; ++j){
            vector_get(p_vector, j + 1, p_my_struct_a);
            vector_get(p_vector, j, p_my_struct_b);
            
            if(my_struct_cmp(p_my_struct_a, p_my_struct_b) == -1){
                vector_set(p_vector, j + 1, p_my_struct_b);
                vector_set(p_vector, j, p_my_struct_a);
            }
        }
    }

    my_struct_free(p_my_struct);
    my_struct_free(p_my_struct_a);
    my_struct_free(p_my_struct_b);
    p_my_struct = NULL;
    p_my_struct_a = NULL;
    p_my_struct_b = NULL;
}

/**
 * @brief Execute a test
 * 
 * @param test_type The type of the test
 * @param p_vector the vector
 * @param n the number of time the test will be executed
 */
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

/**
 * @brief Get the formated args object
 * 
 * @param argv The argv
 * @param test_type The type of test
 * @param init_size The size init
 * @param n The number of time the test will be executed
 */
void get_formated_args(char *argv[], char** test_type, size_t* init_size, size_t* n){
    *test_type = argv[1];
    sscanf(argv[2], "%zu", init_size);
    sscanf(argv[3], "%zu", n);
}

/**
 * @brief Init random generator
 * 
 */
void init_random(){
    time_t t = 0;
    time(&t);
    srand(t);
}

/**
 * @brief The main program
 * 
 * @param argc Number of argument
 * @param argv The arguments
 * @return int The error
 */
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
    vector_free(p_vector);

    return 0;
}