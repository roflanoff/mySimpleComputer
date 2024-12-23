#include <include/myBigChars.h>
#include <include/myPrintConsole.h>
#include <include/myReadKey.h>
#include <include/mySimpleComputer.h>

int
rk_readvalue (int *value, int timeout)
{
  if (!value)
    return -1;

  int rk_mytermregime_result = rk_mytermregime (0, timeout, 0, 0, 1);
  if (rk_mytermregime_result)
    return -1;

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
            return -1;
          if (readed_key == SEQ_ENTER)
            break;
          /*if(readed_key == SEQ_BACKSPACE && size_b > 0)
          {

            size_b--;

          }*/
          if ((readed_key == SEQ_MINUS || readed_key == SEQ_PLUS)
              && size_b == 0)
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
  int sign = 0;
  int command = 0;
  int operand = 0;
  if (buffer[0] == SEQ_MINUS)
    {
      sign = 1;
    }
  else if (buffer[0] == SEQ_PLUS)
    {
      sign = 0;
    }
  else
    return -1;

  for (int i = 1; i < 5; i++)
    {
      if (!((buffer[i] >= '0' && buffer[i] <= '9')
            || (buffer[i] >= 'a' && buffer[i] <= 'f')
            || (buffer[i] >= 'A' && buffer[i] <= 'F')))
        return -1;
    }

  if (buffer[1] >= '0' && buffer[1] <= '9')
    command += (buffer[1] - '0') * 16;
  if (buffer[2] >= '0' && buffer[2] <= '9')
    command += (buffer[2] - '0');

  if (buffer[1] >= 'a' && buffer[1] <= 'f')
    command += (buffer[1] - 'a' + 10) * 16;
  if (buffer[2] >= 'a' && buffer[2] <= 'f')
    command += (buffer[2] - 'a' + 10);

  if (buffer[1] >= 'A' && buffer[1] <= 'F')
    command += (buffer[1] - 'A' + 10) * 16;
  if (buffer[2] >= 'A' && buffer[2] <= 'F')
    command += (buffer[2] - 'A' + 10);

  if (buffer[3] >= '0' && buffer[3] <= '9')
    operand += (buffer[3] - '0') * 16;
  if (buffer[4] >= '0' && buffer[4] <= '9')
    operand += (buffer[4] - '0');
  if (buffer[3] >= 'a' && buffer[3] <= 'f')
    operand += (buffer[3] - 'a' + 10) * 16;
  if (buffer[4] >= 'a' && buffer[4] <= 'f')
    operand += (buffer[4] - 'a' + 10);
  if (buffer[3] >= 'A' && buffer[3] <= 'F')
    operand += (buffer[3] - 'A' + 10) * 16;
  if (buffer[4] >= 'A' && buffer[4] <= 'F')
    operand += (buffer[4] - 'A' + 10);

  int sc_commandEncode_result
      = sc_commandEncode (sign, command, operand, &buf_value);
  if (!sc_commandEncode_result)
    *value = buf_value;

  return sc_commandEncode_result;
}
