#include <stdio.h>
#include <errno.h>

int ungetc(int c,FILE *stream)
{
  if(c==EOF)
    return EOF;
  if(stream->flags&64) /* Error on stream */
  { errno=EPERM;
    return EOF; }
  if(stream->flags&8) /* File is in write mode */
    if(__fflush(stream)) /* write buffer */
      return EOF;
  if(stream->tmpp==NULL)
  { if(stream->flags&4) /* File is in read mode */
    { stream->tmpp=stream->p; /* store actual position */
      stream->tmpinc=stream->incount;
      stream->p=&stream->unget[4]; /* and use other buffer */
      stream->incount=0;
    }else /* File is in indeterminated state */
    { stream->tmpp=(unsigned char *)2; /* Dummy */
      stream->tmpinc=0;
      stream->p=&stream->unget[4]; /* use other buffer */
      stream->incount=0;
      stream->flags|=4;
    }
  }
  if(stream->incount==4) /* ungetc buffer overflow */
    return EOF;
  stream->incount++;
  return *--stream->p=c;
}
