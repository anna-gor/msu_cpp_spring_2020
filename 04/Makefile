CC=g++ -std=c++14

all: serializer

serializer: test.cpp serializer.h
	$(CC) -o serializer test.cpp

test: serializer
	./serializer

clean:
	rm -rf *.o serializer