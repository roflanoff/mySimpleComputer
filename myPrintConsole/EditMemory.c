#include <include/myPrintConsole.h>
#include <include/myReadKey.h>
#include <string.h>
#include <unistd.h>

void
EditMemory (enum keys readed_key)
{
  if (readed_key == SEQ_ENTER)
    {
      mt_setcursorvisible (1);
      int y_pos = (_Active_Cell % 10) * 6 + 2;
      int x_pos = _Active_Cell / 10 + 2;
      mt_gotoXY (x_pos, y_pos);
      mt_setbgcolor (COLOR_GREEN);
      write (1, "     ", 5);
      mt_gotoXY (x_pos, y_pos);
      int value;
      int rk_readvalue_result = rk_readvalue (&value, 40);
      if (!rk_readvalue_result)
        {
          sc_memorySet (_Active_Cell, value);
          printTerm (_Active_Cell, 0);
        }

      mt_setcursorvisible (0);
      mt_setdefaultcolor ();
    }
}
