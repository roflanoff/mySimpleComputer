#include <include/mySimplebasic.h>

int
sb_stroke_in_tokens (char *second_operand, char tokens[50][255], int *index)
{
  int t = 0;  // индекс в токене числа 
  int error_flag = 0; // порядок буква операция буква
  int open_br = 0; // обазанчает открытые закрытые скобки 
  for (int i = 0; second_operand[i] != '\0'; i++)
    {
      if (second_operand[i] >= 'A' && second_operand[i] <= 'Z')
        {
          if (error_flag != 1)
            {
              tokens[*index][0] = second_operand[i]; //считываем букавку
              tokens[*index][1] = '\0';
              (*index)++;
              error_flag = 1;
            }
          else
            return -1;
        }
      else if (second_operand[i] == '+' || second_operand[i] == '-'
               || second_operand[i] == '*' || second_operand[i] == '/')
        {
          if (error_flag != 0)
            {
              tokens[*index][0] = second_operand[i];
              tokens[*index][1] = '\0';
              (*index)++;
              error_flag = 0;
            }
          else
            return -1;
        }
      else if (second_operand[i] == '(')
        {
          if (error_flag != 1)
            {
              tokens[*index][0] = second_operand[i];
              tokens[*index][1] = '\0';
              (*index)++;
              open_br++; 
              // error_flag = 1;
            }
          else
            return -1;
        }
      else if (second_operand[i] == ')')
        {
          if (error_flag != 0)
            {
              tokens[*index][0] = second_operand[i];
              tokens[*index][1] = '\0';
              (*index)++;
              open_br--;
              if (open_br < 0)
                return -1;
              // error_flag = 0;
            }
          else
            return -1;
        }
      else if (second_operand[i] < '0' || second_operand[i] > '9')
        return -1; // передано не число
      else
        {
          if (error_flag != 1)
            {
              while (second_operand[i] >= '0' && second_operand[i] <= '9')
                {
                  tokens[*index][t] = second_operand[i]; //перекопируем в  токен
                  t++;
                  i++;
                }
              i--;
              tokens[*index][t] = '\0';
              (*index)++;
              t = 0;
              error_flag = 1;
            }
          else
            return -1;
        }
      if ((*index) >= 50) // проверка на размер, тк в текнов в строке 50
        return -1;
    }
  if (open_br != 0)
    return -1;
  return 0;
}
