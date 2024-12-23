#include <include/myReadKey.h>

int
rk_mytermsave ()
{
  int result = tcgetattr (STDIN_FILENO, &TERM);
  return result;
}
