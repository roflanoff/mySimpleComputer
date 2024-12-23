#include <include/myBigChars.h>

int
bc_strlen (unsigned char *str)
{
  if (!str)
    return 0;
  int bytes; // число байтов в кодировке символа
  int length = 0;
  for (int i = 0; str[i] != '\0';)
    {
      if (str[i] >> 7 == 0)
        {
          length++;
          i++;
        }
      else
        {
          int mask = 6;
          for (int j = 5; j >= 3; j--)
            {
              if (str[i] >> j == mask) // совпадение
                {
                  i++;
                  bytes = 8 - j - 2;
                  break;
                }
              mask = (mask << 1) + 2;
            }
          if (mask > 30)
            return 0;
          for (; bytes > 0; bytes--)
            if (str[i++] >> 6 != 2)
              return 0;
          length++;
        }
    }
  return length;
}
