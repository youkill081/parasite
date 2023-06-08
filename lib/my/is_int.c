/*
** EPITECH PROJECT, 2022
** is_int
** File description:
** uwu
*/
int is_int(char* str, int i)
{
    if (str[i] >= '0' && str[i] <= '9') {
        return 1;
    }else {
        return 0;
    }
}
