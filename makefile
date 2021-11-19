prog : 
	gcc -o vector_v1_double.o test_vector_v1_double

vector_v1_double.o : vector_v1_double.c
	gcc -c -Wall vector_v1_double.c

test_vector_v1_double.o : test_vector_v1_double.c
	gcc -c -Wall test_vector_v1_double.c