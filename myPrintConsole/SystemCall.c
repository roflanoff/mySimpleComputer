#include <include/myPrintConsole.h>

void
SystemCall (enum keys readed_key)
{
  if (readed_key == SEQ_ESC)
    {
      mt_gotoXY (27, 1);
      mt_setcursorvisible (1);
      if (rk_mytermrestore ())
        {
          PrintMessage (
              "не удалось восстановить исходные настройки терминала\n");
          exit (-1);
        }
      exit (0);
    }
  if (readed_key == SEQ_r) // запуск программы
    sc_regSet (IGNORE_COUNTER, 0);
  if (readed_key == SEQ_t)
    {
      if (!MemoryController ())
        { // запуск одной команды
          CU ();
        }
      else
        {
          _Downtime_Counter = 0;
        }
    }
  if (readed_key == SEQ_i) // reset
    raise (SIGUSR1);
}
