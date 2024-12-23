#include <include/mySimplebasic.h>
//проверяет допустимые символы в алг примере
int
sb_is_expression (char a)
{
  if (a >= 'A' && a <= 'Z')
    return 1;
  if (a >= '0' && a <= '9')
    return 1;
  if (a == '-' || a == '+' || a == '*' || a == '/' || a == '(' || a == ')')
    return 1;
  return 0;
}
