/*
** EPITECH PROJECT, 2020
** strace.h
** File description:
** Strace
*/

#ifndef STRACE_H
#define STRACE_H

#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <ctype.h>

typedef struct flags_t {
    bool p;
    int p_value;
    bool s;
    bool error;
    int index;
}flags_s;

int parse_and_execute(int argc, char **argv);
int execution_loop(pid_t child, bool is_detailed);
int wait_for_syscall(pid_t child);
int syscall_loop(pid_t child, bool is_detailed);
int execute_binary(char **argv, bool is_detailed);
bool is_error(int argc, char **argv);
bool end_syscall(int status);
void print_without_option(int status, pid_t child, \
                        struct user_regs_struct regs);
void print_with_option(int status, pid_t child, struct user_regs_struct regs);
void print_detailed_syscall_parameters(int sys_number, \
                                    struct user_regs_struct regs, pid_t child);
void print_return_register(int sys_number, pid_t child, \
                            unsigned long long _register);
void print_syscall_parameters(int sys_number, struct user_regs_struct regs);
bool check_help(int argc, char **argv);
bool check_digit(char *str);
int print_error(void);
void parse_args_conditions(char **argv, flags_s *flags, int x);
int good_call_third(flags_s *flags, char **argv);
char *check_alloc(int i, int read, char *str);
void choose_print(char *str);
void choose_print_back(char *str);
void check_error(char **argv, int x, flags_s *flags);

#endif /* !STRACE_H */
