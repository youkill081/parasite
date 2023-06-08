/*
** EPITECH PROJECT, 2022
** my_put_nbr.c
** File description:
** task07 day03
*/

void my_putchar(char c);
void my_put_nbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = nb * -1;
    }
    int nbr = nb % 10;
    int suivant = nb / 10;
    if (suivant >= 1) {
        my_put_nbr(suivant);
    }
    my_putchar(nbr + 48);
}

int my_put_long(long nb, int len)
{
    if (nb < 0) {
        my_putchar('-');
        nb = nb * -1;
    }
    int nbr = nb % 10;
    int suivant = nb / 10;
    if (suivant >= 1) {
        len = my_put_long(suivant, len + 1);
    }
    my_putchar(nbr + 48);
    return len;
}
