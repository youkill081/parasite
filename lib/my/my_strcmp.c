/*
** EPITECH PROJECT, 2022
** my_strcmp.c
** File description:
** task06 day06
*/

int add_ascii(char const *str);
int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;
    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0') {
        i++;
    }
    return (s1[i] - s2[i]);
}
