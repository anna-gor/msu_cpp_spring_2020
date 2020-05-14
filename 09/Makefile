CC=g++ -std=c++14

all: sort

sort: test.o sort.o pool.o
	$(CC) -pthread test.o sort.o pool.o -o sort 

test: sort
	./sort

test.o: test.cpp sort.h pool.h
	$(CC) -c -pthread test.cpp

sort.o: sort.cpp sort.h pool.h
	$(CC) -c -pthread sort.cpp

pool.o: sort.cpp sort.h pool.h
	$(CC) -c -pthread pool.cpp

clean:
	rm -rf *.o sort