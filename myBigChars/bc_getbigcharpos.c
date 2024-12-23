#include <include/myBigChars.h>

int
bc_getbigcharpos (int *big, int x, int y, int *value)
{
  if (!big)
    return -1;
  if (x >= 8 || y >= 8)
    return -1;
  if (x < 4)
    *value = big[0] >> (y + x * 8) & 1;

  if (x >= 4)
    *value = big[1] >> (y + (x - 4) * 8) & 1;
  return 0;
}
