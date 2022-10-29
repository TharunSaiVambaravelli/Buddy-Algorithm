#include "malloc.h"
#include "utils.h"

void *realloc(void *ptr, size_t size) {
  if (ptr != NULL)
  {
  	MallocHeader *hdr;
  	hdr = MALLOC_BASE(ptr);
 	 if (hdr->size < size){}
 	 else
 	  return ptr;

  void *ret;
  ret = malloc(size);
  memcpy((char *)ret, ptr, hdr->size);
  free(ptr);
  return ret;
  }
  else
  {
   	void * temp;
   	temp=malloc(size);
   	return temp;
  }

}

void *reallocarray(void *ptr, size_t nmemb, size_t size) 
{
  size_t total=nmemb;
  total=total*size;
  void *ptr1=realloc(ptr,total);
  return ptr1;
}
