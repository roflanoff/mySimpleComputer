#include <include/myBigChars.h>

int
bc_printbigchar (int mas[2], int x, int y, enum colors fg, enum colors bg)
{
  char data[100];
  mt_setfgcolor (fg);
  mt_setbgcolor (bg);
  int tmp = 0;
  for (int i = 0; i < 8; i++)
    {
      mt_gotoXY (x + i, y);
      for (int j = 0; j < 8; j++)
        {

          bc_getbigcharpos (mas, i, j, &tmp);
          sprintf (data, "%c", tmp ? 'a' : ' ');
          bc_printA (data);
        }
    }
  mt_setdefaultcolor ();
  return 0;
}
