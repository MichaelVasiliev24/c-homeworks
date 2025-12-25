#include "menu.h"
#include "sortedList.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    SortedList* list = createSortedList();
    if (list == NULL) {
        printf("Ошибка создания списка\n");
        return 1;
    }

    int choice;
    int shouldExit = 0;

    do {
        printMenu();

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода\n");
            clearInputBuffer();
            continue;
        }

        shouldExit = processChoice(choice, list);

    } while (!shouldExit);

    destroySortedList(list);
    return 0;
}