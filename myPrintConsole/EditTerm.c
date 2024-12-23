#include <include/myPrintConsole.h>

void
EditTerm (int cell)
{
  int x_pos = 24;
  int y_pos = 69;
  int value;
  char buffer[10];
  int buffer_size = sprintf (buffer, "%03d<", cell);
  mt_gotoXY (x_pos, y_pos);
  write (1, buffer, buffer_size);

  mt_gotoXY (x_pos, y_pos + 4);
  mt_setbgcolor (COLOR_GREEN);
  write (1, "     ", 5);
  mt_gotoXY (x_pos, y_pos + 4);
  if (rk_readvalue (&value, 60))
    value = 0; // если не был произведен ввод

  sc_memorySet (cell, value);
  L1_set (cell, value);
  mt_setdefaultcolor ();
  printTerm (cell, 0);
}
