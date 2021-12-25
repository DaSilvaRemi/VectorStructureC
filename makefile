all : test_vector

test_vector : test_vector.o vector.o random.o my_struct.o
	gcc vector.o my_struct.o random.o test_vector.o -g -o test_vector

test_vector_double : test_vector_double.o vector_double.o random.o
	gcc vector_double.o random.o test_vector_double.o -g -o test_vector_double

test_random : test_random.o random.o
	gcc random.o test_random.o -g -o test_random

bench_vector : bench_vector.o my_struct.o vector.o random.o
	gcc vector.o my_struct.o random.o bench_vector.o -g -o bench_vector

test_my_struct :  my_struct.o random.o test_my_struct.o
	gcc my_struct.o random.o test_my_struct.o -g -o test_my_struct

vector.o : vector.c vector.h
	gcc -Wall -Wextra -g -c vector.c

vector_double.o : vector_double.c  vector_double.h
	gcc -Wall -Wextra -D V2 -g -c vector_double.c

random.o : random.c random.h
	gcc -Wall -Wextra -g -c random.c

my_struct.o: my_struct.c my_struct.h
	gcc -Wall -Wextra -g -c my_struct.c

test_vector.o : test_vector.c
	gcc -Wall -Wextra -g -c test_vector.c

test_vector_double.o : test_vector_double.c
	gcc -Wall -Wextra -g -c test_vector_double.c

test_random.o : test_random.c
	gcc -Wall -Wextra -g -c test_random.c

test_my_struct.o : test_my_struct.c
	gcc -Wall -Wextra -g -c test_my_struct.c

bench_vector.o : bench_vector.c
	gcc -Wall -Wextra -g -c bench_vector.c

clean :
	rm -f *.o test_vector test_vector_double test_random test_my_struct bench_vector bench_vector_v2 