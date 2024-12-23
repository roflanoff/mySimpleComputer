#include <include/myPrintConsole.h>

void
CU ()
{
  int cell;
  int i_counter;
  sc_icounterGet (&i_counter);
  if (L1_get (i_counter, &cell))
    return;
  int sign;
  int command;
  int operand;
  sc_commandDecode (cell, &sign, &command, &operand);

  if (sign) // не команда
    {
      sc_regSet (IGNORE_COUNTER, 1);
      sc_regSet (WRONG_COMMAND, 1);
      return;
    }
  if (!sc_commandValidate (command)) // ошибка при декодировании комады
    {
      sc_regSet (IGNORE_COUNTER, 1);
      sc_regSet (WRONG_COMMAND, 1);
      return;
    }

  int is_jump = 0; // 1 - был переход
  int value;
  int sign_buf, command_buf, operand_buf;
  int ALU_result;
  switch (command)
    {
    case 0:
      break;
    case 1:
      printAuthor ();
      break;

    case 10:
      EditTerm (operand);
      break;

    case 11:
      printTerm (operand, 1);
      break;

    case 20:
      if (L1_get (operand, &value))
        return;
      sc_accumulatorSet (value);
      break;

    case 21:
      sc_accumulatorGet (&value);
      if (L1_set (operand, value))
        return;
      break;

    case 40:
      if (operand >= 0 && operand < MEMORY)
        {
          sc_icounterSet (operand);
          is_jump = 1;
        }
      else
        {
          sc_regSet (IGNORE_COUNTER, 1);
          sc_regSet (OUT_OF_MEMORY, 1);
          return;
        }

      break;

    case 41:

      sc_accumulatorGet (&value);
      sc_commandDecode (value, &sign_buf, &command_buf, &operand_buf);
      if (operand >= 0 && operand < MEMORY)
        {
          if (sign_buf)
            {
              sc_icounterSet (operand);
              is_jump = 1;
            }
        }
      else
        {
          sc_regSet (IGNORE_COUNTER, 1);
          sc_regSet (OUT_OF_MEMORY, 1);
          return;
        }
      break;

    case 42:
      sc_accumulatorGet (&value);
      if (operand >= 0 && operand < MEMORY)
        {
          if (value == 0)
            {
              sc_icounterSet (operand);
              is_jump = 1;
            }
        }
      else
        {
          sc_regSet (IGNORE_COUNTER, 1);
          sc_regSet (OUT_OF_MEMORY, 1);
          return;
        }
      break;

    case 43:
      sc_regSet (IGNORE_COUNTER, 1);
      is_jump = 1;
      break;

    default:
      sc_regSet (OVERFLOW, 0);
      ALU_result = ALU (command, operand);
      if (ALU_result)
        {
          return;
        }
    }

  if (!is_jump)
    {
      if ((i_counter + 1) < MEMORY)
        sc_icounterSet (i_counter + 1);
      else
        {
          sc_regSet (IGNORE_COUNTER, 1);
          sc_regSet (OUT_OF_MEMORY, 1);
        }
    }
}
