#include <include/myPrintConsole.h>
#include <include/mySimpleComputer.h>
#include <string.h>
#include <unistd.h>

void
printCounters (void)
{
  int value = 0;
  if (!sc_icounterGet (&value))
    {
      char data[100];
      sprintf (data, "T: %02d", _Downtime_Counter);
      mt_gotoXY (5, 63);
      write (STDOUT_FILENO, data, strlen (data));
      sprintf (data, "IC: %c%04X", value & SIGN_MASK ? '-' : '+', value);
      mt_gotoXY (5, 73);
      write (STDOUT_FILENO, data, strlen (data));
    }
}
