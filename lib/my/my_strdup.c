/*
** EPITECH PROJECT, 2022
** my_strdup.c
** File description:
** task01 day08
*/

#include <stdlib.h>

int my_strlen(char const *str);
char *my_strdup(char const *src)
{
    char *str;
    int i = 0;
    str = malloc(sizeof(char) * (my_strlen(src)));
    while (src[i] != '\0') {
        str[i] = src[i];
        i++;
    }
    str[i] = '\0';
    return str;
}
