#include <include/mySimplebasic.h>

// иначе возвращает номер строки с ошибкой
int
sb_translation (int descriptor, struct as_command *translation, int *as_stroke)
{
  char fsign; //считанный символ
  char current_line[255]; // текущая строчка
  int ind_in_line = 0; // иддекс в строчке
  int line_num = 1; // номер строчки
  int operations = 0; // количество операция в 1 строке
  int end_flag = 0; //признак оокнчания файла
  while (read (descriptor, &fsign, 1))
    {
      if (fsign != '\n')
        current_line[ind_in_line++] = fsign;
      else
        {
          if (ind_in_line) // если строчка не пустая
            {
              current_line[ind_in_line++] = '\0';
              // воть токены
              int number = 0; // токен номера строчки 
              int command_name = 0;// код команды 
              char first_operand[255] = ""; // 1 операнд 
              char second_operand[255] = "";// второй операнд
              int type_of_inequaliry = 0; // код операции сравнения
              // разбиение строки на токены 
              // 6 операций сранвения  >= и тд
              int lexer_result = sb_lexer (&number, &command_name,
                                           first_operand, second_operand,
                                           &type_of_inequaliry, current_line);
              if (lexer_result)
                return line_num;
              if (number / 10 != line_num) //получаем настоящее значение, если другой то нумерация неправильная в файле 
                return line_num;
              // проверка токенов строки и формирование ячейки памяти
              int parser_result
                  = sb_parser (number, command_name, first_operand,
                               second_operand, type_of_inequaliry, as_stroke,
                               translation, &operations, &end_flag); //
              if (parser_result)
                return line_num;
            }
          line_num++;
          ind_in_line = 0;

        }
    }

  if (end_flag != 1) //есть функция енд
    return -1;
  if (sb_namer (as_stroke, translation))
    return -1;

  return 0;
}
