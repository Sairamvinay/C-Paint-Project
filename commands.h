#ifndef COMMANDS_H
#define COMMANDS_H


#include "canvas.h"
bool check_valid_int(int integer,int num_args_read,char *arg_name);
void check_args(int argc,char **argv,int *num_rows,int *num_cols);
void print_help();
void keep_commanding(Canvas *canvas);


#endif
