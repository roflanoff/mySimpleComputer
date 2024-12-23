#include <include/myBigChars.h>

int
bc_bigcharwrite (int fd, int *big, int count)
{
  if (!big)
    return -1;
  int size = count * 2 * 4;
  int writeResult = write (fd, big, size);
  if (writeResult != size)
    return -1;
  return 0;
}
