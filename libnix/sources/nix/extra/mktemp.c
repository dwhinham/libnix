#include <unistd.h>
#include <string.h>
#include <proto/exec.h>
#include "strsup.h"

char *mktemp(char *buf)
{
  long pid = (long)FindTask(0L);
  char *c = buf + strlen(buf);

  while (*--c == 'X') {
    *c = pid % 10 + '0';
    pid /= 10;
  }
  c++;
  if (*c) {
    for(*c='A'; *c <= 'Z'; (*c)++) {
      if (access(buf, 0)) {
        return buf;
      }
    }
    *c = 0;
  }
  return buf;
}
