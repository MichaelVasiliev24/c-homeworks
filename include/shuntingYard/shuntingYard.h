#pragma once

#include <stdbool.h>
#include <stddef.h>

#define MAX_INPUT_STRING_SIZE 256
#define MAX_OUTPUT_STRING_SIZE 512

// Функция проверки на оператора
bool isOperator(char symbol);

// Функция получения приоритета оператора
int operatorPriority(char symbol);

// Добавляет символ в выходную строку с пробелом перед ним, если нужно, возвращает false при переполнении буфера, иначе true.
bool addToOutput(char symbol, bool needSpace, char* output, size_t* outputPos, size_t maxSize);

// Функция для преобразования инфиксного выражения в постфиксное
bool infixToPostfix(const char* infix, char* postfix, size_t maxSize);
