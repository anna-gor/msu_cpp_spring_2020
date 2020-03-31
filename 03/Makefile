CC=g++ -std=c++14
  
all: parse

parse: test.cpp matrix.cpp matrix.h
	$(CC) -o matrix test.cpp matrix.cpp  
 
test: matrix  
	./matrix
	 
  
clean:  
	rm -rf *.o matrix