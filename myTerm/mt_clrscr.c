#include <include/myTerm.h>
#include <string.h>
#include <unistd.h>

int
mt_clrscr (void)
{
  int bytes_written = 0;
  char *data = "\E[H\E[J\E[1;1H";
  bytes_written = write (STDOUT_FILENO, data, strlen (data));
  if (strlen (data) != bytes_written)
    return -1;
  return 0;
}
