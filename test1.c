#include<stdlib.h>
#include<stdio.h>
#include <math.h>
#include "utils.h"
#include "utils.c"
#include "malloc.h"
#include "malloc.c"
#include "memalign.c"
#include "free.c"
#include "realloc.c"


int main()
{

  void *ptr;
	size_t boundary,size;
  while(1)
  {
    	printf("Select the function you would like to check\n");
	  printf(" 1.malloc \n 2.calloc \n 3. free \n 4. realloc \n 5.reallocarray \n 6.memalign \n 7.posix_memalign\n");
	  int choice;
	  scanf("%d",&choice);
	  if(choice==1)
	  {
      printf("No. of bytes you will like to allocate \n");
		  scanf("%zu",&size);
		  ptr=malloc(size);
		  void *ptr1=ptr+size;
      int unused_space;
      if(size<2048)
        {
          int total=size+(sizeof(MallocHeader));
          int i,new_total;
          for(i=0; (total >> (i + 1));i++);
          int k=(2<<(i-1));
          if(k==total)
          {
            new_total=total;
          }
          else
          {
            i=i+1;
            new_total=(2<<(i-1));
          }
          unused_space=new_total-(size+(sizeof(MallocHeader)));
        }
        else
        {
          unused_space=0;
        }
      //printf(" Allocated Memory %d \n",new_total);
      printf(" Internal Fragmentation %d \n",unused_space);
		  printf("starting address %p ending address %p block size %zu \n",ptr,ptr1,size);
	  }
	  else if(choice==2)
  	{
      printf("No. of bytes you will like to allocate \n");
		  scanf("%zu",&size);
		  size_t num;
      printf("no. of elements\n");
		  scanf("%zu",&num);
		  ptr=calloc(num,size);
		  void *ptr1=ptr+(num*size);
      int unused_space;
      if(size<2048)
        {
          int total=(num*size)+(sizeof(MallocHeader));
          int i,new_total;
          for(i=0; (total >> (i + 1));i++);
          int k=(2<<(i-1));
          if(k==total)
          {
            new_total=total;
          }
          else
          {
            i=i+1;
            new_total=(2<<(i-1));
          }
          unused_space=new_total-((num*size)+(sizeof(MallocHeader)));
        }
        else
        {
          unused_space=0;
        }
      //printf(" Allocated Memory %d \n",new_total);
      printf(" Internal Fragmentation %d \n",unused_space);
		  printf("starting address %p ending address %p block size %zu \n",ptr,ptr1,(num*size));
	  }
    else if(choice==3)
    {
      void *ptr2;
      printf("Enter address you would like to free\n");
      scanf("%p",&ptr2);
      free(ptr);

    }
    else if(choice==4)
    {
      printf("No. of bytes you will like to allocate \n");
      scanf("%zu",&size);
      void *ptr2;
      printf("Address which you would like to reallocate \n");
      scanf("%p",&ptr2);
      ptr=realloc(ptr2,size);
      void *ptr1=ptr+size;
      int unused_space;
      if(size<2048)
        {
          int total=size+(sizeof(MallocHeader));
          int i,new_total;
          for(i=0; (total >> (i + 1));i++);
          int k=(2<<(i-1));
          if(k==total)
          {
            new_total=total;
          }
          else
          {
            i=i+1;
            new_total=(2<<(i-1));
          }
          unused_space=new_total-(size+(sizeof(MallocHeader)));
        }
        else
        {
          unused_space=0;
        }
      //printf(" Allocated Memory %d \n",new_total);
      printf(" Internal Fragmentation %d \n",unused_space);
      printf("starting address %p ending address %p block size %zu \n",ptr2,ptr1,size);
    }
    else if(choice==5)
    {
      printf("No. of bytes you will like to allocate \n");
      scanf("%zu",&size);
      void *ptr2;
      size_t num;
      printf("no. of elements\n");
      scanf("%zu",&num);
      printf("Address which you would like to reallocate \n");
      scanf("%p",&ptr2);
      ptr=reallocarray(ptr2,num,size);
      void *ptr1=ptr+size;
      int unused_space;
      if(size<2048)
        {
          int total=(num*size)+(sizeof(MallocHeader));
          int i,new_total;
          for(i=0; (total >> (i + 1));i++);
          int k=(2<<(i-1));
          if(k==total)
          {
            new_total=total;
          }
          else
          {
            i=i+1;
            new_total=(2<<(i-1));
          }
          unused_space=new_total-((num*size)+(sizeof(MallocHeader)));
        }
        else
        {
          unused_space=0;
        }
      //printf(" Allocated Memory %d \n",new_total);
      printf(" Internal Fragmentation %d \n",unused_space);
      printf("starting address %p ending address %p block size %zu \n",ptr2,ptr1,(num*size));

    }
    else if(choice==6)
    { 
      printf("size of memory you would like to use \n");
      scanf("%zu",&size);
       printf("Enter boundary size(in power of 2) \n");
      scanf("%zu",&boundary);
      ptr=memalign(boundary,size);
      int unused_space;
      if(size<2048)
        {
          int total=size+boundary+(2*sizeof(MallocHeader));
          int i,new_total;
          for(i=0; (total >> (i + 1));i++);
          int k=(2<<(i-1));
          if(k==total)
          {
            new_total=total;
          }
          else
          {
            i=i+1;
            new_total=(2<<(i-1));
          }
          unused_space=new_total-(size+(2*sizeof(MallocHeader)))-boundary;
        }
        else
        {
          unused_space=0;
        }
      //printf(" Allocated Memory %d \n",new_total);
      printf(" Internal Fragmentation %d \n",unused_space);

  

      void *ptr1=ptr+size;
      printf("starting address %p ending address %p block size %zu \n",ptr,ptr1,size);

    }
    else if(choice==7)
    {
      printf("size of memory you would like to use \n");
      scanf("%zu",&size);
       printf("Enter boundary size(in power of 2) \n");
      scanf("%zu",&boundary);
      //void *ptr2;
      printf("Enter address you would like to free\n");
      scanf("%p",&ptr);
      int x=posix_memalign(ptr,boundary,size);
      if(x==0)
      {
        void *ptr1=ptr+size;
        int unused_space;
        if(size<2048)
        {
          int total=size+boundary+(2*sizeof(MallocHeader));
          int i,new_total;
          for(i=0; (total >> (i + 1));i++);
          int k=(2<<(i-1));
          if(k==total)
          {
            new_total=total;
          }
          else
          {
            i=i+1;
            new_total=(2<<(i-1));
          }
          unused_space=new_total-(size+(2*sizeof(MallocHeader)))-boundary;
        }
        else
        {
          unused_space=0;
        }
      //printf(" Allocated Memory %d \n",new_total);
      printf(" Internal Fragmentation %d \n",unused_space);
        printf("starting address %p ending address %p block size %zu \n",ptr,ptr1,size);
    }
      else
      {
        printf("error \n");
      }

    }
    else{
      break;
    }
  }
}
