CC=g++ -std=c++14
  
all: bigint

bigint: tests.cpp bigint.cpp bigint.h
	$(CC) -o bigint tests.cpp bigint.cpp  
 
test: bigint  
	./bigint
	 
  
clean:  
	rm -rf *.o bigint