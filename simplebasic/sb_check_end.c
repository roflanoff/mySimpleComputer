#include <include/mySimplebasic.h>

int
sb_check_end (char *line, int *ind_in_line)
{
  if (line[*ind_in_line] == '\0')
    return 0;
  for (; line[*ind_in_line] == ' '; (*ind_in_line)++)
    ;
  if (line[*ind_in_line] != '\0')
    return -1;
  return 0;
}
