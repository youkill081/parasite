/*
** EPITECH PROJECT, 2022
** my_show_wor_array.c
** File description:
** task03 day08
*/

int my_putstr(char const *str);
void my_putchar(char c);
int my_show_word_array(char * const *tab)
{
    int i = 0;
    while (tab[i] != 0) {
        my_putstr(tab[i]);
        my_putchar('\n');
        i++;
    }
    return 0;
}
