#include <include/myReadKey.h>

int
rk_mytermrestore ()
{
  int result = tcsetattr (STDIN_FILENO, TCSAFLUSH, &TERM);
  return result;
}
