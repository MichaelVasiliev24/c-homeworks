#pragma once

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} SortedList;

SortedList* createSortedList(void);
void destroySortedList(SortedList* list);
void insertValue(SortedList* list, int value);
int deleteValue(SortedList* list, int value);
void printList(const SortedList* list);