#ifndef M_H
#define M_H

#include <unistd.h>
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
#endif