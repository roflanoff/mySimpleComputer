#include <include/myPrintConsole.h>
#include <string.h>
void
IRC (int signum)
{
  if (signum == SIGINT)
    {
      sc_regSet (IGNORE_COUNTER, 1);
      /*mt_gotoXY (27, 1);
      mt_setcursorvisible (1);
      rk_mytermrestore ();*/
    }
  if (signum == SIGUSR1) // сигнал reset
    {
      sc_memoryInit ();
      sc_accumulatorInit ();
      sc_icounterInit ();
      sc_regInit ();
      L1_init ();
      _Downtime_Counter = 0;
    }
  int value;
  sc_regGet (IGNORE_COUNTER, &value);

  if (signum == SIGALRM && !value)
    { // запуск устройства управления
      if (!MemoryController ())
        CU ();
    }
}
