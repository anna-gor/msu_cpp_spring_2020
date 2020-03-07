#include "alloc.h"
#include <stdio.h>

int main()
{

    //make allocator
    makeAllocator(500);

    //nullptr
    char *ptr = nullptr;
    assert (!ptr); //null

    //overflow
    ptr = alloc(600);
    assert(!ptr); //null


    //alloc
    ptr = alloc(100);
    assert(ptr); //not null
    //reset
    reset();
    ptr = alloc(100);
    assert(ptr);

    printf("All tests are passed!\n");



    return 0;
}