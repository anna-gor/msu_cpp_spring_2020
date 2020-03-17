CC=g++ -std=c++14
  
all: test

parser: test.cpp parser.cpp parser.h
	$(CC) -o parser test.cpp parser.cpp  
 
test: parser  
	./parser
	 
  
clean:  
	rm -rf *.o parser