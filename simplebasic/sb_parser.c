#include <include/mySimplebasic.h>
#include <string.h>
//принимаетт токены и начинает их обрабатывать и преобразывает их в ассемблерные команды
int
sb_parser (int number, int command_name, char *first_operand,
           char *second_operand, int type_of_inequaliry, int *as_stroke,
           struct as_command *translation, int *operations, int *end_flag)
{
  if (command_name == 0) //коментарий не обрабатываем
    return 0;
  if (*end_flag == 1) // если у нас есть операция конца, то после него ничего не должно идти
    return -1;
  if (command_name == 1) //инпут 
    {
      translation[*as_stroke].stroke_basic = number; //добавляем номер строки в файле басик
      sprintf (translation[*as_stroke].command, "READ"); // команду на ассемблере
      sprintf (translation[*as_stroke].operand, "%s", first_operand); //  этот самый операнд в виде строчки 
      translation[*as_stroke].type_op = 1; //тип операнда
      (*as_stroke)++; //индекс в масиве транслейшен и его прибавляем
      return 0;
    }
  if (command_name == 2)
    {
      translation[*as_stroke].stroke_basic = number;
      sprintf (translation[*as_stroke].command, "WRITE");
      sprintf (translation[*as_stroke].operand, "%s", first_operand);
      translation[*as_stroke].type_op = 1;
      (*as_stroke)++;
      return 0;
    }
  if (command_name == 3)
    {
      translation[*as_stroke].stroke_basic = number;
      sprintf (translation[*as_stroke].command, "JUMP");
      sprintf (translation[*as_stroke].operand, "%s", first_operand);
      translation[*as_stroke].type_op = 4; //адрес
      (*as_stroke)++;
      return 0;
    }
  if (command_name == 4)
    {
      translation[*as_stroke].stroke_basic = number;
      sprintf (translation[*as_stroke].command, "HALT");
      sprintf (translation[*as_stroke].operand, "00"); // у него нет операнда поэтмоу записываем 0 
      (*as_stroke)++;
      *end_flag = 1;
      return 0;
    }
  if (command_name == 5)//иф
    {
      char tokens[50][255]; // обратная польская натация
      //каждая значимая часть в алгебраической операции числа отдельно, скобки и тд
      char OPN[50][255]; // обратная польская нотация то что преоразуем из массива токенов
      int index = 0;// индекс в токенах
      if (sb_stroke_in_tokens (second_operand, tokens, &index))
        return -1;
      sb_tokens_in_OPN (tokens, OPN, &index);
      sb_OPN_in_as (OPN, &index, translation, as_stroke, number, operations);

      if (type_of_inequaliry == 1)
        {
          (*operations)--;
          translation[*as_stroke - 1].stroke_basic = number;
          sprintf (translation[*as_stroke - 1].command, "JNEG");
          sprintf (translation[*as_stroke - 1].operand, "%s", first_operand);
          translation[*as_stroke - 1].type_op = 4;
        }
      if (type_of_inequaliry == 2)
        {
          (*operations)--;
          translation[*as_stroke - 1].stroke_basic = number;
          sprintf (translation[*as_stroke - 1].command, "MUL"); //умножить
          sprintf (translation[*as_stroke - 1].operand, "%d", -1);
          translation[*as_stroke - 1].type_op = 2;

          translation[*as_stroke].stroke_basic = number;
          sprintf (translation[*as_stroke].command, "JNEG");
          sprintf (translation[*as_stroke].operand, "%s", first_operand);
          translation[*as_stroke].type_op = 4;
          (*as_stroke)++;
        }
      if (type_of_inequaliry == 3)
        {
          (*operations)--;
          translation[*as_stroke - 1].stroke_basic = number;
          sprintf (translation[*as_stroke - 1].command, "JNEG"); //если в акуме отрицу число
          sprintf (translation[*as_stroke - 1].operand, "%s", first_operand);
          translation[*as_stroke - 1].type_op = 4;

          translation[*as_stroke].stroke_basic = number;
          sprintf (translation[*as_stroke].command, "JZ"); // если в акуме 0 
          sprintf (translation[*as_stroke].operand, "%s", first_operand);
          translation[*as_stroke].type_op = 4;
          (*as_stroke)++;
        }
      if (type_of_inequaliry == 4)
        {
          (*operations)--;
          translation[*as_stroke - 1].stroke_basic = number;
          sprintf (translation[*as_stroke - 1].command, "MUL");
          sprintf (translation[*as_stroke - 1].operand, "%d", -1);
          translation[*as_stroke - 1].type_op = 2;

          translation[*as_stroke].stroke_basic = number;
          sprintf (translation[*as_stroke].command, "JNEG");
          sprintf (translation[*as_stroke].operand, "%s", first_operand);
          translation[*as_stroke].type_op = 4;
          (*as_stroke)++;

          translation[*as_stroke].stroke_basic = number;
          sprintf (translation[*as_stroke].command, "JZ");
          sprintf (translation[*as_stroke].operand, "%s", first_operand);
          translation[*as_stroke].type_op = 4;
          (*as_stroke)++;
        }
      if (type_of_inequaliry == 5)
        {

          (*operations)--;
          translation[*as_stroke - 1].stroke_basic = number;
          sprintf (translation[*as_stroke - 1].command, "JZ");
          sprintf (translation[*as_stroke - 1].operand, "%s", first_operand);
          translation[*as_stroke - 1].type_op = 4;
        }
      if (type_of_inequaliry == 6)
        {
          (*operations)--;
          translation[*as_stroke - 1].stroke_basic = number;
          sprintf (translation[*as_stroke - 1].command, "JNEG");
          sprintf (translation[*as_stroke - 1].operand, "%s", first_operand);
          translation[*as_stroke - 1].type_op = 4;

          translation[*as_stroke].stroke_basic = number;
          sprintf (translation[*as_stroke].command, "MUL");
          sprintf (translation[*as_stroke].operand, "%d", -1);
          translation[*as_stroke].type_op = 2;
          (*as_stroke)++;

          translation[*as_stroke].stroke_basic = number;
          sprintf (translation[*as_stroke].command, "JNEG");
          sprintf (translation[*as_stroke].operand, "%s", first_operand);
          translation[*as_stroke].type_op = 4;
          (*as_stroke)++;
        }
      return 0;
    }
  if (command_name == 6) //присваивание 
    {
      char tokens[50][255]; //разбиваем на токены
      char OPN[50][255];
      int index = 0;
      if (sb_stroke_in_tokens (second_operand, tokens, &index))
        return -1;
      sb_tokens_in_OPN (tokens, OPN, &index);
      sb_OPN_in_as (OPN, &index, translation, as_stroke, number, operations);
      sprintf (translation[*as_stroke - 1].operand, "%s", first_operand); //добваляем первый операнд
      translation[*as_stroke - 1].type_op = 1;
      (*operations)--;
      return 0;
    }

  return -1;
}
