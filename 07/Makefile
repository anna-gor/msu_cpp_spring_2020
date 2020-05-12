CC=g++ -std=c++14

all: vector

vector: test.o
	$(CC) -o vector test.o

test: vector
	./vector

test.o: test.cpp vector.h
	$(CC) -c test.cpp

clean:
	rm -rf *.o vector