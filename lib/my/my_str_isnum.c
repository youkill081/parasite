/*
** EPITECH PROJECT, 2022
** my_str_isalpha.c
** File description:
** task12 day06
*/

int my_str_isnum(char const *str)
{
    int i = 0;
    while (str[i] != '\0') {
        if (!(str[i] >= 48 && str[i] <= 57)) {
            return 0;
        }
        i++;
    }
    return 1;
}
