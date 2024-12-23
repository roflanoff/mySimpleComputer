#include <include/myReadKey.h>

int
rk_readkey (enum keys *key)
{
  char buffer[5] = { 0, 0, 0, 0, 0 };
  buffer[0] = 0;
  int read_result = read (0, buffer, 5);
  if (!read_result)
    return -1;
  for (int i = 0; i < 5; i++)
    if (buffer[i] < 0)
      return 1; // для функции printKeyboardLayoutErr
  // printf("%d %d %d %d
  // %d\n",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);
  if (buffer[0] == 27)
    {

      if (buffer[1] == '[')
        {
          if (buffer[2] == 'A')
            {
              *key = SEQ_UP;
              return 0;
            }
          if (buffer[2] == 'B')
            {
              *key = SEQ_DOWN;
              return 0;
            }
          if (buffer[2] == 'C')
            {
              *key = SEQ_RIGHT;
              return 0;
            }
          if (buffer[2] == 'D')
            {
              *key = SEQ_LEFT;
              return 0;
            }
          if (buffer[2] == '1')
            {
              if (buffer[3] == '5')
                {
                  *key = SEQ_F5;
                  return 0;
                }
              if (buffer[3] == '7')
                {
                  *key = SEQ_F6;
                  return 0;
                }
            }
        }

      *key = SEQ_ESC;
      return 0;
    }
  *key = buffer[0];
  return 0;
}
