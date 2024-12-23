#pragma once
#include <stdio.h>

enum colors
{
  COLOR_BLACK = 0,
  COLOR_RED = 1,
  COLOR_GREEN = 2,
  COLOR_YELLOW = 3,
  COLOR_BLUE = 4,
  COLOR_MAGENTA = 5,
  COLOR_CYAN = 6,
  COLOR_WHITE = 7

};
int mt_clrscr (void);
int mt_gotoXY (int x, int y);
int mt_getscreensize (int *rows, int *cols);
int mt_setfgcolor (enum colors c);
int mt_setbgcolor (enum colors c);
int mt_setdefaultcolor (void);
int mt_setcursorvisible (int value);
int mt_delline (void);
