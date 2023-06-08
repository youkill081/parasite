/*
** EPITECH PROJECT, 2022
** function3
** File description:
** n
*/

char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int nb);
int my_showstr(char const *str)
{
    return 0;
}

int my_compute_power_rec(int nb, int p)
{
    if (p == 0)
        return 1;
    if (p < 0)
        return 0;
    return nb * my_compute_power_rec (nb, p - 1);
}
