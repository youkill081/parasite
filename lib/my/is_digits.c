/*
** EPITECH PROJECT, 2022
** lib
** File description:
** is digit
*/

int is_digit(char *str)
{
    int i = 0;
    while (str[i] != '\0') {
        if (!(str[i] >= 48 && str[i] <= 57) && !(i == 0 && str[i] == '-'))
            return 0;
        i++;
    }
    return 1;
}

int is_digit_float(char *str)
{
    int i = 0;
    int number_point = 0;
    while (str[i] != '\0') {
        if (str[i] == '.' && number_point < 1 && i != 0 && str[i + 1] != '\0') {
            number_point++;
            i++;
            continue;
        }
        if (!(str[i] >= 48 && str[i] <= 57) && !(i == 0 && str[i] == '-'))
            return 0;
        i++;
    }
    return 1;
}
