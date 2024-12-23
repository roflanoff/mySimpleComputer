#include <include/mySimpleassembler.h>

void
sa_fill_commands ()
{
  commands[0].name = "NOP";
  commands[0].code = 0;
  commands[1].name = "CPUINFO";
  commands[1].code = 1;

  commands[2].name = "READ";
  commands[2].code = 10;
  commands[3].name = "WRITE";
  commands[3].code = 11;

  commands[4].name = "LOAD";
  commands[4].code = 20;
  commands[5].name = "STORE", commands[5].code = 21;

  commands[6].name = "ADD";
  commands[6].code = 30;
  commands[7].name = "SUB";
  commands[7].code = 31;
  commands[8].name = "DIVIDE";
  commands[8].code = 32;
  commands[9].name = "MUL";
  commands[9].code = 33;

  commands[10].name = "JUMP";
  commands[10].code = 40;
  commands[11].name = "JNEG", commands[11].code = 41;
  commands[12].name = "JZ";
  commands[12].code = 42;
  commands[13].name = "HALT";
  commands[13].code = 43;

  commands[14].name = "AND";
  commands[14].code = 52;
  commands[15].name = "OR";
  commands[15].code = 53;
  commands[16].name = "XOR";
  commands[16].code = 54;

  commands[17].name = "=";
  commands[17].code = 100;
}
