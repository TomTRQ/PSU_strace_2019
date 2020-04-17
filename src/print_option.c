/*
** EPITECH PROJECT, 2020
** print_option.c
** File description:
** print_option.c
*/

#include "strace.h"
#include "sys_call_name.h"

void print_with_option(int status, pid_t child, struct user_regs_struct regs)
{
    int sys_number = regs.rax;
    int retval = 0;

    printf("%s(", g_entries[sys_number].name);
    print_detailed_syscall_parameters(sys_number, regs, child);
    printf(") = ");
    if (!end_syscall(status)) {
        printf("?\n");
        return;
    }
    retval = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * RAX, 0);
    print_return_register(sys_number, child, retval);
}

void print_without_option(int status, pid_t child, struct user_regs_struct regs)
{
    int sys_number = regs.rax;
    int retval = 0;

    printf("%s(", g_entries[sys_number].name);
    print_syscall_parameters(sys_number, regs);
    printf(") = ");
    if (!end_syscall(status)) {
        printf("?\n");
        return;
    }
    retval = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * RAX);
    printf("0x%x\n", retval);
}
