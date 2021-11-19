prog : 
	gcc -o vector_v1_double.o

vector_v1_double.o : vector_v1_double.c
	gcc -c -Wall vector_v1_double.c