#include <include/mySimpleassembler.h>

int
sa_check_file_name (char *file_name, char *extension)
{
  if (!file_name || !extension)
    return -1;
  int i = 0;
  if (file_name[0] == ' ')
    return -1;
  for (; file_name[i] != '.'; i++)
    if (file_name[i] == '\0')
      return -1;
  if (!i)
    return -1;

  for (int j = 0; extension[j]; j++)
    if (file_name[i++] != extension[j])
      return -1;
  if (file_name[i])
    return -1;
  return 0;
}
