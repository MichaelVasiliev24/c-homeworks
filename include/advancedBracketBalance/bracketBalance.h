#pragma once

#include "stackOnPointers.h"
#include <stdbool.h>

// Константы
#define MAX_INPUT_STRING_SIZE 1000

// Функции проверки скобок
bool isOpenBracket(char bracket);
bool isCloseBracket(char bracket);
bool areMatchingBrackets(char openBracket, char closeBracket);

// Основная функция проверки баланса
bool checkBracketBalance(const char* expression);

// Вспомогательные функции
void cleanInputString(char* input);
void printBalanceResult(bool isBalanced);