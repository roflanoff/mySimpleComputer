#include <include/myBigChars.h>

int
bc_box (int x1, int y1, int x2, int y2, enum colors box_fg, enum colors box_bg,
        unsigned char *header, enum colors header_fg, enum colors header_bg)
{

  int length = bc_strlen (header);
  if (!length)
    return -1;

  mt_setfgcolor (box_fg);
  mt_setbgcolor (box_bg);
  mt_gotoXY (x1, y1);
  bc_printA ("l");
  mt_gotoXY (x1, y1 + y2 - 1);
  bc_printA ("k");
  mt_gotoXY (x1 + x2 - 1, y1);
  bc_printA ("m");
  mt_gotoXY (x1 + x2 - 1, y1 + y2 - 1);
  bc_printA ("j");
  mt_gotoXY (x1, y1 + 1);
  for (int i = 0; i < y2 - 2; i++)
    {
      bc_printA ("q");
    }
  mt_gotoXY (x1 + x2 - 1, y1 + 1);
  for (int i = 0; i < y2 - 2; i++)
    {
      bc_printA ("q");
    }

  for (int i = 1; i < x2 - 1; i++)
    {
      mt_gotoXY (x1 + i, y1);
      bc_printA ("x");
    }

  for (int i = 1; i < x2 - 1; i++)
    {
      mt_gotoXY (x1 + i, y1 + y2 - 1);
      bc_printA ("x");
    }
  mt_setfgcolor (header_fg);
  mt_setbgcolor (header_bg);
  char buffer[100];
  int h = (y2 - length) / 2;
  mt_gotoXY (x1, y1 + h);
  int buffer_size = sprintf (buffer, "%s", header);
  int writeResult = write (1, buffer, buffer_size); // вывод заголовка
  if (writeResult != buffer_size)
    return -1;
  mt_setdefaultcolor ();
  return 0;
}
