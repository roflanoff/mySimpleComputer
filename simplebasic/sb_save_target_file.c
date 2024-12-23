#include <include/mySimplebasic.h>
#include <string.h>

int
sb_save_target_file (int descriptor, struct as_command *translation,
                     int as_stroke)
{

  int bytes_written = 0;
  char data[256];
  for (int i = 0; i < as_stroke; i++)
    {
      sprintf (data, "%02d ", i);
      bytes_written = write (descriptor, data, strlen (data));
      if (strlen (data) != bytes_written)
        return -1;
      sprintf (data, "%s ", translation[i].command);
      bytes_written = write (descriptor, data, strlen (data));
      if (strlen (data) != bytes_written)
        return -1;
      sprintf (data, "%s", translation[i].operand);
      bytes_written = write (descriptor, data, strlen (data));
      if (strlen (data) != bytes_written)
        return -1;
      sprintf (data, "\n");
      bytes_written = write (descriptor, data, strlen (data));
      if (strlen (data) != bytes_written)
        return -1;
    }
  return 0;
}
