/*
** EPITECH PROJECT, 2022
** my_strcapitalize.c
** File description:
** task10 day06
*/

int is_digit_or_letter(char c);
char *first_car(char *str, int i, int *cap);
char  *other_car(char *str, int i, int *cap_next);
char *other_car(char *str, int i, int *cap_next);

char *my_strcapitalize(char *str)
{
    int i = 0;
    int capitalize_next = 1;
    while (str[i] != '\0') {
        if (capitalize_next) {
            first_car(str, i, &capitalize_next);
            i++;
            continue;
        }
        other_car(str, i, &capitalize_next);
        i++;
    }
    return str;
}

int is_digit_or_letter(char c)
{
    if (c >= 48 && c <= 57 || c >= 97 && c <= 122)
        return 1;
    return 0;
}

char *first_car(char *str, int i, int *cap)
{
    if (str[i] >= 97 && str[i] <= 122) {
        str[i] = str[i] - 32;
        *cap = 0;
    }
    if (str[i] >= 48 && str[i] <= 57)
        *cap = 0;
    return str;
}

char *other_car(char *str, int i, int *cap_next)
{
    if (str[i] >= 65 && str[i] <= 90) {
        str[i] = str[i] + 32;
        return str;
    }
    if (str[i] >= 48 && str[i] <= 57) {
        return str;
    }
    if (str[i] >= 97 && str[i] <= 122) {
        return str;
    }
    *cap_next = 1;
    return str;
}
