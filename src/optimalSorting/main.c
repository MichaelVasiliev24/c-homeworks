#include "mergeSort.h"
#include "count.h"
#include <stdio.h>

int main(void)
{
    int numbers[MAX_ELEMENTS]; // Массив для сортировки
    int original[MAX_ELEMENTS]; // Массив для сохранения исходного порядка
    int count = 0; // Количество введенных чисел
    int inputNum; // Переменная для чтения очередного числа
    char separator; // Символ, следующий за числом (разделитель)

    printf("Введите до %d целых чисел через пробел: ", MAX_ELEMENTS);

    // Основной цикл чтения чисел
    while (count < MAX_ELEMENTS) {
        // Используем scanf для чтения числа и следующего символа за ним
        int result = scanf("%d%c", &inputNum, &separator);

        // Проверка на конец файла
        if (result == EOF) {
            break;
        }

        // Если не удалось прочитать число (некорректный ввод)
        if (result == 0) {
            fprintf(stderr, "Ошибка: некорректный ввод\n");
            return 1;
        }

        // Сохраняем число в оба массива
        numbers[count] = inputNum;
        original[count] = inputNum;
        count++;

        // Если следующий символ - перевод строки, ввод завершен
        if (separator == '\n') {
            break;
        }

        /*Если следующий символ не пробел - нарушен формат ввода
        Числа должны разделяться ровно одним пробелом */
        if (separator != ' ') {
            fprintf(stderr, "Ошибка: числа должны разделяться пробелами\n");
            return 1;
        }

        // Если separator == ' ', цикл продолжается для чтения следующего числа
    }

    // Проверка, что хотя бы одно число было введено
    if (count == 0) {
        fprintf(stderr, "Ошибка: нет данных для сортировки\n");
        return 1;
    }

    // Вызов функции сортировки
    mergeSort(numbers, 0, count - 1);

    // Подсчет элементов, изменивших позицию
    int movedCount = countMovedElements(original, numbers, count);

    // Вывод результата
    printf("Количество элементов, изменивших позицию после сортировки: %d\n", movedCount);

    return 0;
}