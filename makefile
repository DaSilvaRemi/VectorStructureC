all : test_vector

test_vector : test_vector.o vector.o
	gcc vector.o test_vector.o -g -o test_vector

test_random : test_random.o random.o
	gcc random.o test_random.o -g -o test_random

bench_vector : bench_vector.o vector.o random.o
	gcc vector.o random.o bench_vector.o -g -o bench_vector

bench_vector_v2 : bench_vector.o vectorV2.o random.o
	gcc vectorV2.o random.o bench_vector.o -g -o bench_vector_V2

vector.o : vector.c vector.h
	gcc -Wall -Wextra -g -c vector.c

vectorV2.o : vector.c vector.h
	gcc -Wall -Wextra -g -D V2 -c vector.c -o vectorV2.o

random.o : random.c random.h
	gcc -Wall -Wextra -g -c random.c

test_vector.o : test_vector.c
	gcc -Wall -Wextra -g -c test_vector.c

test_random.o : test_random.c
	gcc -Wall -Wextra -g -c test_random.c

bench_vector.o : bench_vector.c
	gcc -Wall -Wextra -g -c bench_vector.c

clean :
	rm -f *.o prog