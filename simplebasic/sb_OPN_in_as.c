#include <include/mySimplebasic.h>
#include <string.h>
//уже преобразует обраную польскую анатацию в ассемблерный код с созданием промежуточных перемнных
int
sb_OPN_in_as (char OPN[50][255], int *index, struct as_command *translation,
              int *as_stroke, int number, int *operations)
{
  char stack[50][255]; // номеый стак
  int stack_index = -1;
  for (int i = 0; i < (*index); i++)
    {
      if ((OPN[i][0] >= 'A' && OPN[i][0] <= 'Z')
          || (OPN[i][0] >= '0' && OPN[i][0] <= '9'))
        {
          stack_index++;
          sprintf (stack[stack_index], "%s", OPN[i]);
        }
      else
        {
          translation[*as_stroke].stroke_basic = number;
          sprintf (translation[*as_stroke].command, "LOAD");
          sprintf (translation[*as_stroke].operand, "%s",
                   stack[stack_index - 1]);
          if (stack[stack_index - 1][0] >= 'A'
              && stack[stack_index - 1][0] <= 'Z')
            translation[*as_stroke].type_op = 1;
          if (stack[stack_index - 1][0] >= '0'
              && stack[stack_index - 1][0] <= '9')
            translation[*as_stroke].type_op = 2;
          if (stack[stack_index - 1][0] == 'r')
            translation[*as_stroke].type_op = 3;

          (*as_stroke)++;
          translation[*as_stroke].stroke_basic = number;
          sprintf (translation[*as_stroke].operand, "%s", stack[stack_index]);
          if (stack[stack_index][0] >= 'A' && stack[stack_index][0] <= 'Z')
            translation[*as_stroke].type_op = 1;
          if (stack[stack_index][0] >= '0' && stack[stack_index][0] <= '9')
            translation[*as_stroke].type_op = 2;
          if (stack[stack_index][0] == 'r')
            translation[*as_stroke].type_op = 3;
          if (OPN[i][0] == '+')
            {
              sprintf (translation[*as_stroke].command, "ADD");
            }
          if (OPN[i][0] == '-')
            {
              sprintf (translation[*as_stroke].command, "SUB");
            }
          if (OPN[i][0] == '*')
            {
              sprintf (translation[*as_stroke].command, "MUL");
            }
          if (OPN[i][0] == '/')
            {
              sprintf (translation[*as_stroke].command, "DIVIDE");
            }
          (*as_stroke)++;
          stack_index -= 2;
          translation[*as_stroke].stroke_basic = number;
          sprintf (translation[*as_stroke].command, "STORE");
          sprintf (translation[*as_stroke].operand, "%c%d", 'r', *operations);
          (*operations)++;
          translation[*as_stroke].type_op = 3;

          stack_index++;
          sprintf (stack[stack_index], "%s", translation[*as_stroke].operand);
          (*as_stroke)++;
        }
    }
  if (stack_index > -1)
    {
      translation[*as_stroke].stroke_basic = number;
      sprintf (translation[*as_stroke].command, "LOAD");
      sprintf (translation[*as_stroke].operand, "%s", stack[stack_index]);
      if (stack[stack_index][0] >= 'A' && stack[stack_index - 1][0] <= 'Z')
        translation[*as_stroke].type_op = 1;
      if (stack[stack_index][0] >= '0' && stack[stack_index - 1][0] <= '9')
        translation[*as_stroke].type_op = 2;
      if (stack[stack_index][0] == 'r')
        translation[*as_stroke].type_op = 3;
      (*as_stroke)++;
      translation[*as_stroke].stroke_basic = number;
      sprintf (translation[*as_stroke].command, "STORE");
      sprintf (translation[*as_stroke].operand, "%c%d", 'r', *operations);
      (*operations)++;
      translation[*as_stroke].type_op = 3;
      (*as_stroke)++;
    }
  return 0;
}
