#pragma once
#include <include/myReadKey.h>
#include <include/mySimpleComputer.h>
#include <include/myTerm.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

struct pair_IN_OUT
{
  int value;
  int address;
  int input;
};

struct l1_cash_line
{
  int line;
  int data[10];
  int priority;
};

extern struct l1_cash_line L1_CASH[5];
extern int addr_to_input;
extern struct pair_IN_OUT IN_OUT[5];
extern int _Active_Cell;
extern int ch1[100];

void printCell (int address, enum colors fg, enum colors bg);
void printFlags (void);
void printDecodedCommand (int value);
void printAccumulator (void);
void printCounters (void);
void printTerm (int address, int input);
void printTerm0 (void);
void printCommand (void);
void printBigCell (void);
void printCash (void);

void L1_init (void);
int L1_get (int address, int *value);
int L1_set (int address, int value);
void MoveMem (enum keys readed_key);
void EditMemory (enum keys readed_key);
void EditAccumulator (enum keys readed_key);
void EditCommand (enum keys readed_key);
void EditTerm (int cell);
void LoadMem (enum keys readed_key);
void SystemCall (enum keys readed_key);
void printAll (void);
void PrintMessage (char *str);

void CU ();
int ALU (int command, int operand);
void IRC (int signum);
int MemoryController (void);

void printAuthor ();
void signalIndicator (int signal_num);
