CC=g++ -std=c++14
  
all: parse

parse: test.cpp parser.cpp parser.h
	$(CC) -o parse test.cpp parser.cpp  
 
test: parse  
	./parse
	 
  
clean:  
	rm -rf *.o parser