#include <include/mySimplebasic.h>

#define skip() for (; line[ind_in_line] == ' '; ind_in_line++) // СКИП ПРОБЕЛОВ 
int
sb_lexer (int *number, int *command_name, char *first_operand,
          char *second_operand, int *type_of_inequaliry, char *line)
{
  int ind_in_line = 0;

  skip ();

  *number = sb_my_atoi (line, &ind_in_line); // адрес ячейки памяти
  if (*number == -1)
    return -1; // не удалось считать адрес ячейки памяти
  if (((*number) % 10 != 0) || (*number) < 10) // проверяем кратно ли оно 10, потому что 10 20 30 и тд
    return -1;
  if (line[ind_in_line] != ' ') // после адреса должен быть пробел
    return -1;
  skip ();

  int validate_result = sb_command_validate (line, &ind_in_line, command_name);
  if (validate_result)
    return -1;
  if (*command_name == 0) // коментарий игнорируем 
    return 0;
  if (*command_name == 4) // енд, чтобы после него ничего не было
    {
      return sb_check_end (line, &ind_in_line);// чтобы был конец строки или проблеы
    }

  if (line[ind_in_line] != ' ') // после команды должен быть пробел
    return -1;
  skip ();

  if (*command_name == 1 || *command_name == 2) //принимают только букву
    {
      if (line[ind_in_line] >= 'A' && line[ind_in_line] <= 'Z')
        {
          first_operand[0] = line[ind_in_line]; // операнд // 0 индекс первого операнда
          first_operand[1] = '\0'; 
          ind_in_line++;
          return sb_check_end (line, &ind_in_line); // чтоб в конце ничего не было
        }
      else
        return -1;
    }

  if (*command_name == 3) // гоу ту . оперданд только число - андрес
    {
      if (line[ind_in_line] < '0' || line[ind_in_line] > '9')
        return -1; // передано не число
      int index = 0; // индекс в 1 операнде 
      while (line[ind_in_line] >= '0' && line[ind_in_line] <= '9')
        {
          first_operand[index] = line[ind_in_line]; // число которое записано в текущей строке и присваиваем его первому операнду
          ind_in_line++;
          index++;
        }
      first_operand[index] = '\0';
      return sb_check_end (line, &ind_in_line);
    }

  if (*command_name == 5) // если
    {
      int br = 0; // количество открытых скобочек
      int index = 0; //индекс в 2 операнде
      second_operand[index++] = '('; // начинаем заключать левую часть условия в скобки 
      while (sb_is_expression (line[ind_in_line])) // пока у нас всё хорошо с проверкой ( возвращает 1)
        {
          if (line[ind_in_line] == '(') //если открыта скобка 
            br++; // прибавляем колчиество открытых скобок
          if (line[ind_in_line] == ')') //если закрыта
            br--; // то уменьшаем
          second_operand[index] = line[ind_in_line]; // перекопируем в секнд операнд всё левое условие
          ind_in_line++;
          index++;
          skip ();
        }
      if (br != 0) //если плохо со скобками то проблема
        return -1;
      if (line[ind_in_line] == '<')
        {
          ind_in_line++;
          if (line[ind_in_line] == '=')
            {
              ind_in_line++;
              *type_of_inequaliry = 3; //присваиваем код операции сравнения
            }
          else
            *type_of_inequaliry = 1;
        }
      else if (line[ind_in_line] == '>')
        {
          ind_in_line++;
          if (line[ind_in_line] == '=')
            {
              ind_in_line++;
              *type_of_inequaliry = 4;
            }
          else
            *type_of_inequaliry = 2;
        }
      else if (line[ind_in_line] == '=')
        {
          ind_in_line++;
          *type_of_inequaliry = 5;
        }
      else if (line[ind_in_line] == '!')
        {
          ind_in_line++;
          if (line[ind_in_line] == '=')
            {
              ind_in_line++;
              *type_of_inequaliry = 6;
            }
          else
            return -1;
        }
      else // если после левой части нет знака то условие не правильное
        return -1;
      second_operand[index++] = ')'; // закрываем скобочкой левую часть условия
      second_operand[index++] = '-'; //комп не умеет сравниваеть, поэтому он вычитает и проверяет итог больше или меньше 0 
      second_operand[index++] = '('; //начинаем правое условие
      skip ();
      while (sb_is_expression (line[ind_in_line]))
        {

          second_operand[index] = line[ind_in_line];
          ind_in_line++;
          index++;
          skip ();
          if (line[ind_in_line] == 'G' && line[ind_in_line + 1] == 'O')
            break;
        }
      second_operand[index++] = ')'; // закрываем скобку
      second_operand[index] = '\0';
      for (int i = 0; i < 4; i++)
        {
          if (line[ind_in_line++] != command_list[3][i]) // проверяем что реально гоу ту после иф
            {
              return -1;
            }
        }
      if (line[ind_in_line] != ' ') // после команды должен быть пробел
        return -1;
      skip ();
      if (line[ind_in_line] < '0' || line[ind_in_line] > '9')
        return -1; // передано не число
      int index2 = 0;
      while (line[ind_in_line] >= '0' && line[ind_in_line] <= '9')
        {
          first_operand[index2] = line[ind_in_line]; //копируем в 1 операнд ( после гоу ту первый операнд идет)
          ind_in_line++;
          index2++;
        }
      first_operand[index2] = '\0';
      return sb_check_end (line, &ind_in_line);
    }

  if (*command_name == 6) //присваивание 
    {
      if (line[ind_in_line] >= 'A' && line[ind_in_line] <= 'Z')
        {
          first_operand[0] = line[ind_in_line]; // операнд
          first_operand[1] = '\0';
          ind_in_line++;
          skip ();
          if (line[ind_in_line] == '=') // что реально знак = после пробела
            {
              ind_in_line++;
              skip ();
              int index = 0; // индекс в секонд операнде
              while (sb_is_expression (line[ind_in_line]))
                {
                  second_operand[index] = line[ind_in_line]; // копируем алгебраическое условие 
                  ind_in_line++;
                  index++;
                  skip ();
                }
              second_operand[index] = '\0';
              return sb_check_end (line, &ind_in_line);
            }
          return -1;
        }
      else
        return -1;
    }
  return -1;
}
