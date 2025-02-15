#ifndef M_H
#define M_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

int slen(char *str);
int check_op(char *op);
int cnt_op(char **argv);
int op_addr(char **argv, int st);
void start(char **argv, int cnt);
void start_fork(char **argv, int cnt, int st);
void fork_semi(char **argv, int first_cmd, int null_space, int st);
#endif