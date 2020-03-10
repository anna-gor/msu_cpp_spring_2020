CC=g++ -std=c++14

all: test

test: tests.cpp alloc.h
	$(CC) tests.cpp alloc.cpp -o test
	./test

clean:
	rm test