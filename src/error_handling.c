/*
** EPITECH PROJECT, 2020
** error_handling.c
** File description:
** error_handling.c
*/

#include "strace.h"

int good_call_third(flags_s *flags, char **argv)
{
    if (flags->p == true)
        return (execution_loop((pid_t)flags->p_value, false));
    else if (flags->s == true) {
        if (argv[2] == NULL)
            return (print_error());
        else
            return (execute_binary(argv + 2, true));
    }
    return (0);
}

void parse_args_conditions(char **argv, flags_s *flags, int x)
{
    if (strlen(argv[x]) >= 2 && strncmp(argv[x], "-s", 2) == 0)
        flags->s = true;
    else if (flags->p_value != 0 && flags->index == 0) {
        if (strncmp(argv[x - 1], "-p", 2) != 0)
            flags->index = x;
    }
}

bool check_help(int argc, char **argv)
{
    if ((argc == 2 && !strcmp(argv[1], "--help"))) {
        printf("USAGE: ./strace [-s] [-p <pid>|<command>]\n");
        return (true);
    }
    return (false);
}

bool check_digit(char *str)
{
    for (size_t i = 0; i < strlen(str); i++)
        if (isdigit(str[i]) == 0)
            return (false);
    return (true);
}

int print_error(void)
{
    printf("USAGE: ./strace [-s] [-p <pid>|<command>]\n");
    return (84);
}