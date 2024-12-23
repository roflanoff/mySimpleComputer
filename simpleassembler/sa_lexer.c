#include <include/mySimpleassembler.h>
//правильность написанного и разбивает строку
int
sa_lexer (char *line, int *address, int *sign, int *command, int *operand)
{
  int ind_in_line = 0;//опять обрабатываем :(

  for (; line[ind_in_line] == ' '; ind_in_line++)
    ;

  *address = sa_my_atoi (line, &ind_in_line); // адрес ячейки памяти  //возвращает индекс строчки
  if (*address == -1)
    return -1; // не удалось считать адрес ячейки памяти

  if (line[ind_in_line] != ' ') // после адреса должен быть пробел
    return -1;
  for (; line[ind_in_line] == ' '; ind_in_line++)
    ;

  int validate_result
      = sa_command_validate (line, &ind_in_line, command); // команда
  if (validate_result)
    return -1;

  if (line[ind_in_line] != ' ') // после команды должен быть пробел
    return -1;
  for (; line[ind_in_line] == ' '; ind_in_line++)
    ;

  if (*command
      == 100) // операция присаивания значения ячейке, нужно прочитать знак
    {
      if (line[ind_in_line] == '+')
        *sign = 0;
      else if (line[ind_in_line] == '-')
        *sign = 1;
      else
        return -1; // знак отсутствует
      ind_in_line++;
      if (line[ind_in_line]
          == ' ') // пробела между знаком и числом быть не должно
        return -1;
    }

  *operand = sa_my_atoi (line, &ind_in_line); // операнд
  if (*operand == -1)
    return -1; // не удалось считать операнд
  // проверка комментария

  for (; line[ind_in_line] == ' '; ind_in_line++)
    ;
  if (line[ind_in_line] != '\0' && line[ind_in_line] != ';')
    return -1;
  return 0;
}
