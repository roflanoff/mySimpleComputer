#include <include/mySimplebasic.h>

int
sb_my_atoi (char *str, int *ind)
{
  int number = 0;
  if (str[*ind] < '0' || str[*ind] > '9')
    return -1; // передано не число
  while (str[*ind] >= '0' && str[*ind] <= '9')
    number = number * 10 + str[(*ind)++] - '0';
  return number;
}
