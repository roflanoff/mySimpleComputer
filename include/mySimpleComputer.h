#pragma once
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define SIGN_MASK 16384
#define COMMAND_MASK 16256
#define OPERAND_MASK 127

#define BINARY_PATTERN "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"

#define TO_BINARY(byte)                                                       \
  ((byte)&0x4000 ? '1' : '0'), ((byte)&0x2000 ? '1' : '0'),                   \
      ((byte)&0x1000 ? '1' : '0'), ((byte)&0x800 ? '1' : '0'),                \
      ((byte)&0x400 ? '1' : '0'), ((byte)&0x200 ? '1' : '0'),                 \
      ((byte)&0x100 ? '1' : '0'), ((byte)&0x80 ? '1' : '0'),                  \
      ((byte)&0x40 ? '1' : '0'), ((byte)&0x20 ? '1' : '0'),                   \
      ((byte)&0x10 ? '1' : '0'), ((byte)&0x08 ? '1' : '0'),                   \
      ((byte)&0x04 ? '1' : '0'), ((byte)&0x02 ? '1' : '0'),                   \
      ((byte)&0x01 ? '1' : '0')

#define DECODED_COMMAND "%c%02X%02X"

#define TO_DECODED_COMMAND(value)                                             \
  value &SIGN_MASK ? '-' : '+', (value & COMMAND_MASK) >> 7,                  \
      value &OPERAND_MASK

#define MEMORY 128
#define MAX_VALUE 32767
#define MAX_NATURAL_VALUE 16383
#define MAX_COUNTER_VALUE 255
#define MAX_OPERAND_VALUE 127
#define MIN_VALUE 0

#define OVERFLOW 16
#define DIVISION_BY_ZERO 8
#define OUT_OF_MEMORY 4
#define IGNORE_COUNTER 2
#define WRONG_COMMAND 1

extern int RAM[MEMORY];
extern int _Accumulator;
extern int _Commands;
extern int _Flags;
extern int _Downtime_Counter;

int sc_memoryInit (void);
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memorySave (char *filename);
int sc_memoryLoad (char *filename);
int sc_regInit (void);
int sc_regSet (int reg, int value);
int sc_regGet (int reg, int *value);
int sc_accumulatorInit (void);
int sc_accumulatorSet (int value);
int sc_accumulatorGet (int *value);
int sc_icounterInit (void);
int sc_icounterSet (int value);
int sc_icounterGet (int *value);
int sc_commandEncode (int sign, int command, int operand, int *value);
int sc_commandDecode (int value, int *sign, int *command, int *operand);
int sc_commandValidate (int command);
