#include "malloc.h"
#include "utils.h"

void* calloc(size_t nmemb, size_t size) {
  int totalSize;
  totalSize = nmemb;
  totalSize=totalSize * size;
  
  void* ret;
  ret = malloc(totalSize);
  if (!ret)
  {
  return ret;
  }
  else
   memset(ret, 0, totalSize);
  return ret;
}