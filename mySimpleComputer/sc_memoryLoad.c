#include <include/mySimpleComputer.h>

int
sc_memoryLoad (char *filename)
{
  int descriptor = open (filename, O_RDONLY, S_IRWXU);
  if (descriptor == -1)
    return -1;
  int buffer[MEMORY];
  int read_result = read (descriptor, buffer, MEMORY * 4);
  if (read_result != MEMORY * 4)
    return -1;
  for (int i = 0; i < MEMORY; i++)
    if (buffer[i] < MIN_VALUE || buffer[i] > MAX_VALUE)
      return -1;
  for (int i = 0; i < MEMORY; i++)
    RAM[i] = buffer[i];
  close (descriptor);
  return 0;
}
