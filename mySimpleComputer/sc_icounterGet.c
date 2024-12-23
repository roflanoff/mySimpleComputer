#include <include/mySimpleComputer.h>

int
sc_icounterGet (int *value)
{
  if (!value)
    return -1;
  *value = _Commands;
  return 0;
}
