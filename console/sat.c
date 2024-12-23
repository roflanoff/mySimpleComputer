#include <include/mySimpleassembler.h>
#include <stdio.h>

struct Command commands[COMMANDS_SIZE];

int
main (int argc, char *argv[])
{
  if (argc < 2)
    {
      printf ("не передано название исходного файла\n");
      return -1;
    }

  if (argc < 3)
    {
      printf ("не передано название целевого файла\n");
      return -1;
    }
  char *orig_file_name = argv[1]; //
  char *target_file_name = argv[2];//передае м туда всё

  if (sa_check_file_name (orig_file_name, ".sa"))
    {
      printf ("название исходного файла не содержит расширения .sa\n");
      return -1;
    }
  if (sa_check_file_name (target_file_name, ".o"))
    {
      printf ("название целевого файла не содержит расширения .o\n");
      return -1;
    }

  int descriptor = open (orig_file_name, O_RDONLY, S_IRWXU);//дальше файл можно перезаписать - права файла, разрешения
  if (descriptor == -1)
    {
      printf ("Не удалось открыть исходный файл %s\n", orig_file_name);
      return -1;
    }

  sa_fill_commands ();
  int translation[MEMORY];//массив, 
  sa_init_translation (translation);

  int translation_result = sa_translation (descriptor, translation);//переделывает аську в бин файлик
  close (descriptor);
  if (translation_result > 0)
    {
      printf ("ошибка при трансляции файла. строка %d\n", translation_result);
      return -1;
    }
  if (translation_result == -1)
    {
      printf ("ошибка при трансляции файла.\n");
      return -1;
    }

  descriptor = open (target_file_name, O_WRONLY | O_CREAT, S_IRWXU); 
  if (descriptor == -1)
    {
      printf ("Не удалось открыть целевой файл %s\n", target_file_name);
      return -1;
    }

  int save_result = sa_save_target_file (descriptor, translation);
  close (descriptor);
  if (save_result)
    printf ("ошибка при записи целевого файла\n");
  return save_result;
}
