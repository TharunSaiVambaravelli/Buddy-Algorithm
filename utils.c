#include "utils.h"
#include "malloc.h"

MemArena arena;

int log_2(int n) {
  int i;
  for(i=0; (n >> (i + 1));i++);
  return i;
}


void *roundUp(void *addr, size_t alignment)
{
  unsigned int s_ul=sizeof(ul);
  return (void *)((((ul)addr + s_ul) & ~(ul)(alignment - 1)) + alignment);
}

void popFront(int index) 
{
  MallocHeader *hdr ;
  hdr= arena.freeList[index];
  arena.freeList[index] = hdr->next;
  const int c=0;
  hdr->next = NULL;
  hdr->is_free = c;
}

void splitBlock(int index) 
{
  MallocHeader *blockA;
  blockA= arena.freeList[index];
  const int c=1;
  blockA->is_free = c;
  blockA->size = (blockA->size)/2;
  popFront(index);

  MallocHeader *blockB;
  blockB = (MallocHeader *)((char *)blockA + blockA->size);
  blockB->is_free = c;
  blockB->size = blockA->size;
  

  blockA->next = blockB;
  arena.freeList[index - 1] = blockA;
  blockB->next = NULL;
}

MallocHeader *getBuddy(MallocHeader *block) 
{
  ul offset;
  offset = (ul)(((char *)block) - (char *)arena.heap);
  ul mask,temp;
  mask = (ul)(0x1 << log_2(block->size));
  temp=offset^mask;
  return (MallocHeader *)((temp) + (char *)arena.heap);
}

void pushFront(int index, MallocHeader *block)
 {
  block->next = arena.freeList[index];
  const int c=1;
  arena.freeList[index] = block;
  block->is_free = c;
  //cout<<block->is_free;
}

void mergeBlock(MallocHeader *block) 
{
  int index;
  index = log_2(block->size / MIN_BLOCK);
 
  if (index < MAX_ORDER) 
  {}
  else
  {
    pushFront(index, block);
    return;
  }


  MallocHeader *buddy = getBuddy(block);
  if (buddy->is_free || buddy->size == block->size) {
  }else
  {
     pushFront(index, block);
    return;
  }

  MallocHeader *cur = arena.freeList[index];
  if (cur != buddy) 
  {
    while (cur->next != buddy) cur = cur->next;
    cur->next = buddy->next;
    buddy->next = NULL;
  } 
  else 
  {
    popFront(index);    
  }

  if (block < buddy) {
    block->size =block->size*2;
    mergeBlock(block);
  } else {
    buddy->size =block->size*2;
    mergeBlock(block);
  }
}
