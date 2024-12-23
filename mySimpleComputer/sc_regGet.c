#include <include/mySimpleComputer.h>

int
sc_regGet (int reg, int *value)
{
  if (reg != OVERFLOW && reg != DIVISION_BY_ZERO && reg != OUT_OF_MEMORY
      && reg != WRONG_COMMAND && reg != IGNORE_COUNTER)
    return -1;
  if (!value)
    return -1;
  *value = _Flags & reg;
  return 0;
}
