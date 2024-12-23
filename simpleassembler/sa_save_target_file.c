#include <include/mySimpleassembler.h>

int
sa_save_target_file (int descriptor, int *translation)
{
  int write_result = write (descriptor, translation, MEMORY * 4);
  if (write_result != MEMORY * 4)
    return -1;
  return 0;
}
