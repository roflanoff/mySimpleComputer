#include <include/mySimpleComputer.h>

int
sc_memoryInit (void)
{
  for (int i = 0; i < MEMORY; i++)
    RAM[i] = 0;
  return 0;
}
