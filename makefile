all : test_vector

test_vector : test_vector.o vector.o
	gcc vector.o test_vector.o -g -o test_vector

vector.o : vector.c vector.h
	gcc -Wall -Wextra -g -c vector.c

test_vector.o : test_vector.c
	gcc -Wall -Wextra -g -c test_vector.c

clean :
	rm -f *.o prog