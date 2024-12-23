#include <include/myPrintConsole.h>
#include <include/myReadKey.h>
#include <include/mySimpleComputer.h>
#include <string.h>
#include <unistd.h>

int
L1_get (int address, int *value)
{
  int line = address - address % 10;
  if (address >= MEMORY || address < 0)
    {
      sc_regSet (IGNORE_COUNTER, 1);
      sc_regSet (OUT_OF_MEMORY, 1);
      return -1;
    }
  for (int i = 0; i < 5; i++)
    {
      if (L1_CASH[i].line == line)
        {
          *value = L1_CASH[i].data[address - line];
          L1_CASH[i].priority = 0;
          return 0;
        }
    }
  _Downtime_Counter = 10;
  addr_to_input = line;
  return -1;
}
