CC=g++ -std=c++14

all: pool

pool: test.o pool.o
	$(CC) -pthread test.o pool.o -o pool

test: pool
	./pool

test.o: test.cpp pool.h
	$(CC) -c -pthread test.cpp


pool.o:  pool.h
	$(CC) -c -pthread pool.cpp

clean:
	rm -rf *.o pool