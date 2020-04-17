/*
** EPITECH PROJECT, 2020
** parse_arguments_test.c
** File description:
** parse_arguments_test.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "strace.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(parseArguments, check_no_args, .init=redirect_all_std)
{
    char *argv[1];

    argv[0] = "./strace";
    cr_assert(parse_and_execute(1, argv) == 84);
}

Test(parseArguments, check_help, .init=redirect_all_std)
{
    char *argv[2];

    argv[0] = "./strace";
    argv[1] = "--help";
    cr_assert(parse_and_execute(2, argv) == 0);
}

Test(parseArguments, check_bad_args, .init=redirect_all_std)
{
    char *argv[2];

    argv[0] = "./strace";
    argv[1] = "-r";
    cr_assert(parse_and_execute(2, argv) == 84);
}

Test(parseArguments, check_good_args, .init=redirect_all_std)
{
    char *argv[3];

    argv[0] = "./strace";
    argv[1] = "-s";
    argv[2] = "./binary";
    cr_assert(parse_and_execute(3, argv) == 87);
}