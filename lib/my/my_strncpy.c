/*
** EPITECH PROJECT, 2022
** my_strncpy.c
** File description:
** task02 day06
*/

int my_strlen(char const *str);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n)
{
    int str_len = my_strlen(src);
    int i = 0;
    if (n > str_len) {
        return my_strcpy(dest, src);
    }
    while (i < n) {
        dest[i] = src[i];
        i++;
    }
    return dest;
}
