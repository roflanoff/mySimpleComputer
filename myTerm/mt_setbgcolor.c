#include <include/myTerm.h>
#include <string.h>
#include <unistd.h>

int
mt_setbgcolor (enum colors c)
{
  int bytes_written = 0;
  char data[10];
  sprintf (data, "\E[4%dm", c);
  bytes_written = write (STDOUT_FILENO, data, strlen (data));
  if (strlen (data) != bytes_written)
    return -1;
  return 0;
}
