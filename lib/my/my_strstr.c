/*
** EPITECH PROJECT, 2022
** my_strstr.c
** File description:
** task05 day06
*/

#include <stddef.h>

int my_strlen(char const *str);
char *my_strncpy(char *dest, char const *src, int n);
int check(char *str, char const *to_find, int beg_i, int tf_size);
char *my_revstr(char *str);
int egal(char a, char b);

char *my_strstr(char *str, char const *to_find)
{
    char fist_car = str[0];
    int to_find_len = my_strlen(to_find);
    int str_len = my_strlen(str);
    int i = 0;
    if (my_strlen(to_find) == 0) {
        return str;
    }
    while (i < str_len) {
        if (str[i] == to_find[0] && check(str, to_find, i, to_find_len)) {
            return &str[i];
        }
        i++;
    }
    return NULL;
}

int check(char *str, char const *to_find, int bi, int tf_size)
{
    int str_len = my_strlen(str);
    int i = 0;
    if (bi + tf_size > str_len)
        return 0;
    while (i < tf_size) {
        if (to_find[i] != str[i + bi]) {
            return 0;
        }
        i++;
    }
    return 1;
}
