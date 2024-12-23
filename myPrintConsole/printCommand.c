#include <include/myPrintConsole.h>
#include <include/mySimpleComputer.h>
#include <string.h>
#include <unistd.h>

void
printCommand (void)
{
  int value = 0;

  if (!sc_icounterGet (&value))
    {
      mt_gotoXY (5, 92);
      int RAM_value = 0;
      if (!sc_memoryGet (value, &RAM_value))
        {
          char data[100];
          sprintf (data, " %c %02X : %02X", TO_DECODED_COMMAND (RAM_value));
          write (STDOUT_FILENO, data, strlen (data));
        }
      else
        {
          char *data = "!+ FF : FF";
          write (STDOUT_FILENO, data, strlen (data));
        }
    }
}
