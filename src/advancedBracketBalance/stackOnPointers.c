#include "../../include/advancedBracketBalance/stackOnPointers.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void initializeStack(Stack* ptr)
{
    ptr->head = NULL;
    ptr->len = 0;
}

int isStackEmpty(Stack* ptr)
{
    return ptr->head == NULL;
}

void push(Stack* ptr, char value)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = value;
        newNode->previous = ptr->head;
        ptr->head = newNode;
        ptr->len++;
    }
    else {
        printf("Ошибка выделения памяти для нового узла стека\n");
        return;
    }
}

char pop(Stack* ptr)
{
    // Проверяем, что стек не пуст
    assert(!isStackEmpty(ptr) && "Попытка извлечения из пустого стека");

    Node* tempNode = ptr->head;
    char returnData = tempNode->data;
    ptr->head = tempNode->previous;
    free(tempNode);
    ptr->len--;
    return returnData;
}

char peek(Stack* ptr)
{
    // Проверяем, что стек не пуст
    assert(!isStackEmpty(ptr) && "Попытка просмотра вершины пустого стека");

    return ptr->head->data;
}

void deleteStack(Stack* ptr)
{
    while (ptr->head != NULL) {
        Node* tempNode = ptr->head;
        ptr->head = tempNode->previous;
        free(tempNode);
        ptr->len--;
    }
}