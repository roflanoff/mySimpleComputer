#pragma once
#include <include/mySimpleComputer.h>

struct as_command
{
  int stroke_basic; //номер строки в имсходном файле на басике
  char command[255];// команда на аське
  char operand[255];// операнд на аське 3 вида - переменная(буква), число, адрес(куда будем переходить с гото)
  int type_op;// определяет обработку операнда 
  // тип операнда 1- переменная 2- число 3- временная переменная 4- адрес перехода
};

struct as_operand
{
  int pointer; //нмоер строки в ассемблере
  char name[255];//имя ( перемнная, контсанта )
};

extern char *command_list[7];

void sb_init_translation (struct as_command *translation);
int sb_check_file_name (char *file_name, char *extension);
int sb_command_validate (char *str, int *ind, int *command_name);
void sb_fill_commands (void);
int sb_my_atoi (char *str, int *ind);
int sb_lexer (int *number, int *command_name, char *first_operand,
              char *second_operand, int *type_of_inequaliry,
              char *curren_line);
int sb_parser (int number, int command_name, char *first_operand,
               char *second_operand, int type_of_inequaliry, int *as_stroke,
               struct as_command *translation, int *operations, int *end_flag);
int sb_translation (int descriptor, struct as_command *translation,
                    int *as_stroke);
int sb_check_end (char *str, int *ind);
int sb_is_expression (char a);
int sb_symbol_priority (char a);
int sb_stroke_in_tokens (char *second_operand, char tokens[50][255],
                         int *index);
int sb_tokens_in_OPN (char tokens[50][255], char OPN[50][255], int *index);
int sb_OPN_in_as (char OPN[50][255], int *index,
                  struct as_command *translation, int *as_stroke, int number,
                  int *operations);
int sb_namer (int *as_stroke, struct as_command *translation);
int sb_save_target_file (int descriptor, struct as_command *translation,
                         int as_stroke);
