/*
** EPITECH PROJECT, 2022
** test
** File description:
** tes
*/

#include <stdlib.h>
#include <stdio.h>

void my_putchar(char c);

int first_letter_from_i(int i, char const *str);
int len_word_from_i(int i, char const *str);
int number_of_word(char const *str);
char *my_strdup(char const *src);
char **my_str_to_word_array(char const *str)
{
    int nbr_word = number_of_word(str);
    char **rec = malloc(sizeof(char *) * (nbr_word + 1));
    int count, i = first_letter_from_i(0, str);
    char *word;
    for (int y = 0; y < nbr_word; y++) {
        int len_word = len_word_from_i(i, str);
        word = malloc(sizeof(char) * (len_word + 1));
        int index_max = i + len_word;
        count = 0;
        for (i = i; i < index_max; i++) {
            word[count] = str[i];
            count++;
        }
        word[len_word] = '\0';
        rec[y] = my_strdup(word);
        i = first_letter_from_i(i, str);
        free(word);
    }
    rec[nbr_word] = NULL;
    return rec;
}

int is_alphanumerique(char c)
{
    if (c >= 33)
        return 1;
    return 0;
}

int first_letter_from_i(int i, char const *str)
{
    while (str[i] != '\0' && !is_alphanumerique(str[i]))
        i++;
    return i;
}

int len_word_from_i(int i, char const *str)
{
    int len = 0;
    while (str[i] != '\0' && is_alphanumerique(str[i])) {
        len++;
        i++;
    }
    return len;
}

int number_of_word(char const *str)
{
    int i = 0;
    int number_word = 0;
    int last_alpha = 0;
    while (str[i] != '\0') {
        if (is_alphanumerique(str[i]) && !last_alpha) {
            number_word++;
            i++;
            last_alpha = 1;
            continue;
        }
        if (!is_alphanumerique(str[i])){
            i++;
            last_alpha = 0;
            continue;
        }
        i++;
    }
    return number_word;
}
