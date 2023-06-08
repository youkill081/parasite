/*
** EPITECH PROJECT, 2022
** my_getnbr.c
** File description:
** task05 day04
*/

void my_putchar(char c);
int is_digits(char c);
char get_last_char(int i, char const *str);
int my_strlen(char const *str);
int index_fist_digit(char const *str);

int my_getnbr(char const *str)
{
    int i = index_fist_digit(str);
    char last_char = get_last_char(i, str);
    double fin = str[i] - 48;
    while (is_digits(str[i + 1])) {
        i++;
        fin = fin * 10 + (str[i] - 48) ;
    }
    if (last_char == '-' && fin <= 2147483648) {
        return fin * -1;
    }
    if (fin <= 2147483647) {
        return fin;
    }
    return 0;
}

int is_digits(char c)
{
    if (c >= 48 && c <= 57) {
        return 1;
    } else {
        return 0;
    }
}

int index_fist_digit(char const *str)
{
    int i = 0;
    while (!is_digits(str[i])) {
        i++;
    }
    return i;
}

char get_last_char(int i, char const *str)
{
    if (i == 0) {
        return ' ';
    }
    return str[i - 1];
}
