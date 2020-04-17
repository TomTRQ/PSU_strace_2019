/*
** EPITECH PROJECT, 2020
** print_arguments.c
** File description:
** strace
*/

#include "strace.h"
#include "sys_call_name.h"

char *read_string(pid_t child, unsigned long addr)
{
    int i = 4096;
    char *str = malloc(i);
    int read = 0;
    unsigned long tmp = 0;

    while (1) {
        tmp = ptrace(PTRACE_PEEKDATA, child, (addr + read));
        if (errno != 0) {
            str[read] = '\0';
            return (str);
        }
        memcpy((str + read), &tmp, sizeof(tmp));
        if (memchr(&tmp, 0, sizeof(tmp)) != NULL)
            return (str);
        read += sizeof(tmp);
    }
}

void print_register(int sys_number, int index, pid_t child, \
                    unsigned long long _register)
{
    char *str = NULL;

    if (g_entries[sys_number].args_value[index] == STR) {
        str = read_string(child, _register);
        choose_print(str);
    } else if (g_entries[sys_number].args_value[index] == INT)
        printf("%lld", _register);
    else
        printf("0x%llx", _register);
}

void print_detailed_syscall_parameters(int sys_number, \
                                    struct user_regs_struct regs, pid_t child)
{
    if (g_entries[sys_number].nb_args >= 1)
        print_register(sys_number, 0, child, regs.rdi);
    if (g_entries[sys_number].nb_args >= 2) {
        printf(", ");
        print_register(sys_number, 1, child, regs.rsi);
    } if (g_entries[sys_number].nb_args >= 3) {
        printf(", ");
        print_register(sys_number, 2, child, regs.rdx);
    }
    if (g_entries[sys_number].nb_args >= 4) {
        printf(", ");
        print_register(sys_number, 3, child, regs.r10);
    }
    if (g_entries[sys_number].nb_args >= 5) {
        printf(", ");
        print_register(sys_number, 4, child, regs.r8);
    }
    if (g_entries[sys_number].nb_args >= 6) {
        printf(", ");
        print_register(sys_number, 5, child, regs.r9);
    }
}

void print_syscall_parameters(int sys_number, struct user_regs_struct regs)
{
    if (g_entries[sys_number].nb_args >= 1)
        printf("0x%llx", regs.rdi);
    if (g_entries[sys_number].nb_args >= 2)
        printf(", 0x%llx", regs.rsi);
    if (g_entries[sys_number].nb_args >= 3)
        printf(", 0x%llx", regs.rdx);
    if (g_entries[sys_number].nb_args >= 4)
        printf(", 0x%llx", regs.r10);
    if (g_entries[sys_number].nb_args >= 5)
        printf(", 0x%llx", regs.r8);
    if (g_entries[sys_number].nb_args >= 6)
        printf(", 0x%llx", regs.r9);
}

void print_return_register(int sys_number, pid_t child, \
                            unsigned long long _register)
{
    char *str = NULL;

    if (g_entries[sys_number].retval == STR) {
        str = read_string(child, _register);
        choose_print_back(str);
    } else if (g_entries[sys_number].retval == INT)
        printf("%lld\n", _register);
    else
        printf("0x%llx\n", _register);
}
