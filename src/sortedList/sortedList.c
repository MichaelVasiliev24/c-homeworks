#include "sortedList.h"
#include <stdio.h>
#include <stdlib.h>

SortedList* createSortedList(void)
{
    SortedList* list = (SortedList*)malloc(sizeof(SortedList));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    return list;
}

void destroySortedList(SortedList* list)
{
    if (list == NULL) {
        return;
    }

    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void insertValue(SortedList* list, int value)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти\n");
        return;
    }
    newNode->value = value;
    newNode->next = NULL;

    if (list->head == NULL || value < list->head->value) {
        newNode->next = list->head;
        list->head = newNode;
        return;
    }

    Node* current = list->head;
    while (current->next != NULL && current->next->value < value) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

int deleteValue(SortedList* list, int value)
{
    if (list->head == NULL) {
        return 0;
    }

    if (list->head->value == value) {
        Node* toDelete = list->head;
        list->head = list->head->next;
        free(toDelete);
        return 1;
    }

    Node* current = list->head;
    while (current->next != NULL && current->next->value != value) {
        current = current->next;
    }

    if (current->next == NULL) {
        return 0;
    }

    Node* toDelete = current->next;
    current->next = toDelete->next;
    free(toDelete);
    return 1;
}

void printList(const SortedList* list)
{
    if (list->head == NULL) {
        printf("Список пуст\n");
        return;
    }

    Node* current = list->head;
    printf("Текущий список: ");
    while (current != NULL) {
        printf("%d", current->value);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}