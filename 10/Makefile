all: test

run_tests: sol.o
	g++ -g -std=c++14 -pthread sol.o -o run_tests

sol.o: sol.cpp 
	g++ -g -std=c++14 -c sol.cpp -o sol.o

test: run_tests
	./run_tests

clean:
	-(rm run_tests *.o)