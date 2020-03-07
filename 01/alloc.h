#include <stdio.h>
#include <stdint.h>
#include <assert.h>

char* data = nullptr;
size_t SizeOfArray = 0;
char *beg = 0;

void makeAllocator(size_t maxSize)
{
    if(!data){
	    beg = data = new char[maxSize];
	    SizeOfArray = maxSize;
	}
    else
    	delete[] data;
}

char* alloc(size_t size)
{
    if (data + size <= beg + SizeOfArray) {
        char *res_ptr = data;
        data += size;
        return res_ptr;
    } else {
        return nullptr;
    }
}


void reset()
{
    data = beg;
}

