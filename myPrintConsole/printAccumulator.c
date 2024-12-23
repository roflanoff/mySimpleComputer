#include <include/myPrintConsole.h>
#include <include/mySimpleComputer.h>
#include <string.h>
#include <unistd.h>

void
printAccumulator (void)
{
  int value = 0;
  if (!sc_accumulatorGet (&value))
    {
      char data[100];
      sprintf (data, "sc: " DECODED_COMMAND " hex: %04X",
               TO_DECODED_COMMAND (value), value);
      mt_gotoXY (2, 64);
      write (STDOUT_FILENO, data, strlen (data));
    }
}
