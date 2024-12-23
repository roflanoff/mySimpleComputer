#include <include/mySimpleassembler.h>
//считывает число
int
sa_my_atoi (
    char *str,
    int *ind) // возвращает число и индекс в строке, где число кончилось
{
  int number = 0;
  if (str[*ind] < '0' || str[*ind] > '9')
    return -1; // передано не число
  while (str[*ind] >= '0' && str[*ind] <= '9')
    number = number * 10 + str[(*ind)++] - '0';
  return number;
}
