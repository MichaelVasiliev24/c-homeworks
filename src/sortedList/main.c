#include "../../include/sortedList/menu.h"
#include "../../include/sortedList/sortedList.h"
#include "../../include/sortedList/testSortedList.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char* argv[])
{
    // Проверка флага --test для запуска тестов
    if (argc > 1 && strcmp(argv[1], "--test") == 0) {
        printf("Running tests for sortedList...\n");
        printf("==============================\n");
        runAllTests();
        int result = runTestsWithSummary();
        printf("==============================\n");
        if (result == 0) {
            printf("All tests passed!\n");
        }
        else {
            printf("Some tests failed!\n");
        }
        return result;
    }

    // Обычный режим работы программы
    SortedList* list = createSortedList();
    if (list == NULL) {
        printf("Ошибка создания списка\n");
        return 1;
    }

    int choice;
    bool shouldExit = false;

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