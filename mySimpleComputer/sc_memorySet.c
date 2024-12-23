#include <include/mySimpleComputer.h>

int
sc_memorySet (int address, int value)
{
  if (address >= MEMORY || address < 0)
    return -1;
  if (value < MIN_VALUE || value > MAX_VALUE)
    return -1;
  RAM[address] = value;
  return 0;
}
