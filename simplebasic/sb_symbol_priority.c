#include <include/mySimplebasic.h>

int
sb_symbol_priority (char a)
{
  if (a == '(' || a == ')')
    return 1;
  if (a == '-' || a == '+')
    return 2;
  if (a == '*' || a == '/')
    return 3;
  return -1;
}
