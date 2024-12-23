#include <include/mySimpleassembler.h>

#define minus(x)                                                              \
  ((x & SIGN_MASK) == 0) ? ((x ^ MAX_VALUE) + 1) : ((x - 1) ^ MAX_VALUE)
//число в отриц версию
int
sa_parser (int address, int sign, int command, int operand, int *translation)
{

  if (command == 100)
    {
      if (sign == 1)//если минус то переводим в отрицательное значение
        {
          operand = minus (operand);
          operand &= MAX_NATURAL_VALUE;
        }
      command = operand >> 7;//приводит в нужный вид
      operand = operand & 127;
    }

  int value;
  int encode_result = sc_commandEncode (sign, command, operand, &value);

  if (encode_result)
    return -1;
  if (address >= MEMORY || address < 0)
    return -1;
  translation[address] = value;
  return 0;
}
