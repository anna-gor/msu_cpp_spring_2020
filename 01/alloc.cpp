#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <new>

char* data = nullptr;
size_t maxSize = 0;
char *beg = 0;

void makeAllocator(size_t maxSize)
{
    try{
	    beg = data = new char[maxSize];
	    ::maxSize = maxSize;}
	
    catch (std::bad_alloc const&) {
        beg = data = nullptr;
        ::maxSize = 0;}

}

char* alloc(size_t size)
{
    if (data + size <= beg + maxSize) {
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

