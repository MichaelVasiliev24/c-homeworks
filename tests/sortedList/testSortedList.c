#include "../../include/sortedList/sortedList.h"
#include "../../include/sortedList/testSortedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool testCreateAndDestroy(void)
{
    SortedList* testList = createSortedList();

    if (testList == NULL) {
        return false;
    }

    if (testList->head != NULL) {
        destroySortedList(testList);
        return false;
    }

    destroySortedList(testList);
    return true;
}

bool testInsertSingle(void)
{
    SortedList* testList = createSortedList();

    insertValue(testList, 5);

    if (testList->head == NULL) {
        destroySortedList(testList);
        return false;
    }

    if (testList->head->value != 5) {
        destroySortedList(testList);
        return false;
    }

    if (testList->head->next != NULL) {
        destroySortedList(testList);
        return false;
    }

    destroySortedList(testList);
    return true;
}

bool testInsertMultipleAscending(void)
{
    SortedList* testList = createSortedList();

    insertValue(testList, 1);
    insertValue(testList, 2);
    insertValue(testList, 3);

    Node* currentNode = testList->head;
    int expectedArray[3] = { 1, 2, 3 };
    int index = 0;

    while (currentNode != NULL && index < 3) {
        if (currentNode->value != expectedArray[index]) {
            destroySortedList(testList);
            return false;
        }
        currentNode = currentNode->next;
        index++;
    }

    bool success = (index == 3 && currentNode == NULL);
    destroySortedList(testList);
    return success;
}

bool testInsertMultipleDescending(void)
{
    SortedList* testList = createSortedList();

    insertValue(testList, 3);
    insertValue(testList, 2);
    insertValue(testList, 1);

    Node* currentNode = testList->head;
    int expectedArray[3] = { 1, 2, 3 };
    int index = 0;

    while (currentNode != NULL && index < 3) {
        if (currentNode->value != expectedArray[index]) {
            destroySortedList(testList);
            return false;
        }
        currentNode = currentNode->next;
        index++;
    }

    bool success = (index == 3 && currentNode == NULL);
    destroySortedList(testList);
    return success;
}

bool testInsertRandomOrder(void)
{
    SortedList* testList = createSortedList();

    insertValue(testList, 4);
    insertValue(testList, 2);
    insertValue(testList, 5);
    insertValue(testList, 1);
    insertValue(testList, 3);

    Node* currentNode = testList->head;
    int expectedArray[5] = { 1, 2, 3, 4, 5 };
    int index = 0;

    while (currentNode != NULL && index < 5) {
        if (currentNode->value != expectedArray[index]) {
            destroySortedList(testList);
            return false;
        }
        currentNode = currentNode->next;
        index++;
    }

    bool success = (index == 5 && currentNode == NULL);
    destroySortedList(testList);
    return success;
}

bool testInsertDuplicates(void)
{
    SortedList* testList = createSortedList();

    insertValue(testList, 1);
    insertValue(testList, 1);
    insertValue(testList, 1);
    insertValue(testList, 2);
    insertValue(testList, 2);

    Node* currentNode = testList->head;
    int expectedArray[5] = { 1, 1, 1, 2, 2 };
    int index = 0;

    while (currentNode != NULL && index < 5) {
        if (currentNode->value != expectedArray[index]) {
            destroySortedList(testList);
            return false;
        }
        currentNode = currentNode->next;
        index++;
    }

    bool success = (index == 5 && currentNode == NULL);
    destroySortedList(testList);
    return success;
}

bool testDeleteExisting(void)
{
    SortedList* testList = createSortedList();

    insertValue(testList, 1);
    insertValue(testList, 2);
    insertValue(testList, 3);

    int resultValue = deleteValue(testList, 2);

    if (!resultValue) {
        destroySortedList(testList);
        return false;
    }

    Node* currentNode = testList->head;
    int expectedArray[2] = { 1, 3 };
    int index = 0;

    while (currentNode != NULL && index < 2) {
        if (currentNode->value != expectedArray[index]) {
            destroySortedList(testList);
            return false;
        }
        currentNode = currentNode->next;
        index++;
    }

    bool success = (index == 2 && currentNode == NULL);
    destroySortedList(testList);
    return success;
}

bool testDeleteNonExisting(void)
{
    SortedList* testList = createSortedList();

    insertValue(testList, 1);
    insertValue(testList, 3);

    int resultValue = deleteValue(testList, 2);

    if (resultValue) {
        destroySortedList(testList);
        return false;
    }

    Node* currentNode = testList->head;
    int expectedArray[2] = { 1, 3 };
    int index = 0;

    while (currentNode != NULL && index < 2) {
        if (currentNode->value != expectedArray[index]) {
            destroySortedList(testList);
            return false;
        }
        currentNode = currentNode->next;
        index++;
    }

    bool success = (index == 2 && currentNode == NULL);
    destroySortedList(testList);
    return success;
}

