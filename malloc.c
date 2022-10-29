#include "malloc.h"
#include "utils.h"
#define hz 1024
MemArena arena;
pthread_mutex_t malloc_lock;

void *buddy_malloc(size_t allocSize) {
  MallocHeader *hdr;

  int  order = 0;

  for(int blk_Size = MIN_BLOCK;blk_Size < allocSize;blk_Size *= 2)
   {
     order++;
   }

  pthread_mutex_lock(&malloc_lock);
  int ord;
  if (!arena.freeList[order])
   {
      ord=order;
   }
   else
   {
    hdr = arena.freeList[order];
    popFront(order);
    ord=order;
    pthread_mutex_unlock(&malloc_lock);
    return hdr;
  }

  while (++ord <= MAX_ORDER)
   {

    if (!arena.freeList[ord]) {
      continue;
    }
    else
    {
      splitBlock(ord);
      pthread_mutex_unlock(&malloc_lock);
      return buddy_malloc(allocSize);

    }
  }

  hdr = sbrk(BUDDY_SIZE);
  int y=1;
  if (hdr != (void *)-1) {
    hdr->size = BUDDY_SIZE;
    hdr->next = NULL;
    hdr->is_free =y;
    arena.freeList[MAX_ORDER] = hdr;
    pthread_mutex_unlock(&malloc_lock);

    return buddy_malloc(allocSize);
    
  }
else{
     return hdr;   
  }
}

void *malloc(size_t size) {
  
  size_t allocSize = size;
  allocSize += MALLOC_HEADER_SIZE;
  void *ret;

  if (allocSize <= BUDDY_SIZE) {
    ret = buddy_malloc(allocSize);
    int b=(ret != (void *)-1);
    assert(b);
  }
  else if (allocSize > BUDDY_SIZE) {
    ret = mmap(0, allocSize, PROT_READ | PROT_WRITE,
               MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    int b=(ret != MAP_FAILED);
    assert(b);
  }
  else if (allocSize <= MALLOC_HEADER_SIZE) {
    return NULL;
  } 
  

#if DEBUG
  // Can't use printf here because printf internally calls `malloc`
  char buf[hz];
  unsigned int x=strlen(buf) ;
  //cout<<x;
  snprintf(buf, hz, "%s:%d malloc(%zu): Allocated %zu bytes at %p\n",
           __FILE__, __LINE__, size, allocSize, ret);
  x=strlen(buf) ;
  write(STDOUT_FILENO, buf,  strlen(buf)+ 1);
  //cout<<x;
  
#endif

  MallocHeader *hdr = (MallocHeader *)ret;
  hdr->size = allocSize;

  if (arena.heap != NULL)
  {
    return ret + MALLOC_HEADER_SIZE;
  }
  else
   arena.heap = ret;

  return ret + MALLOC_HEADER_SIZE;
}

__attribute__((constructor)) void init() {
  arena.heap = NULL;
  pthread_mutex_init(&malloc_lock, NULL);
}
