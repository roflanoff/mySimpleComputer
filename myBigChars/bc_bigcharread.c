#include <include/myBigChars.h>

int
bc_bigcharread (int fd, int *big, int need_count, int *count)
{
  *count = read (fd, big, need_count * 2 * 4);
  if (*count == -1)
    return -1;
  return 0;
}
