#include <include/myPrintConsole.h>

#define minus(x)                                                              \
  ((x & SIGN_MASK) == 0) ? ((x ^ MAX_VALUE) + 1) : ((x - 1) ^ MAX_VALUE)

int
ALU (int command, int operand)
{
  int acc_value = 0, mem_value = 0, mem2_value = 0, mem3_value = 0;
  int acc_sign = 0, mem_sign = 0, mem2_sign = 0, mem3_sign = 0;

  int result = 0;
  switch (command)
    {
    case 30: //+
      sc_accumulatorGet (&acc_value);
      if (L1_get (operand, &mem_value))
        return -1;
      acc_sign = acc_value & SIGN_MASK;
      mem_sign = mem_value & SIGN_MASK;
      result = mem_value + acc_value;
      if (acc_sign == mem_sign
          && result > (acc_sign ? MAX_VALUE : MAX_NATURAL_VALUE))
        {
          sc_regSet (OVERFLOW, 1);
        }
      result &= MAX_VALUE;
      return sc_accumulatorSet (result);
      break;

    case 31: //-
      sc_accumulatorGet (&acc_value);
      if (L1_get (operand, &mem_value))
        return -1;
      if (mem_value != 0)
        mem_value = minus (mem_value);
      acc_sign = acc_value & SIGN_MASK;
      mem_sign = mem_value & SIGN_MASK;
      result = mem_value + acc_value;
      if (acc_sign == mem_sign
          && result > (acc_sign ? MAX_VALUE : MAX_NATURAL_VALUE))
        {
          sc_regSet (OVERFLOW, 1);
        }
      result &= MAX_VALUE;
      return sc_accumulatorSet (result);
      break;

    case 32:              // /
      if (mem_value == 0) // ошибка деления на 0
        {
          sc_regSet (DIVISION_BY_ZERO, 1);
          sc_regSet (IGNORE_COUNTER, 1);
          return -1;
        }
      sc_accumulatorGet (&acc_value);
      if (L1_get (operand, &mem_value))
        return -1;
      acc_sign = acc_value & SIGN_MASK;
      mem_sign = mem_value & SIGN_MASK;
      result = (acc_sign ? minus (acc_value) : acc_value)
               / ((mem_sign) ? minus (mem_value) : mem_value);
      if (result > MAX_NATURAL_VALUE)
        {
          sc_regSet (OVERFLOW, 1);
        }
      result &= MAX_VALUE;
      if (acc_sign != mem_sign && result != 0)
        result = minus (result);

      return sc_accumulatorSet (result);
      break;

    case 33: // *
      sc_accumulatorGet (&acc_value);
      if (L1_get (operand, &mem_value))
        return -1;
      acc_sign = acc_value & SIGN_MASK;
      mem_sign = mem_value & SIGN_MASK;
      if (acc_sign)
        acc_value = minus (acc_value);

      if (mem_sign)
        mem_value = minus (mem_value);
      result = acc_value * mem_value;

      if (result > MAX_NATURAL_VALUE)
        {
          sc_regSet (OVERFLOW, 1);
        }
      result &= MAX_VALUE;
      if (acc_sign != mem_sign && result != 0)
        result = minus (result);

      return sc_accumulatorSet (result);
      break;

    case 51:
      sc_accumulatorGet (&acc_value);
      result = acc_value ^ MAX_VALUE;
      return L1_set (operand, result);
      break;
    case 52:
      sc_accumulatorGet (&acc_value);
      if (L1_get (operand, &mem_value))
        return -1;
      result = acc_value & mem_value;
      if (result > MAX_VALUE)
        {
          sc_regSet (OVERFLOW, 1);
        }
      result &= MAX_VALUE;
      return sc_accumulatorSet (result);
      break;

    case 53:
      sc_accumulatorGet (&acc_value);
      if (L1_get (operand, &mem_value))
        return -1;
      result = acc_value | mem_value;
      if (result > MAX_VALUE)
        {
          sc_regSet (OVERFLOW, 1);
        }
      result &= MAX_VALUE;
      return sc_accumulatorSet (result);
      break;
    case 54:
      sc_accumulatorGet (&acc_value);
      if (L1_get (operand, &mem_value))
        return -1;
      result = acc_value ^ mem_value;
      if (result > MAX_VALUE)
        {
          sc_regSet (OVERFLOW, 1);
        }
      result &= MAX_VALUE;
      return sc_accumulatorSet (result);
      break;

    case 60: // CHL
      if (L1_get (operand, &mem_value))
        return -1;
      result = mem_value << 1;
      result &= MAX_VALUE;
      if (result > MAX_VALUE)
        {
          sc_regSet (OVERFLOW, 1);
        }
      result &= MAX_VALUE;
      return sc_accumulatorSet (result);
      break;

    case 61: // SHR
      if (L1_get (operand, &mem_value))
        return -1;
      result = mem_value >> 1;
      result &= MAX_VALUE;
      if (result > MAX_VALUE)
        {
          sc_regSet (OVERFLOW, 1);
        }
      result &= MAX_VALUE;
      return sc_accumulatorSet (result);
      break;

    case 62: // RCL
      if (L1_get (operand, &mem_value))
        return -1;
      mem_sign = mem_value & SIGN_MASK;
      result = (mem_value << 1) + (mem_sign >> 14);
      result &= MAX_VALUE;
      if (result > MAX_VALUE)
        {
          sc_regSet (OVERFLOW, 1);
        }
      result &= MAX_VALUE;
      return sc_accumulatorSet (result);
      break;

    case 63: // RCR
      L1_get (operand, &mem_value);
      result = (mem_value >> 1) + ((mem_value & 1) << 14);
      result &= MAX_VALUE;
      return sc_accumulatorSet (result);
      break;

    case 64:
      if (L1_get (operand, &mem_value))
        return -1;
      result = minus (mem_value);
      return sc_accumulatorSet (result);
      break;

    case 65: // ADDC
      sc_accumulatorGet (&acc_value);
      if (L1_get (operand, &mem_value))
        return -1;
      if (L1_get (acc_value, &mem2_value))
        return -1;
      mem2_sign = mem2_value & SIGN_MASK;
      mem_sign = mem_value & SIGN_MASK;
      result = mem_value + mem2_value;
      if (mem2_sign == mem_sign
          && result > (mem_sign ? MAX_VALUE : MAX_NATURAL_VALUE))
        {
          sc_regSet (OVERFLOW, 1);
        }
      result &= MAX_VALUE;
      return sc_accumulatorSet (result);
      break;

    case 66: // SUBC
      sc_accumulatorGet (&acc_value);
      if (L1_get (operand, &mem_value))
        return -1;
      if (L1_get (acc_value, &mem2_value))
        return -1;
      if (mem_value != 0)
        mem2_value = minus (mem2_value);
      mem2_sign = mem2_value & SIGN_MASK;
      mem_sign = mem_value & SIGN_MASK;
      result = mem_value + mem2_value;
      if (mem2_sign == mem_sign
          && result > (mem_sign ? MAX_VALUE : MAX_NATURAL_VALUE))
        {
          sc_regSet (OVERFLOW, 1);
        }
      result &= MAX_VALUE;
      return sc_accumulatorSet (result);
      break;

    case 67:
      sc_accumulatorGet (&acc_value);
      if (L1_get (operand, &mem_value))
        return -1;
      result = mem_value << acc_value;
      result &= MAX_VALUE;
      return sc_accumulatorSet (result);
      break;

    case 68:
      sc_accumulatorGet (&acc_value);
      if (L1_get (operand, &mem_value))
        return -1;
      result = mem_value >> acc_value;
      result &= MAX_VALUE;
      return sc_accumulatorSet (result);
      break;

    case 69: // RCCL
      sc_accumulatorGet (&acc_value);
      if (L1_get (operand, &mem_value))
        return -1;
      result = mem_value << acc_value;
      result += mem_value >> (15 - acc_value);
      result &= MAX_VALUE;
      return sc_accumulatorSet (result);
      break;

    case 70: // RCCR
      sc_accumulatorGet (&acc_value);
      if (L1_get (operand, &mem_value))
        return -1;
      result = mem_value >> acc_value;
      result += mem_value << (15 - acc_value);
      result &= MAX_VALUE;
      return sc_accumulatorSet (result);
      break;

    case 71: // MOVA
      sc_accumulatorGet (&acc_value);
      if (L1_get (operand, &mem_value))
        return -1;
      return L1_set (acc_value, mem_value);
      break;

    case 72: // MOVR
      sc_accumulatorGet (&acc_value);
      if (L1_get (operand, &mem_value))
        return -1;
      return L1_set (operand, mem_value);
      break;

    case 73: // MOVCA
      sc_accumulatorGet (&acc_value);
      if (L1_get (operand, &mem_value))
        return -1;
      if (L1_get (acc_value, &mem2_value))
        return -1;
      return L1_set (mem2_value, mem_value);
      break;

    case 74: // MOVCR
      sc_accumulatorGet (&acc_value);
      sc_memoryGet (acc_value, &mem_value);
      return L1_set (operand, mem_value);
      break;

    case 75: // ADDC
      sc_accumulatorGet (&acc_value);
      if (L1_get (operand, &mem_value))
        return -1;
      if (L1_get (acc_value, &mem2_value))
        return -1;
      if (L1_get (mem2_value, &mem3_value))
        return -1;
      mem3_sign = mem3_value & SIGN_MASK;
      mem_sign = mem_value & SIGN_MASK;
      result = mem3_value + mem_value;
      if (mem2_sign == mem3_sign
          && result > (mem_sign ? MAX_VALUE : MAX_NATURAL_VALUE))
        {
          sc_regSet (OVERFLOW, 1);
        }
      result &= MAX_VALUE;
      return sc_accumulatorSet (result);
      break;

    case 76: // SUBC
      sc_accumulatorGet (&acc_value);
      if (L1_get (operand, &mem_value))
        return -1;
      if (L1_get (acc_value, &mem2_value))
        return -1;
      if (L1_get (mem2_value, &mem3_value))
        return -1;
      if (mem_value != 0)

        mem3_value = minus (mem3_value);
      mem3_sign = mem3_value & SIGN_MASK;
      mem_sign = mem_value & SIGN_MASK;
      result = mem3_value + mem_value;
      if (mem2_sign == mem3_sign
          && result > (mem_sign ? MAX_VALUE : MAX_NATURAL_VALUE))
        {
          sc_regSet (OVERFLOW, 1);
        }
      result &= MAX_VALUE;
      return sc_accumulatorSet (result);
      break;

    default:
      return -1;
      break;
    }
  // sc_accumulatorSet (result);
  return -1;
}
