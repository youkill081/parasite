/*
** EPITECH PROJECT, 2022
** find the char in a array
** File description:
** uwu
*/
#include <stdio.h>

int find_char (char* str, char c)
{
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == c){
            i++;
            return 1;
        }else {
            i++;
        }
    }
    return 0;
}
