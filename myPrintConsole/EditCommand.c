#include <include/myPrintConsole.h>
#include <include/myReadKey.h>
#include <string.h>
#include <unistd.h>

// редактирование счетчика команд
void
EditCommand (enum keys readed_key)
{
  if (readed_key == SEQ_F6)
    {
      mt_setcursorvisible (1);
      rk_mytermregime (0, 20, 5, 1, 1);

      mt_gotoXY (5, 77);
      mt_setbgcolor (COLOR_GREEN);
      write (1, "     ", 5);
      mt_gotoXY (5, 77);

      int rk_mytermregime_result = rk_mytermregime (0, 40, 0, 0, 1);
      if (rk_mytermregime_result)
        {
          mt_setdefaultcolor ();
          mt_setcursorvisible (0);
          return;
        }

      char buffer[5];
      int size_b = 0;
      enum keys readed_key = 1;
      int rk_readkey_result = 0;
      while (!rk_readkey_result)
        {
          rk_readkey_result = rk_readkey (&readed_key);
          if (!rk_readkey_result)
            {
              if (readed_key == SEQ_ESC)
                {
                  mt_setdefaultcolor ();
                  mt_setcursorvisible (0);
                  return;
                }
              if (readed_key == SEQ_ENTER)
                break;
              /*if(readed_key == SEQ_BACKSPACE && size_b > 0)
              {

                size_b--;

              }*/
              if (readed_key == SEQ_PLUS && size_b == 0)
                {
                  buffer[size_b] = readed_key;
                  write (STDOUT_FILENO, buffer + size_b, 1);
                  size_b++;
                }
              if (((readed_key >= SEQ_0 && readed_key <= SEQ_9)
                   || (readed_key >= SEQ_A && readed_key <= SEQ_F)
                   || (readed_key >= SEQ_a && readed_key <= SEQ_f))
                  && (size_b > 0 && size_b < 5))
                {
                  buffer[size_b] = readed_key;
                  write (STDOUT_FILENO, buffer + size_b, 1);
                  size_b++;
                }
            }
        }
      int buf_value = 0;
      if (buffer[0] != SEQ_PLUS)
        {
          mt_setdefaultcolor ();
          mt_setcursorvisible (0);
          return;
        }

      for (int i = 1; i < size_b; i++)
        {
          if (buffer[i] >= '0' && buffer[i] <= '9')
            buf_value = (buffer[i] - '0') + buf_value * 16;
          if (buffer[i] >= 'a' && buffer[i] <= 'f')
            buf_value = (buffer[i] - 'a' + 10) + buf_value * 16;
          if (buffer[i] >= 'A' && buffer[i] <= 'F')
            buf_value = (buffer[i] - 'A' + 10) + buf_value * 16;
        }
      sc_icounterSet (buf_value);
      mt_setdefaultcolor ();
      mt_setcursorvisible (0);
    }
}
