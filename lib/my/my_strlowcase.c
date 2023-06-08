/*
** EPITECH PROJECT, 2022
** my_strlowcase.c
** File description:
** task09 day06
*/

char *my_strlowcase(char *str)
{
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= 65 && str[i] <= 90) {
            str[i] = str[i] + 32;
        }
        i++;
    }
    return str;
}
