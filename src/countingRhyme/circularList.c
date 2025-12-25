#include "../../include/countingRhyme/circularList.h"
#include <stdio.h>
#include <stdlib.h>

Node* createNode(int value)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

Node* createCircularList(int n)
{
    if (n <= 0) {
        return NULL;
    }

    Node* head = createNode(1);
    if (head == NULL) {
        printf("Ошибка: Не удалось выделить память для узла\n");
        return NULL;
    }

    Node* current = head;

    for (int i = 2; i <= n; i++) {
        current->next = createNode(i);
        if (current->next == NULL) {
            printf("Ошибка: Не удалось выделить память для узла %d.\n", i);
            freeCircularList(head);
            return NULL;
        }
        current = current->next;
    }

    current->next = head;
    return head;
}

void freeCircularList(Node* head)
{
    if (head == NULL) {
        return;
    }

    Node* current = head;
    Node* temp;

    do {
        temp = current->next;
        free(current);
        current = temp;
    } while (current != head && current != NULL);
}