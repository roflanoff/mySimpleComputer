#include <include/mySimpleComputer.h>

int
sc_memoryGet (int address, int *value)
{
  if (address >= MEMORY || address < 0)
    return -1;
  if (!value)
    return -1;
  *value = RAM[address];
  return 0;
}
