#include <include/myPrintConsole.h>
#include <include/mySimpleComputer.h>
#include <string.h>
#include <unistd.h>

void
printCash (void)
{
  for (int i = 0; i < 5; i++)
    {
      mt_gotoXY (20 + i, 2);
      char data[100];
      if (L1_CASH[i].line == -1)
        {
          sprintf (data, "-1:");
          write (STDOUT_FILENO, data, strlen (data));
        }
      else
        {
          sprintf (data, "%02d:", L1_CASH[i].line);
          write (STDOUT_FILENO, data, strlen (data));
          for (int j = 0; j < 10; j++)
            {
              mt_gotoXY (20 + i, 8 + j * 6);
              sprintf (data, DECODED_COMMAND,
                       TO_DECODED_COMMAND (L1_CASH[i].data[j]));
              write (STDOUT_FILENO, data, strlen (data));
            }
        }
    }
}
