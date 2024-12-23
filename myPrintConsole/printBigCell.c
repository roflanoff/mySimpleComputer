#include <include/myBigChars.h>
#include <include/myPrintConsole.h>
#include <include/mySimpleComputer.h>
#include <string.h>
#include <unistd.h>

void
printBigCell (void)
{
  int value = 0;
  if (!sc_memoryGet (_Active_Cell, &value))
    {
      bc_printbigchar (ch1 + 2 * (16 + ((value & SIGN_MASK) >> 14)), 9, 64, 7,
                       0);
      int digit = (0x7800 & value) >> 11;
      bc_printbigchar (ch1 + 2 * digit, 9, 72, 7, 0);
      digit = (0x780 & value) >> 7;
      bc_printbigchar (ch1 + 2 * digit, 9, 80, 7, 0);
      digit = (0x70 & value) >> 4;
      bc_printbigchar (ch1 + 2 * digit, 9, 88, 7, 0);
      digit = (0xF & value);
      bc_printbigchar (ch1 + 2 * digit, 9, 96, 7, 0);
      mt_gotoXY (17, 66);
      mt_setfgcolor (COLOR_BLUE);
      char buffer[100];
      int buffer_size
          = sprintf (buffer, "номер редактируемой ячейки: %03d", _Active_Cell);
      write (1, buffer, buffer_size);
      mt_setdefaultcolor ();
    }
}
