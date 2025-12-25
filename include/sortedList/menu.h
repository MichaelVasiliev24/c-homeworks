#pragma once
#include "sortedList.h"

void clearInputBuffer(void);
int readInt(const char* prompt, int* value);
void printMenu(void);
void handleInsert(SortedList* list);
void handleDelete(SortedList* list);
int processChoice(int choice, SortedList* list);
