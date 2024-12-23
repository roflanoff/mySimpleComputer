#include <include/mySimpleComputer.h>

int
sc_commandEncode (int sign, int command, int operand, int *value)
{
  if (!(sign == 0 || sign == 1))
    return -1;
  if (operand < MIN_VALUE || operand > MAX_OPERAND_VALUE)
    return -1;
  if (!value)
    return -1;
  *value = operand + (command << 7) + (sign << 14);
  return 0;
}
