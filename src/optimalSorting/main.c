#include "mergeSort.h"
#include "count.h"
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
            // Некорректный ввод - завершаем с ошибкой
            fprintf(stderr, "Ошибка: некорректный ввод\n");
            return 1;
        }

        numbers[count] = inputNum;
        original[count] = inputNum;
        count++;

        // Проверяем следующий символ
        inputChar = getchar();
        if (inputChar == '\n' || inputChar == EOF) {
            break;
        }

        // Если следующий символ не пробел и не конец - ошибка
        if (inputChar != ' ') {
            fprintf(stderr, "Ошибка: числа должны разделяться пробелами\n");
            return 1;
        }

        // Пропускаем возможные дополнительные пробелы
        while ((inputChar = getchar()) == ' ') {
            ;
        }

        if (inputChar == '\n' || inputChar == EOF) {
            break;
        }

        // Возвращаем символ обратно в поток
        ungetc(inputChar, stdin);
    }

    if (count == 0) {
        fprintf(stderr, "Ошибка: нет данных для сортировки\n");
        return 1;
    }

    mergeSort(numbers, 0, count - 1);

    int movedCount = countMovedElements(original, numbers, count);

    printf("Количество элементов, изменивших позицию после сортировки: %d\n", movedCount);

    return 0;
}