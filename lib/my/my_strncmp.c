/*
** EPITECH PROJECT, 2022
** my_strncmp.c
** File description:
** task07 day06
*/

int add_asciin(char const *str, int n);
int my_strncmp(char const *s1, char const *s2, int n)
{
    int add_s1 = add_asciin(s1, n);
    int add_s2 = add_asciin(s2, n);
    return (add_s1 - add_s2);
}

int add_asciin(char const *str, int n)
{
    int res = 0;
    int i = 0;
    while (str[i] != '\0' && i < n) {
        res = res + (int) str[i];
        i++;
    }
    return res;
}
