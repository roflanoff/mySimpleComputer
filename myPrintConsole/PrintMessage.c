#include <include/myPrintConsole.h>
#include <string.h>

void
PrintMessage (char *str)
{
  mt_gotoXY (26, 1);
  write (STDOUT_FILENO, str, strlen (str));
}
