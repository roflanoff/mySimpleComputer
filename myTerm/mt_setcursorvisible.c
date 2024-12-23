#include <include/myTerm.h>
#include <string.h>
#include <unistd.h>

int
mt_setcursorvisible (int value)
{
  int bytes_written = 0;
  char *data;
  if (value)
    data = "\E[?25h\E[?8c";
  else
    data = "\E[?25l\E[?1c";
  bytes_written = write (STDOUT_FILENO, data, strlen (data));
  if (strlen (data) != bytes_written)
    return -1;
  return 0;
}
