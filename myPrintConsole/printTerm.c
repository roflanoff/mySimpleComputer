#include <include/myPrintConsole.h>
#include <include/mySimpleComputer.h>
#include <string.h>
#include <unistd.h>

void
printTerm (int address, int input)
{
  int value = 0;
  for (int i = 3; i >= 0; i--)
    {
      IN_OUT[i + 1] = IN_OUT[i];
    }
  if (L1_get (address, &value))
    sc_memoryGet (address, &value);
  IN_OUT[0].value = value;
  IN_OUT[0].address = address;
  IN_OUT[0].input = input;
  for (int i = 0; i < 5; i++)
    {
      mt_gotoXY (24 - i, 69);
      char data[100];
      if (IN_OUT[i].input)
        {
          sprintf (data, "%03d>" DECODED_COMMAND, IN_OUT[i].address,
                   TO_DECODED_COMMAND (value));
        }
      else
        {
          sprintf (data, "%03d<" DECODED_COMMAND, IN_OUT[i].address,
                   TO_DECODED_COMMAND (value));
        }
      write (STDOUT_FILENO, data, strlen (data));
    }
}

void
printTerm0 (void)
{
  for (int i = 0; i < 5; i++)
    {
      mt_gotoXY (24 - i, 69);
      char data[100];
      if (IN_OUT[i].input)
        {
          sprintf (data, "%03d>" DECODED_COMMAND, IN_OUT[i].address,
                   TO_DECODED_COMMAND (IN_OUT[i].value));
        }
      else
        {
          sprintf (data, "%03d<" DECODED_COMMAND, IN_OUT[i].address,
                   TO_DECODED_COMMAND (IN_OUT[i].value));
        }
      write (STDOUT_FILENO, data, strlen (data));
    }
}
