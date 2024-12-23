#include <include/mySimplebasic.h>
#include <string.h>
// берет токены  и их разбивает операнды влево, операция вправо и переворачивает их РАСТАВЛЯЕТ
int
sb_tokens_in_OPN (char tokens[50][255], char OPN[50][255], int *index)
{
  char stack[50][255]; // 50 токенов по 255 символов
  int stack_index = -1; // индекс в стеке
  int tmp = 0; //  индекс в опн
  for (int i = 0; i < (*index); i++)
    {
      if ((tokens[i][0] >= 'A' && tokens[i][0] <= 'Z')
          || (tokens[i][0] >= '0' && tokens[i][0] <= '9'))
        {
          sprintf (OPN[tmp++], "%s", tokens[i]); //запписываем сразу в опн 
        }
      else
        {
          if (stack_index == -1) //если ничего нет 
            {
              stack_index++;
              sprintf (stack[stack_index], "%s", tokens[i]); // записываем в стек 1 токен 
            }
          else
            {
              if ((tokens[i][0] == '(')) //записываем скобочку в стек( пишем туда только знки)
                sprintf (stack[++stack_index], "%s", tokens[i]);
              else if ((tokens[i][0] == ')')) 
                {
                  // printf ("[%s]", stack[stack_index]);
                  while (stack[stack_index][0] != '(')
                    {
                      sprintf (OPN[tmp], "%s", stack[stack_index]);
                      tmp++;
                      stack_index--;
                    }
                  stack_index--;
                }
              else if (sb_symbol_priority (tokens[i][0])
                       > sb_symbol_priority (stack[stack_index][0]))
                {
                  sprintf (stack[++stack_index], "%s", tokens[i]);
                }
              else
                {
                  while (stack_index >= 0
                         && (sb_symbol_priority (tokens[i][0])
                             <= sb_symbol_priority (stack[stack_index][0]))) //приоритеты 
                    {
                      sprintf (OPN[tmp++], "%s", stack[stack_index--]);
                    }
                  printf (stack[++stack_index], "%s", tokens[i]);
                }
            }
        }
    }

  while (stack_index >= 0) //если после обработки в стеке что--то осталось , мы со стека в опн пихаем
    {
      sprintf (OPN[tmp], "%s", stack[stack_index]);
      tmp++;
      stack_index--;
    }
  *index = tmp;
  return 0;
}
