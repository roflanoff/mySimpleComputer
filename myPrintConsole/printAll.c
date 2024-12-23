#include <include/myBigChars.h>
#include <include/myPrintConsole.h>
#include <include/mySimpleComputer.h>
#include <string.h>
#include <unistd.h>

void
printAll (void)
{
  mt_clrscr ();
  bc_box (1, 1, 15, 61, 7, 0, (unsigned char *)"Оперативная память", COLOR_RED,
          0);
  bc_box (16, 1, 3, 61, 7, 0, (unsigned char *)"Редактируемая ячейка(формат)",
          COLOR_RED, COLOR_WHITE);
  bc_box (1, 62, 3, 23, 7, 0, (unsigned char *)"Аккумулятор", COLOR_RED, 0);
  bc_box (1, 85, 3, 23, 7, 0, (unsigned char *)"Регистр флагов", COLOR_RED, 0);
  bc_box (4, 62, 3, 23, 7, 0, (unsigned char *)"Счетчик команд", COLOR_RED, 0);
  bc_box (4, 85, 3, 23, 7, 0, (unsigned char *)"Команда", COLOR_RED, 0);
  bc_box (7, 62, 12, 46, 7, 0,
          (unsigned char *)"Редактируемая ячейка(увеличено)", COLOR_RED,
          COLOR_WHITE);
  bc_box (19, 1, 7, 67, 7, 0, (unsigned char *)"Кеш процессора", COLOR_GREEN,
          COLOR_WHITE);
  bc_box (19, 68, 7, 11, 7, 0, (unsigned char *)"IN-OUT", COLOR_GREEN,
          COLOR_WHITE);
  bc_box (19, 79, 7, 29, 7, 0, (unsigned char *)"клавиши", COLOR_GREEN,
          COLOR_WHITE);

  char buffer[100];

  mt_gotoXY (20, 80);
  int buffer_size = sprintf (buffer, "l - load s - save i - reset");
  write (1, buffer, buffer_size);

  mt_gotoXY (21, 80);
  buffer_size = sprintf (buffer, "r - run t - step");
  write (1, buffer, buffer_size);

  mt_gotoXY (22, 80);
  buffer_size = sprintf (buffer, "Esc - выход");
  write (1, buffer, buffer_size);

  mt_gotoXY (23, 80);
  buffer_size = sprintf (buffer, "F5 - accumulator");
  write (1, buffer, buffer_size);

  mt_gotoXY (24, 80);
  buffer_size = sprintf (buffer, "F6 - instruction counter");
  write (1, buffer, buffer_size);

  for (int i = 0; i < MEMORY; i++)
    {
      if (_Active_Cell == i)
        {
          printCell (i, 0, 7);
        }
      else
        printCell (i, 7, 0);
    }
  int value = 0;
  sc_memoryGet (_Active_Cell, &value);
  printDecodedCommand (value);
  printBigCell ();

  printTerm0 ();
  printCounters ();
  printAccumulator ();
  printFlags ();
  printCommand ();
  printCash ();
}
