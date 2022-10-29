#ifndef _UTILS_H_
#define _UTILS_H_

#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#include "malloc.h"

typedef unsigned long ul;

void pushFront(int index, MallocHeader *block);
void popFront(int index);
void mergeBlock(MallocHeader *block);
int log_2(int n);
void *roundUp(void *addr, size_t alignment);
void splitBlock(int index);

#endif
