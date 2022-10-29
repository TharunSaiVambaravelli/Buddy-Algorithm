#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <stdlib.h>

#define MIN_BLOCK 8
#define BUDDY_SIZE 2048
#define MAX_ORDER 8

typedef struct MallocHeader {
  void* header_addr;
  int is_free;
  struct MallocHeader *next;
  size_t size;
} MallocHeader;

typedef struct MemArena {
  
  struct MallocHeader *freeList[MAX_ORDER + 1];
  void *heap;
} MemArena;

extern pthread_mutex_t malloc_lock;
extern MemArena arena;

int posix_memalign(void **memptr, size_t alignment, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);
void *malloc(size_t size);
void *memalign(size_t alignment, size_t size);
void *realloc(void *ptr, size_t size);
void *calloc(size_t nmemb, size_t size);
void free(void *ptr);

#define MALLOC_BASE(addr) ((void *)((char *)addr - MALLOC_HEADER_SIZE))
#define MALLOC_HEADER_SIZE (sizeof(MallocHeader))

#endif