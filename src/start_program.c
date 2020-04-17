/*
** EPITECH PROJECT, 2020
** start_program.c
** File description:
** start_program.c
*/

#include "strace.h"
#include "sys_call_name.h"

bool end_syscall(int status)
{
    return ((WSTOPSIG(status) == SIGTRAP || WSTOPSIG(status) == SIGSTOP) \
    && WIFSTOPPED(status));
}

void chose_print(bool is_detailed, int status, const pid_t child,\
                struct user_regs_struct regs)
{
    if (is_detailed == true)
        print_with_option(status, child, regs);
    else
        print_without_option(status, child, regs);
}

int syscall_loop(const pid_t child, bool is_detailed)
{
    struct user_regs_struct regs;
    int status = 0;
    pid_t _wait;
    unsigned short int sys_index = 0;

    _wait = waitpid(child, &status, 0);
    while (end_syscall(status)) {
        ptrace(PTRACE_GETREGS, child, NULL, &regs);
        sys_index = ptrace(PTRACE_PEEKTEXT, child, regs.rip, NULL);
        ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
        _wait = waitpid(child, &status, 0);
        if (sys_index == 0x80CD || sys_index == 0x50F)
            chose_print(is_detailed, status, child, regs);
    }
    printf("+++ exited with %llu +++\n", regs.rdi);
    return (regs.rdi);
}

int execution_loop(pid_t child, bool is_detailed)
{
    if (getpgid(child) >= 0)
        return (syscall_loop(child, is_detailed));
    printf("strace: attach: ptrace(PTRACE_SEIZE, %d): No such process\n", \
            child);
    return (84);
}

int execute_binary(char **argv, bool is_detailed)
{
    pid_t child = fork();

    if (child < 0)
        return (84);
    else if (child == 0) {
        ptrace(PTRACE_TRACEME);
        kill(getpid(), SIGSTOP);
        if (execvp(argv[0], argv) == -1)
            return (84);
    } else
        return (execution_loop(child, is_detailed));
}