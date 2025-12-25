#include "menu.h"
#include "sortedList.h"
#include <stdio.h>

void clearInputBuffer(void)
{
    while (getchar() != '\n') {
        ;
    }
}

void printMenu(void)
{
    printf("\nМеню:\n");
    printf("0 - выйти\n");
    printf("1 - добавить значение в сортированный список\n");
    printf("2 - удалить значение из списка\n");
    printf("3 - распечатать список\n");
    printf("Выберите операцию: ");
}

int processChoice(int choice, SortedList* list)
{
    int value;

    switch (choice) {
        case 0:
            printf("Выход...\n");
            return 1;

        case 1:
            printf("Введите значение для добавления: ");
            if (scanf("%d", &value) == 1) {
                insertValue(list, value);
                printf("Значение %d добавлено\n", value);
            }
            else {
                printf("Ошибка ввода\n");
                clearInputBuffer();
            }
            break;

        case 2:
            printf("Введите значение для удаления: ");
            if (scanf("%d", &value) == 1) {
                if (deleteValue(list, value)) {
                    printf("Значение %d удалено\n", value);
                }
                else {
                    printf("Значение %d не найдено\n", value);
                }
            }
            else {
                printf("Ошибка ввода\n");
                clearInputBuffer();
            }
            break;

        case 3:
            printList(list);
            break;

        default:
            printf("Операции с таким кодом нет. Попробуйте снова\n");
            break;
    }
    return 0;
}