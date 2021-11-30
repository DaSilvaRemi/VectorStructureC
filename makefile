all : test_vector

test_vector : test_vector.o vector.o
	gcc vector.o test_vector.o -g -o test_vector

test_random : test_random.o random.o
	gcc random.o test_random.o -g -o test_random

vector.o : vector.c vector.h
	gcc -Wall -Wextra -g -c vector.c

random.o : random.c random.h
	gcc -Wall -Wextra -g -c random.c

test_vector.o : test_vector.c
	gcc -Wall -Wextra -g -c test_vector.c

test_random.o : test_random.c
	gcc -Wall -Wextra -g -c test_random.c

clean :
	rm -f *.o prog