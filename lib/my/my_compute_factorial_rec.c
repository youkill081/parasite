/*
** EPITECH PROJECT, 2022
** my_compute_factorial_rec.c
** File description:
** task02 day05
*/

int my_compute_factorial_rec(int nb)
{
    if (nb < 0 || nb >= 13)
        return 0;
    if (nb == 0)
        return 1;
    return nb * my_compute_factorial_rec(nb - 1);
}
