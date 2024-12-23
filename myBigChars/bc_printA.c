#include <include/myBigChars.h>

int
bc_printA (char *str)
{
  char *data1 = "\E(0";
  write (STDOUT_FILENO, data1, strlen (data1));
  write (STDOUT_FILENO, str, strlen (str));
  data1 = "\E(B";
  write (STDOUT_FILENO, data1, strlen (data1));
  return 0;
}
