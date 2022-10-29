#include "malloc.h"
#include "utils.h"

#define hz 1024

MemArena arena;
pthread_mutex_t malloc_lock;

void free(void *ptr)
{
  if (ptr != NULL)
  {
  	MallocHeader *hdr = MALLOC_BASE(ptr);
    if (!hdr->header_addr){}
    else return free(hdr->header_addr);

    if (hdr->size > BUDDY_SIZE) 
  {
      munmap(hdr, hdr->size);
  }
   else if (hdr->size <= BUDDY_SIZE) 
   {
      if (hdr->is_free) {}
      else
      {
        hdr->next = NULL;
        hdr->is_free = 1;
        pthread_mutex_lock(&malloc_lock);
        mergeBlock(hdr);
        pthread_mutex_unlock(&malloc_lock);
      }
    }
   

#if DEBUG
  char buf[hz];
  snprintf(buf, hz, "%s:%d free(%p): Freeing %zu bytes from %p\n", __FILE__,
           __LINE__, ptr, hdr->size, hdr);
  write(STDOUT_FILENO, buf, strlen(buf) + 1);
#endif
}
  else
   return;

}
