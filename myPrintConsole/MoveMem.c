#include <include/myPrintConsole.h>
#include <include/myReadKey.h>
#include <include/mySimpleComputer.h>
#include <string.h>
#include <unistd.h>

void
MoveMem (enum keys readed_key)
{
  if (readed_key == SEQ_UP)
    {
      if (_Active_Cell - 10 >= 0)
        _Active_Cell -= 10;
      else
        _Active_Cell += (_Active_Cell + 120 < MEMORY) ? 120 : 110;
    }
  if (readed_key == SEQ_DOWN)
    {
      if (_Active_Cell + 10 < MEMORY)
        _Active_Cell += 10;
      else
        _Active_Cell -= (_Active_Cell - 120 >= 0) ? 120 : 110;
    }
  if (readed_key == SEQ_LEFT)
    {
      if (_Active_Cell % 10)
        _Active_Cell--;
      else
        _Active_Cell += (_Active_Cell + 9 < MEMORY) ? 9 : 7;
    }
  if (readed_key == SEQ_RIGHT)
    {
      if ((_Active_Cell + 1) % 10 && _Active_Cell != MEMORY - 1)
        _Active_Cell++;
      else
        _Active_Cell
            -= (_Active_Cell - 9 >= 0 && _Active_Cell != MEMORY - 1) ? 9 : 7;
    }
}
