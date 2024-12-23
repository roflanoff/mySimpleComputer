#include <include/mySimplebasic.h>
#include <stdio.h>

char *command_list[7]; // АССОЦИАВТИЫВНЫЙ МАССИВ СО СПИСОКМ КОМАНД

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
  char *orig_file_name = argv[1];
  char *target_file_name = argv[2];

  if (sb_check_file_name (orig_file_name, ".sb"))
    {
      printf ("название исходного файла не содержит расширения .sa\n");
      return -1;
    }
  if (sb_check_file_name (target_file_name, ".sa"))
    {
      printf ("название целевого файла не содержит расширения .o\n");
      return -1;
    }

  int descriptor = open (orig_file_name, O_RDONLY, S_IRWXU);
  if (descriptor == -1)
    {
      printf ("Не удалось открыть исходный файл %s\n", orig_file_name);
      return -1;
    }

  sb_fill_commands ();
  struct as_command translation[128]; //массив из 128 строк ассмеблерного кода
  int as_stroke = 0;
  sb_init_translation (translation);

  int translation_result
      = sb_translation (descriptor, translation, &as_stroke);
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
  descriptor
      = open (target_file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU); //
  if (descriptor == -1)
    {
      printf ("Не удалось открыть целевой файл %s\n", target_file_name);
      return -1;
    }
  int save_result = sb_save_target_file (descriptor, translation, as_stroke);
  close (descriptor);
  if (save_result)
    printf ("ошибка при записи целевого файла\n");
  return save_result;
  return 0;
}
