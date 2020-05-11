CC=g++ -std=c++14
  
all: format

format: test.o
	$(CC) -o format test.o  
 
test: format  
	./format
	
test.o: test.cpp format.h  
	$(CC) -c test.cpp  
    
clean:  
	rm -rf *.o format