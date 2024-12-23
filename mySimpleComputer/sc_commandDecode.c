#include <include/mySimpleComputer.h>

int
sc_commandDecode (int value, int *sign, int *command, int *operand)
{
  if (value < MIN_VALUE || value > MAX_VALUE)
    return -1;
  *operand = value & 127;
  *command = (value & 127 << 7) >> 7;
  *sign = (value & 1 << 14) >> 14;
  return 0;
}
