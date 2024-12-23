#include <fcntl.h>
#include <include/myBigChars.h>
#include <include/mySimpleComputer.h>
#include <sys/ioctl.h>
#include <unistd.h>

int RAM[128];

int
main ()
{

  mt_clrscr ();

  int ch1[36];
  for (int i = 0; i < 34; i++)
    ch1[i] = 0;

  bc_setbigcharpos (ch1 + 2, 0, 4, 1);
  bc_setbigcharpos (ch1 + 2, 0, 5, 1);
  bc_setbigcharpos (ch1 + 2, 0, 6, 1);

  bc_setbigcharpos (ch1 + 2, 1, 3, 1);
  bc_setbigcharpos (ch1 + 2, 1, 4, 1);
  bc_setbigcharpos (ch1 + 2, 1, 5, 1);
  bc_setbigcharpos (ch1 + 2, 1, 6, 1);

  bc_setbigcharpos (ch1 + 2, 2, 2, 1);
  bc_setbigcharpos (ch1 + 2, 2, 3, 1);
  bc_setbigcharpos (ch1 + 2, 2, 4, 1);
  bc_setbigcharpos (ch1 + 2, 2, 5, 1);
  bc_setbigcharpos (ch1 + 2, 2, 6, 1);

  bc_setbigcharpos (ch1 + 2, 3, 5, 1);
  bc_setbigcharpos (ch1 + 2, 3, 6, 1);

  bc_setbigcharpos (ch1 + 2, 4, 5, 1);
  bc_setbigcharpos (ch1 + 2, 4, 6, 1);

  bc_setbigcharpos (ch1 + 2, 5, 5, 1);
  bc_setbigcharpos (ch1 + 2, 5, 6, 1);

  bc_setbigcharpos (ch1 + 2, 6, 5, 1);
  bc_setbigcharpos (ch1 + 2, 6, 6, 1);

  bc_setbigcharpos (ch1 + 2, 7, 5, 1);
  bc_setbigcharpos (ch1 + 2, 7, 6, 1);

  ch1[0] = 0x6666663c;
  ch1[1] = 0x3c666666;

  ch1[4] = 0x7066663c;
  ch1[5] = 0x7e7e0c38;

  ch1[6] = 0x3860663c;
  ch1[7] = 0x3c666038;

  ch1[8] = 0x66666666;
  ch1[9] = 0x6060607c;

  ch1[10] = 0x3e06067e;
  ch1[11] = 0x3c666060;

  ch1[12] = 0x0666663c;
  ch1[13] = 0x3c66663e;

  ch1[14] = 0x3060607e;
  ch1[15] = 0x18181818;

  ch1[16] = 0x3c66663c;
  ch1[17] = 0x3c66663c;

  // 8
  ch1[18] = 0x6666663c;
  ch1[19] = 0x3c66607c;

  ch1[20] = 0x66663c18;
  ch1[21] = 0x66667e66;

  ch1[22] = 0x3e66663e;
  ch1[23] = 0x3e66663e;

  ch1[24] = 0x06663c18;
  ch1[25] = 0x183c6606;

  ch1[26] = 0x6666361e;
  ch1[27] = 0x1e366666;

  ch1[28] = 0x7e067e7e;
  ch1[29] = 0x7e7e067e;

  ch1[30] = 0x7E067e7e;
  ch1[31] = 0x0606067E;

  ch1[32] = 0x7E181800;
  ch1[33] = 0x0018187E;

  ch1[34] = 0x7E000000;
  ch1[35] = 0x0000007E;
  int file = open ("font.bin", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
  bc_bigcharwrite (file, ch1, 18);
  close (file);
  for (int i = 0; i < 30; i += 2)
    {
      bc_printbigchar (ch1 + i, 3, 3, 7, 0);
      bc_printbigchar (ch1 + i + 2, 3, 13, 7, 0);
      bc_printbigchar (ch1 + i + 4, 3, 23, 7, 0);
      bc_printbigchar (ch1 + i + 6, 3, 33, 7, 0);
      sleep (1.5);
    }
  mt_gotoXY (20, 1);
  return 0;
}
