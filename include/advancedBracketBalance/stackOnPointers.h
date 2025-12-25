#pragma once
#include <stddef.h>

typedef struct Node {
    char data;
    struct Node* previous;
} Node;

typedef struct {
    Node* head;
    size_t len;
} Stack;

void initializeStack(Stack* ptr); // инициализация стека, выставляем указатель "head" в NULL, а длину - в 0
int isStackEmpty(Stack* ptr); // проверка стека на пустоту; этому состоянию соответствует указатель "head" == NULL
void push(Stack* ptr, char value); // положить элемент в стек
char pop(Stack* ptr); // удалить и при этом посмотреть удаляемый из стека элемент
char peek(Stack* ptr); // посмотреть элемент в стеке
void deleteStack(Stack* ptr); // удалить стек, осовободить память для всех его узлов (элементов)