# Buddy Algorithm

In this project, We created a library that implements the necessary calls to support heap memory allocation and deallocation for applications. We implemented our own versions of the standard malloc, calloc, realloc, posix_memalign, memalign, reallocarray and free calls, and use the “buddy algorithm” for managing the heap.

Buddy System: The buddy memory allocation technique is a memory allocation algorithm that divides memory into partitions to try to satisfy a memory request as suitably as possible. This system makes use of splitting memory into halves to try to give a best-fit.

## Design Overview: 

The malloc library provides the following api’s to the programs.
```
        void *malloc(size_t size);
        void free(void *ptr);
        void *calloc(size_t nmemb, size_t size);
        void *realloc(void *ptr, size_t size);
        void *reallocarray(void *ptr, size_t nmemb, size_t size);
        int posix_memalign(void **memptr, size_t alignment, size_t size);
        void *memalign(size_t alignment, size_t size);

```
## Program structure:

There are two header files “utils.h” and "malloc.h" which has declarations for memory allocation data
structure and functions that are used across the malloc library. For each functionality, there is a
separate '.c' file i.e. utils.c, malloc.c, realloc.c, free.c, calloc.c, memalign.c and each file includes
utils.h the header file. Also a MAKEFILE has been created to store how the object files will be created in what order.
"t-test1.c" file is present in the folder which was used to test our code(Given in pdf). Also "test1.c" is the file containing the menu driven code which will be used as our main.

## Data Structures Overview:

1. Each memory node has a header attached to it that contains the metadata of the node. Memory Header
```
            typedef struct MallocHeader {
            void* header_addr;
            int is_free;
            struct MallocHeader *next;
            size_t size;
            };
```
2. A memory arena is represented as the following. This stores a list which works as a bit map to check whether that block is free or not. 
```
            typedef struct MemArena {​​​​​​  
            struct MallocHeader *freeList[MAX_ORDER + 1]; 
            void *heap;
            }​​​​​​;

```

## Advantages:

It can be highly efficient for applications where memory is limited as it leads to very less memory
wastage.

## Limitations:

In our version Memory distribution, a small drawback is the way memory is managed once after sbrk() is called for giving more memory for a process and the process which is not
adjacent to the ending limit finishes, that data block becomes free but does not show as free to other processes.

Also Internal Fragmentation is also visible in blocks.