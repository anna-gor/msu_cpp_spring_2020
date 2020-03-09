#pragma once
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

void makeAllocator(size_t maxSize);
char* alloc(size_t size);
void reset();