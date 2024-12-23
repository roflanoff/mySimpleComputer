#include <include/myPrintConsole.h>
#define MAX_FILE_NAME 255
// запись ОЗУ в файл, считывание из файла, сброс
void
LoadMem (enum keys readed_key)
{
  if (readed_key == SEQ_s) // запись оперативной памяти в файл
    {
      mt_setcursorvisible (1);
      rk_mytermrestore ();
      mt_gotoXY (26, 1);
      write (1, "Введите файл для записи оперативной памяти: ", 82);
      char buffer[MAX_FILE_NAME];
      read (0, buffer, MAX_FILE_NAME);
      char filename[MAX_FILE_NAME];
      int i = 0;
      for (; buffer[i] != '\n'; i++)
        filename[i] = buffer[i];
      filename[i] = '\0';
      if (sc_memorySave (filename))
        {
          write (0, "не удалось записать память в файл\n", 63);
          sleep (2);
        }
    }
  if (readed_key == SEQ_l) // загрузка оперативной памяти из файла
    {
      mt_setcursorvisible (1);
      rk_mytermrestore ();
      mt_gotoXY (26, 1);
      write (1, "Введите файл для загрузки оперативной памяти: ", 86);
      char buffer[MAX_FILE_NAME];
      read (0, buffer, MAX_FILE_NAME);
      char filename[MAX_FILE_NAME];
      int i = 0;
      for (; buffer[i] != '\n'; i++)
        filename[i] = buffer[i];
      filename[i] = '\0';
      if (sc_memoryLoad (filename))
        {
          write (0, "не удалось загрузить память из файла\n", 69);
          sleep (2);
        }
    }
}
