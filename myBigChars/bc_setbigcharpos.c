#include <include/myBigChars.h>

int
bc_setbigcharpos (int *big, int x, int y, int value)
{
  if (!big)
    return -1;
  if (x >= 8 || y >= 8)
    return -1;
  if (value)
    {
      if (x < 4)
        big[0] = big[0] | (1 << (x * 8 + y));
      else if (x >= 4)
        big[1] = big[1] | (1 << ((x - 4) * 8 + y));
    }
  else
    {
      if (x < 4)
        big[0] -= big[0] & (1 << (x * 8 + y));
      else if (x >= 4)
        big[1] -= big[1] & (1 << ((x - 4) * 8 + y));
    }
  return 0;
}
