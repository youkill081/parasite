/*
** EPITECH PROJECT, 2022
** lib
** File description:
** convert str to int
*/

#include "my.h"

int my_str_to_int(char *str)
{
    int fin = 0;
    int i = 0;
    int is_neg = 0;
    if (str[0] == '-') {
        is_neg = 1;
        i = 1;
    }
    while (str[i] != '\0') {
        fin = fin * 10;
        fin = fin + (str[i] - 48);
        i++;
    }
    if (is_neg)
        return fin * -1;
    return fin;
}
