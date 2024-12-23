#include <include/mySimpleComputer.h>

int
sc_accumulatorSet (int value)
{
  if (value < MIN_VALUE || value > MAX_VALUE)
    return -1;
  _Accumulator = value;
  return 0;
}
