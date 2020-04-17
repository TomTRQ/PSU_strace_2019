/*
** EPITECH PROJECT, 2020
** main file
** File description:
** strace
*/

#include "strace.h"

int main(int argc, char **argv, char **env)
{
    if (argc < 2)
        return (84);
    return (parse_and_execute(argc, argv));
}