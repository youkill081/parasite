/*
** EPITECH PROJECT, 2022
** my_is_prime.c
** File description:
** task06 day06
*/
int my_compute_power_it(int nb, int p);
int my_compute_square_root2(int nb);
int divise(int a, int b);

int my_is_prime(int nb)
{
    if (nb <= 1)
        return 0;
    int max = nb / 2 + 1;
    for (int i = 2; i < max; i++) {
        if (nb % i == 0)
            return 0;
    }
    return 1;
}
