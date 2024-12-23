#include <include/mySimpleassembler.h>

int
sa_command_validate (char *str, int *ind, int *command)
{
  for (int command_ind = 0; command_ind < COMMANDS_SIZE; command_ind++)
    {
      int i = 0;
      int is_continue = 0;
      for (i = 0; commands[command_ind].name[i] != '\0'; i++)
        if (str[(*ind) + i] != commands[command_ind].name[i])
          {
            is_continue = 1;
            break;
          }
      if (!is_continue)
        {
          *command = commands[command_ind].code;
          (*ind) += i;
          return 0;
        }
    }
  return -1;
}
