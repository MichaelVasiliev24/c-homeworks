#include "../../include/sortedList/menu.h"
#include <stdio.h>

void clearInputBuffer(void)
{
    while (getchar() != '\n') {
        ;
    }
}

int readInt(const char* prompt, int* value)
{
    printf("%s", prompt);
    if (scanf("%d", value) != 1) {
        printf("Ошибка ввода\n");
        clearInputBuffer();
        return 0;
    }
    return 1;
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

void handleInsert(SortedList* list)
{
    int value;
    if (readInt("Введите значение для добавления: ", &value)) {
        insertValue(list, value);
        printf("Значение %d добавлено\n", value);
    }
}

void handleDelete(SortedList* list)
{
    int value;
    if (readInt("Введите значение для удаления: ", &value)) {
        if (deleteValue(list, value)) {
            printf("Значение %d удалено\n", value);
        }
        else {
            printf("Значение %d не найдено\n", value);
        }
    }
}

int processChoice(int choice, SortedList* list)
{
    switch (choice) {
        case 0:
            printf("Выход...\n");
            return 1;

        case 1:
            handleInsert(list);
            break;

        case 2:
            handleDelete(list);
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
