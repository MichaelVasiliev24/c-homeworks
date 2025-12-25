#include "../../include/optimalSorting/mergeSort.h"
#include "../../include/optimalSorting/count.h"
#include <stdio.h>

int main(void)
{
    int numbers[MAX_ELEMENTS];
    int original[MAX_ELEMENTS];
    int count = 0;
    int inputNum;
    int inputChar;

    printf("Введите до %d целых чисел через пробел: ", MAX_ELEMENTS);

    while (count < MAX_ELEMENTS) {
        int result = scanf("%d", &inputNum);

        if (result == EOF) {
            break;
        }

        if (result == 0) {
            inputChar = getchar();
            if (inputChar == '\n' || inputChar == EOF) {
                break;
            }
            while ((inputChar = getchar()) != '\n' && inputChar != EOF && inputChar != ' ') {
                ;
            }
            if (inputChar == '\n' || inputChar == EOF) {
                break;
            }
            continue;
        }

        numbers[count] = inputNum;
        original[count] = inputNum;
        count++;

        inputChar = getchar();
        if (inputChar == '\n' || inputChar == EOF) {
            break;
        }
        ungetc(inputChar, stdin);
    }

    if (count == 0) {
        fprintf(stderr, "Ошибка: нет данных для сортировки\n");
        return 0;
    }

    if (count > MAX_ELEMENTS) {
        fprintf(stderr, "Ошибка: превышено максимальное количество элементов (%d)\n", MAX_ELEMENTS);
        return 0;
    }

    mergeSort(numbers, 0, count - 1);

    int movedCount = countMovedElements(original, numbers, count);

    printf("Количество элементов, изменивших позицию после сортировки: %d\n", movedCount);
}