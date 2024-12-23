#include <include/myTerm.h>
#include <sys/ioctl.h>
#include <unistd.h>

int
mt_getscreensize (int *rows, int *cols)
{
  struct winsize ws;
  if (!ioctl (STDOUT_FILENO, TIOCGWINSZ, &ws))
    {
      *rows = ws.ws_row;
      *cols = ws.ws_col;
    }
  else
    return -1;
  return 0;
}