bool testDeleteHead(void)
{
    SortedList* testList = createSortedList();

    insertValue(testList, 1);
    insertValue(testList, 2);
    insertValue(testList, 3);

    int resultValue = deleteValue(testList, 1);

    if (!resultValue) {
        destroySortedList(testList);
        return false;
    }

    if (testList->head == NULL) {
        destroySortedList(testList);
        return false;
    }

    if (testList->head->value != 2) {
        destroySortedList(testList);
        return false;
    }

    destroySortedList(testList);
    return true;
}

bool testDeleteTail(void)
{
    SortedList* testList = createSortedList();

    insertValue(testList, 1);
    insertValue(testList, 2);
    insertValue(testList, 3);

    int resultValue = deleteValue(testList, 3);

    if (!resultValue) {
        destroySortedList(testList);
        return false;
    }

    Node* currentNode = testList->head;
    while (currentNode != NULL && currentNode->next != NULL) {
        currentNode = currentNode->next;
    }

    if (currentNode == NULL) {
        destroySortedList(testList);
        return false;
    }

    if (currentNode->value != 2) {
        destroySortedList(testList);
        return false;
    }

    destroySortedList(testList);
    return true;
}

bool testDeleteFromEmpty(void)
{
    SortedList* testList = createSortedList();

    int resultValue = deleteValue(testList, 1);

    bool success = (resultValue == 0);
    destroySortedList(testList);
    return success;
}

bool testDeleteAllElements(void)
{
    SortedList* testList = createSortedList();

    insertValue(testList, 1);
    insertValue(testList, 2);
    insertValue(testList, 3);

    deleteValue(testList, 2);
    deleteValue(testList, 1);
    deleteValue(testList, 3);

    bool success = (testList->head == NULL);
    destroySortedList(testList);
    return success;
}

bool testNegativeNumbers(void)
{
    SortedList* testList = createSortedList();

    insertValue(testList, -5);
    insertValue(testList, -1);
    insertValue(testList, -3);
    insertValue(testList, 0);
    insertValue(testList, -2);

    Node* currentNode = testList->head;
    int expectedArray[5] = { -5, -3, -2, -1, 0 };
    int index = 0;

    while (currentNode != NULL && index < 5) {
        if (currentNode->value != expectedArray[index]) {
            destroySortedList(testList);
            return false;
        }
        currentNode = currentNode->next;
        index++;
    }

    bool success = (index == 5 && currentNode == NULL);
    destroySortedList(testList);
    return success;
}

bool testPrintEmpty(void)
{
    SortedList* testList = createSortedList();

    printList(testList);

    destroySortedList(testList);
    return true;
}

void runAllTests(void)
{
    printf("Запуск всех тестов для сортированного списка\n\n");

    struct TestCase testCases[] = {
        { testCreateAndDestroy, "Создание и удаление списка" },
        { testInsertSingle, "Добавление одного элемента" },
        { testInsertMultipleAscending, "Добавление в возрастающем порядке" },
        { testInsertMultipleDescending, "Добавление в убывающем порядке" },
        { testInsertRandomOrder, "Добавление в случайном порядке" },
        { testInsertDuplicates, "Добавление дубликатов" },
        { testDeleteExisting, "Удаление существующего элемента" },
        { testDeleteNonExisting, "Удаление несуществующего элемента" },
        { testDeleteHead, "Удаление головного элемента" },
        { testDeleteTail, "Удаление последнего элемента" },
        { testDeleteFromEmpty, "Удаление из пустого списка" },
        { testDeleteAllElements, "Удаление всех элементов" },
        { testNegativeNumbers, "Работа с отрицательными числами" },
        { testPrintEmpty, "Печать пустого списка" }
    };

    int totalTests = sizeof(testCases) / sizeof(testCases[0]);
    int passedTests = 0;

    for (int i = 0; i < totalTests; i++) {
        printf("Тест %d: %s - ", i + 1, testCases[i].name);

        bool result = testCases[i].func();
        if (result) {
            printf("ПРОЙДЕН\n");
            passedTests++;
        }
        else {
            printf("НЕ ПРОЙДЕН\n");
        }
    }

    printf("\nРезультаты: %d/%d тестов пройдено\n", passedTests, totalTests);
    printf("\nВсе тесты завершены\n");
}

int runTestsWithSummary(void)
{
    bool results[] = {
        testCreateAndDestroy(),
        testInsertSingle(),
        testInsertMultipleAscending(),
        testInsertMultipleDescending(),
        testInsertRandomOrder(),
        testInsertDuplicates(),
        testDeleteExisting(),
        testDeleteNonExisting(),
        testDeleteHead(),
        testDeleteTail(),
        testDeleteFromEmpty(),
        testDeleteAllElements(),
        testNegativeNumbers(),
        testPrintEmpty()
    };

    int totalTests = sizeof(results) / sizeof(results[0]);
    int passedTests = 0;

    for (int i = 0; i < totalTests; i++) {
        if (results[i]) {
            passedTests++;
        }
    }

    if (passedTests == totalTests) {
        return 0;
    }

    return 1;
}