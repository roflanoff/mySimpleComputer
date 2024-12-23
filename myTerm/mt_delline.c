#include <include/myTerm.h>
#include <string.h>
#include <unistd.h>

int
mt_delline (void)
{
  int bytes_written = 0;
  char *data = "\E[M";
  bytes_written = write (STDOUT_FILENO, data, strlen (data));
  if (strlen (data) != bytes_written)
    return -1;
  return 0;
}
