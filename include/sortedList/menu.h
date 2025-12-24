#pragma once
#include "sortedList.h"

static void clearInputBuffer(void);
static int readInt(const char* prompt, int* value);
static void printMenu(void);
static void handleInsert(SortedList* list);
static void handleDelete(SortedList* list);
static int processChoice(int choice, SortedList* list);
