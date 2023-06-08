/*
** EPITECH PROJECT, 2022
** my_find_prime_sup.c
** File description:
** task07 day05
*/

int my_is_prime(int nb);
int my_find_prime_sup(int nb)
{
    if (nb <= 1)
        return 2;
    int prime_sup = nb;
    while (!my_is_prime(prime_sup)) {
        prime_sup++;
    }
    return prime_sup;
}
