/*
** EPITECH PROJECT, 2022
** my_sort_int_array.c
** File description:
** task 06 day 03
*/

void mins(int *min, int *indexmin, int *array, int *k);
void swap(int *array, int index1, int index2);
void my_sort_int_array(int *array, int size)
{
    int min_index = 0;
    int min = 0;
    int index_min;
    for (int i = min_index; i < size; i++) {

        min = array[i];
        index_min = i;
        for (int k = i + 1; k < size; k++) {
            mins(&min, &index_min, array, &k);
        }
        min_index++;
        swap(array, i, index_min);
    }
}

void mins(int *min, int *index_min, int *array, int *k)
{
    if (*min > array[*k]) {
        *min = array[*k];
        *index_min = *k;
    }
}

void swap(int *array, int index1, int index2)
{
    int c = array[index1];
    array[index1] = array[index2];
    array[index2] = c;
}
