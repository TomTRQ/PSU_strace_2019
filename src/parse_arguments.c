/*
** EPITECH PROJECT, 2020
** parse_arguments.c
** File description:
** parse_arguments.c
*/

#include "strace.h"

void parse_args(char **argv, flags_s *flags, int x)
{
    if (strlen(argv[x]) >= 2 && strncmp(argv[x], "-p", 2) == 0) {
        flags->p = true;
        check_error(argv, x, flags);
    }
    else if ((strlen(argv[x]) >= 2 && strncmp(argv[x], "-s", 2) == 0) ||
            (flags->p_value != 0 && flags->index == 0))
        parse_args_conditions(argv, flags, x);
}

void init_struct(flags_s *flags)
{
    flags->p = false;
    flags->p_value = 0;
    flags->s = false;
    flags->error = false;
    flags->index = 0;
}

int good_call_second(flags_s *flags, char **argv)
{
    if (flags->s == true && flags->p == true)
        return (execution_loop((pid_t)flags->p_value, true));
    else if ((flags->p == true) || (flags->s == true))
        return (good_call_third(flags, argv));
    return (0);
}

int good_call(flags_s *flags, char **argv)
{
    if (flags->error == true)
        return (print_error());
    else if (flags->p == false && flags->s == false)
        if (argv[1] == NULL)
            return (print_error());
        else
            return (execute_binary(argv + 1, false));
    else
        return (good_call_second(flags, argv));
}

int parse_and_execute(const int argc, char **argv)
{
    int opt = 0;
    int ret_value = 0;
    flags_s *flags = malloc(sizeof(flags_s));
    char *str = 0;

    init_struct(flags);
    if (check_help(argc, argv))
        return (0);
    for (int x = 1; x < argc; x++)
        parse_args(argv, flags, x);
    return (good_call(flags, argv));
}