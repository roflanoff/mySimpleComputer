#include <include/myPrintConsole.h>
#include <include/mySimpleComputer.h>
#include <string.h>
#include <unistd.h>

void
printCell (int address, enum colors fg, enum colors bg)
{
  int value = 0;
  if (!sc_memoryGet (address, &value))
    {
      mt_setfgcolor (fg);
      mt_setbgcolor (bg);
      mt_gotoXY ((address / 10) + 2, (address % 10) * 6 + 2);
      char data[100];
      sprintf (data, DECODED_COMMAND, TO_DECODED_COMMAND (value));
      write (STDOUT_FILENO, data, strlen (data));
      mt_setdefaultcolor ();
    }
}
