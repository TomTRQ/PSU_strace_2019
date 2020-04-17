/*
** EPITECH PROJECT, 2020
** alloc.c
** File description:
** alloc.c
*/

#include "strace.h"

void check_error(char **argv, int x, flags_s *flags)
{
    if (argv[x + 1] != NULL && check_digit(argv[x + 1]))
        flags->p_value = atoi(argv[x + 1]);
    else
        flags->error = true;
}

void choose_print_back(char *str)
{
    if (str == NULL)
        printf("NULL");
    else
        printf("\"%s\"\n", str);
}

void choose_print(char *str)
{
    if (str == NULL)
        printf("NULL");
    else
        printf("\"%s\"", str);
}
