
#include "malloc.h"
#include "utils.h"

void *memalign(size_t alignment, size_t size) 
{
  size_t val=size+alignment;
  val+=MALLOC_HEADER_SIZE;
  void *ptr;
  ptr = malloc(val);
  if (!ptr) {
  return NULL;
  } else {
  	 void *ret;
  	 ret = roundUp(ptr, alignment);
    ((MallocHeader *)MALLOC_BASE(ret))->header_addr = ptr;
    return ret;
  }
}

int posix_memalign(void **memptr, size_t alignment, size_t size) {
  void *ret;
  ret = memalign(alignment, size);
  if (!ret) {
  return errno;
  } else {
    *memptr = ret;
    return 0;
  }
}
