#include <include/mySimpleassembler.h>

void
sa_init_translation (int *translation)
{
  for (int i = 0; i < MEMORY; i++)
    translation[i] = 0;
}
