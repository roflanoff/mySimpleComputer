#include <include/mySimpleassembler.h>

// иначе возвращает номер строки с ошибкой
int
sa_translation (int descriptor, int *translation)
{
  char fsign;//читаемае буква
  char current_line[200];//текущая строка
  int ind_in_line = 0;//индекс в строке
  int line_num = 1;//номер строки в файлике
  while (read (descriptor, &fsign, 1))
    {
      if (fsign != '\n')//пока не дошли до конца строчки
        current_line[ind_in_line++] = fsign;//+ целевой знак
      else
        {
          if (ind_in_line)
            {
              current_line[ind_in_line++] = '\0';//знак переноса на знак в знак конца строчки, потому что читаем конкретную строчку
              int address, sign = 0, command, operand;
              // разбиение строки на токены
              int lexer_result = sa_lexer (current_line, &address, &sign,
                                           &command, &operand);//либо 0, либо 1
              if (lexer_result)
                return line_num;
              // проверка токенов строки и формирование ячейки памяти
              int parser_result
                  = sa_parser (address, sign, command, operand, translation);//0 или 1 ошибся или нет
              if (parser_result)
                return line_num;
            }
          line_num++;
          ind_in_line = 0;
          if (line_num == 128) // длина файла привышает 128 строк
            return -1;
        }
    }
  return 0;
}
