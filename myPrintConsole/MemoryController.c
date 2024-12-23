#include <include/myPrintConsole.h>
#include <include/myReadKey.h>
#include <include/mySimpleComputer.h>
#include <string.h>
#include <unistd.h>

int
MemoryController (void)
{
  if (_Downtime_Counter > 0)
    {
      _Downtime_Counter--;
      return -1;
    }
  if (addr_to_input != -1)
    {
      int max_priority = 0;
      int max_i;
      for (int i = 0; i < 5; i++)
        {
          if (L1_CASH[i].priority > max_priority)
            {
              max_priority = L1_CASH[i].priority;
              max_i = i;
            }
        }
      if (L1_CASH[max_i].line != -1)
        for (int i = 0; i < 10; i++)
          {
            sc_memorySet (L1_CASH[max_i].line + i, L1_CASH[max_i].data[i]);
          }
      int value = 0;
      L1_CASH[max_i].line = addr_to_input;
      for (int i = 0; i < 10; i++)
        {
          value = 0;
          sc_memoryGet (L1_CASH[max_i].line + i, &value);
          L1_CASH[max_i].data[i] = value;
        }
      L1_CASH[max_i].priority = 0;
      for (int i = 0; i < 5; i++)
        {
          L1_CASH[i].priority++;
        }
      addr_to_input = -1;
      printCash ();
    }
  return 0;
}
