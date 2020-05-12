CC=g++ -std=c++14
  
all: run_tests

run_tests: tests.o
	$(CC) -pthread tests.o -o run_tests

tests.o: tests.cpp pool.h
	$(CC) -c tests.cpp -o tests.o

test: run_tests
	./run_tests

clean:
	-(rm run_tests *.o)