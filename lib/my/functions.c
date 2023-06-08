/*
** EPITECH PROJECT, 2022
** functions.c
** File description:
** functions
*/

#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

int my_isneg(int c)
{
    if (c < 0)
        return 1;
    return 0;
}

void my_swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

int my_putstr(char const *str)
{
    int i = 0;
    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
}
