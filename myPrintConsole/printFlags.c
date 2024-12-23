#include <include/myPrintConsole.h>
#include <include/mySimpleComputer.h>
#include <string.h>
#include <unistd.h>

void
printFlags (void)
{
  int value = _Flags;
  mt_gotoXY (2, 89);
  char data[100];
  sprintf (
      data, "%c  %c  %c  %c  %c", value & OVERFLOW ? 'P' : '_',
      value & DIVISION_BY_ZERO ? '0' : '_', value & OUT_OF_MEMORY ? 'M' : '_',
      value & IGNORE_COUNTER ? 'T' : '_', value & WRONG_COMMAND ? 'E' : '_');
  write (STDOUT_FILENO, data, strlen (data));
}
