#include <include/mySimpleComputer.h>

int
sc_memorySave (char *filename)
{
  int descriptor = open (filename, O_WRONLY | O_CREAT, S_IRWXU);
  if (descriptor == -1)
    return -1;
  int write_result = write (descriptor, RAM, MEMORY * 4);
  if (write_result != MEMORY * 4)
    return -1;
  close (descriptor);
  return 0;
}
