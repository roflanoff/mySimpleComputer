#include <include/myPrintConsole.h>
#include <include/mySimpleComputer.h>
#include <string.h>
#include <unistd.h>

void
printDecodedCommand (int value)
{
  char data[100];
  mt_gotoXY (17, 2);
  sprintf (data, "dec: %05d | oct: %05o | hex: %04X bin: " BINARY_PATTERN,
           value, value, value, TO_BINARY (value));
  write (STDOUT_FILENO, data, strlen (data));
}
