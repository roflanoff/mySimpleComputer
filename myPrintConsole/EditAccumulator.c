#include <include/myPrintConsole.h>
#include <include/myReadKey.h>
#include <unistd.h>

void
EditAccumulator (enum keys readed_key)
{
  if (readed_key == SEQ_F5)
    {
      mt_setcursorvisible (1);
      mt_gotoXY (2, 68);
      mt_setbgcolor (COLOR_GREEN);
      write (1, "     ", 5);
      mt_gotoXY (2, 68);
      int value;
      int rk_readvalue_result = rk_readvalue (&value, 40);
      if (!rk_readvalue_result)
        sc_accumulatorSet (value);
      mt_setdefaultcolor ();
      mt_setcursorvisible (0);
    }
}
