#include <fcntl.h>
#include <include/myBigChars.h>
#include <include/myPrintConsole.h>
#include <include/myReadKey.h>
#include <include/mySimpleComputer.h>
#include <include/myTerm.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

int RAM[128];
struct pair_IN_OUT IN_OUT[5];
struct l1_cash_line L1_CASH[5];
int addr_to_input;

int _Accumulator;
int _Commands;
int _Flags;
int _Downtime_Counter;
int _Active_Cell;

int ch1[100];
struct termios TERM;

int
main (int argc, char *argv[])
{
  if (!isatty (1))
    {
      return -1;
    }
  int rows = 0, cols = 0;
  if (mt_getscreensize (&rows, &cols))
    {
      return -1;
    }
  else if (rows < 25 || cols < 105)
    {
      char *error = "terminal is too small\n";
      write (1, error, strlen (error));
      return -1;
    }
  int file;
  if (argc == 1)
    file = open ("font.bin", O_RDONLY);
  else
    file = open (argv[1], O_RDONLY);

  int count = 0;
  if (bc_bigcharread (file, ch1, 18, &count) == -1)
    {
      char *error = "can not read the font file\n";
      write (1, error, strlen (error));
      return -1;
    }
  close (file);
  if (rk_mytermsave ())
    {
      printf ("не удалось получить настройки терминала\n");
      return -1;
    }
  mt_clrscr ();

  _Active_Cell = 0;

  signal (SIGUSR1, IRC); // кнопка reset
  signal (SIGALRM, IRC); // тактовый сигнал
  signal (SIGINT, IRC);
  struct itimerval nval, oval;

  nval.it_interval.tv_sec = 0;
  nval.it_interval.tv_usec = 500000;
  nval.it_value.tv_sec = 0;
  nval.it_value.tv_usec = 500000;

  /* Запускаем таймер */
  setitimer (ITIMER_REAL, &nval, &oval);

  // clearTerm ();
  raise (SIGUSR1); // отправляем  сигнал reset
  // int is_write = 0;
  // sc_memoryLoad ("RAM_file.bin");
  int value = 1;
  while (1)
    {
      mt_setcursorvisible (0);
      printAll ();
      rk_mytermregime (0, 1, 1, 0, 1);

      enum keys readed_key = 1;
      sc_regGet (IGNORE_COUNTER, &value);

      if (!value)
        pause ();
      if (value)
        {
          setitimer (ITIMER_REAL, NULL, NULL);

          int rk_readkey_result = rk_readkey (&readed_key);
          if (!rk_readkey_result)
            {
              MoveMem (readed_key);
              EditMemory (readed_key);
              LoadMem (readed_key);
              EditAccumulator (readed_key);
              EditCommand (readed_key);
              SystemCall (readed_key);
            }
          setitimer (ITIMER_REAL, &nval, &oval);
        }
    }
  // sc_memorySave ("RAM_file.bin");
  mt_gotoXY (27, 1);
  mt_setcursorvisible (1);
  rk_mytermrestore ();
  return 0;
}
