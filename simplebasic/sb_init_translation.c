#include <include/mySimplebasic.h>

void
sb_init_translation (struct as_command *translation)
{
  for (int i = 0; i < 128; i++)
    {
      translation[i].stroke_basic = 0;
      translation[i].command[0] = '\0';
      translation[i].operand[0] = '\0';
      translation[i].type_op = 0;
    }
}
