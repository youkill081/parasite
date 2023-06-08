/*
** EPITECH PROJECT, 2022
** my_revstr.c
** File description:
** task03 day06
*/

int my_strlen(char const *str);
char *my_revstr(char *str)
{
    int len = my_strlen(str);
    int mid = len / 2;
    for (int i = 0; i < mid ; i++) {
        char c = str[i];
        str[i] = str [len - i - 1];
        str[len - i - 1] = c;
    }
    return str;
}
