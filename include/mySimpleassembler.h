#pragma once
#include <include/mySimpleComputer.h>
#define COMMANDS_SIZE 18

struct Command
{
  char *name;
  int code;
};

extern struct Command commands[];

void sa_fill_commands ();
void sa_init_translation (int *translation);

int sa_check_file_name (char *file_name, char *extension);

int sa_translation (int descriptor, int *translation);

int sa_lexer (char *line, int *address, int *sign, int *command, int *operand);
int sa_parser (int address, int sign, int command, int operand,
               int *translation);

int sa_command_validate (char *str, int *ind, int *command);
int sa_my_atoi (char *str, int *ind);

int sa_save_target_file (int descriptor, int *translation);
