#include <stdlib.h>
#include <proto/exec.h>

void *realloc(void *ptr,unsigned long size)
{
  void *a;
  unsigned long l;
  if(size)
    a=malloc(size);
  else
    a=NULL;
  if(ptr!=NULL)
  { if(a!=NULL)
    { l=((ULONG *)ptr)[-1]-sizeof(ULONG);
      l=l<size?l:size;
      CopyMem(ptr,a,l);
    }
    if(size==0||a!=NULL)
      free(ptr);
  }
  return a;
}
