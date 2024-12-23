#include <include/mySimpleComputer.h>

int
sc_accumulatorGet (int *value)
{
  if (!value)
    return -1;
  *value = _Accumulator;
  return 0;
}
