#include <include/mySimplebasic.h>

int
sb_command_validate (char *str, int *ind, int *command_name)
{
  for (int command_ind = 0; command_ind < 7; command_ind++)
    {
      int i = 0;
      int is_continue = 0;
      for (i = 0; command_list[command_ind][i] != '\0'; i++)
        if (str[(*ind) + i] != command_list[command_ind][i])//сравнение строки с командой
          {
            is_continue = 1;
            break;
          }
      if (!is_continue)
        {
          *command_name = command_ind; // если нашли то код команды присваиваем имени
          (*ind) += i;
          return 0;
        }
    }
  return -1;
}
