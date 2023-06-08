/*
** EPITECH PROJECT, 2022
** test
** File description:
** tes
*/

#include <stdlib.h>
#include <stdio.h>

void my_putchar(char c);

int first_letter_from_i2(int i, char const *str, char const *delim);
int len_word_from_i2(int i, char const *str, char const *delim);
int number_of_word2(char const *str, char const *delim);
char *my_strdup(char const *src);
char **my_str_to_array(char const *str, char const *delim)
{
    int nbr_word = number_of_word2(str, delim);
    char **rec = malloc(sizeof(char *) * (nbr_word + 1));
    int count, i = first_letter_from_i2(0, str, delim);
    char *word;
    for (int y = 0; y < nbr_word; y++) {
        int len_word = len_word_from_i2(i, str, delim);
        word = malloc(sizeof(char) * (len_word + 1));
        int index_max = i + len_word;
        count = 0;
        for (i = i; i < index_max; i++) {
            word[count] = str[i];
            count++;
        }
        word[len_word] = '\0';
        rec[y] = my_strdup(word);
        i = first_letter_from_i2(i, str, delim);
        free(word);
    }
    rec[nbr_word] = NULL;
    return rec;
}

int is_in_str(char c, const char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            return 0;
    }
    return 1;
}

int first_letter_from_i2(int i, char const *str, char const *delim)
{
    while (str[i] != '\0' && !is_in_str(str[i], delim))
        i++;
    return i;
}

int len_word_from_i2(int i, char const *str, char const *delim)
{
    int len = 0;
    while (str[i] != '\0' && is_in_str(str[i], delim)) {
        len++;
        i++;
    }
    return len;
}

int number_of_word2(char const *str, char const *delim)
{
    int i = 0;
    int number_word = 0;
    int last_alpha = 0;
    while (str[i] != '\0') {
        if (is_in_str(str[i], delim) && !last_alpha) {
            number_word++;
            i++;
            last_alpha = 1;
            continue;
        }
        if (!is_in_str(str[i], delim)){
            i++;
            last_alpha = 0;
            continue;
        }
        i++;
    }
    return number_word;
}
