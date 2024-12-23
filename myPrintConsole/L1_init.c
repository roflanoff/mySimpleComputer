#include <include/myPrintConsole.h>

void
L1_init (void)
{
  for (int i = 0; i < 5; i++)
    {
      L1_CASH[i].line = -1;
      L1_CASH[i].priority = 10;
      for (int j = 0; j < 10; j++)
        L1_CASH[i].data[j] = 0;
    }
  addr_to_input = -1;
}
