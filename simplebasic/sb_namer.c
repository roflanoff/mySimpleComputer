#include <include/mySimplebasic.h>
#include <string.h>
 //создает перемнные прямо в памяти
int
sb_namer (int *as_stroke, struct as_command *translation)
{
  struct as_operand mas_operands[128]; // массивы добвлять утад перемнные и проверять еслть ли там пееремннеы
  int count = 0;
  for (int i = 0; i < *as_stroke; i++) //количесвто декодированных строк 
    {
      if (translation[i].type_op == 1 || translation[i].type_op == 3) //по всему массиву с ячейками с токенами
        {

          int is_there = -1; // которая определяет есть ли в массиву эта переменная 
          for (int j = 0; j < count; j++)
            {
              if (strcmp (translation[i].operand, mas_operands[j].name) == 0) //есть ли переменная или конспента в списке
                is_there = j; // приравниваем к индексу в этом массиве с переменными мас операнд
            }

          if (is_there == -1) //если ничего не найдено, добаывляем
            {
              sprintf (mas_operands[count].name, "%s", translation[i].operand);
              mas_operands[count].pointer = *as_stroke;
              sprintf (translation[i].operand, "%d",
                       mas_operands[count].pointer);
              count++;
              translation[*as_stroke].stroke_basic = -1;
              sprintf (translation[*as_stroke].command, "=");
              sprintf (translation[*as_stroke].operand, "+0000"); //создаем и зануляем

              translation[*as_stroke].type_op = 0;
              (*as_stroke)++;
            }
          else
            sprintf (translation[i].operand, "%d",
                     mas_operands[is_there].pointer); //операнд теперь в строке которую мы обрабатывали 
        }
      if (translation[i].type_op == 2)
        {
          int is_there = -1;
          for (int j = 0; j < count; j++)
            {
              if (strcmp (translation[i].operand, mas_operands[j].name) == 0)
                is_there = j;
            }

          if (is_there == -1)
            {

              sprintf (mas_operands[count].name, "%s", translation[i].operand);
              mas_operands[count].pointer = *as_stroke;

              sprintf (translation[i].operand, "%d",
                       mas_operands[count].pointer);
              int tmp = 0;
              int integer = sb_my_atoi (mas_operands[count].name, &tmp);
              translation[*as_stroke].stroke_basic = -1;
              sprintf (translation[*as_stroke].command, "=");
              sprintf (translation[*as_stroke].operand, "%+05d", integer); //обязательно будет ранва 5 символам.
//если меньше , то зануляем
              translation[*as_stroke].type_op = 0;
              (*as_stroke)++;
              count++;
            }
          else
            sprintf (translation[i].operand, "%d",
                     mas_operands[is_there].pointer);
        }
      if (translation[i].type_op == 4) //нмоер ячейки гоу ту оператор
        {
          int pointer = 0;
          int tmp = 0;
          int p = sb_my_atoi (translation[i].operand, &tmp); //перегоняем операнд в число
          for (int j = 0; p > translation[j].stroke_basic; j++) //пробегаем по всем ячейкам транслейшена итогового набора команд на аське
            {
              if (j > *as_stroke) 
                return -1;
              pointer++;
            }
          sprintf (translation[i].operand, "%d", pointer); //индекс в нашем массиве транслейшен
          translation[i].type_op = 0;
        }
    }
  return 0;
}
