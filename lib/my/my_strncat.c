/*
** EPITECH PROJECT, 2022
** my_strncat.c
** File description:
** task03 day07
*/

int my_strlen(char const *str);
char *my_strncat(char *dest, const char *src, int nb)
{
    int i;
    int dest_len = my_strlen(dest);
    for (i = 0 ; i < nb && src[i] != '\0' ; i++)
        dest[dest_len + i] = src[i];
    dest[dest_len + i] = '\0';
    return dest;
}
