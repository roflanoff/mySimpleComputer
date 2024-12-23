#include <include/myBigChars.h>
#include <include/mySimpleComputer.h>
#include <include/myTerm.h>

int
sc_icounterSet (int value)
{
  if (value < MIN_VALUE || value > MAX_VALUE)
    return -1;
  _Commands = value;
  return 0;
}
