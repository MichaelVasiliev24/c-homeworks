#pragma once

#include "stackOnPointers.h"

// Константы для строк
#define MAX_INPUT_STRING_SIZE 1000
#define MAX_OUTPUT_STRING_SIZE 2000

// Функция для проверки, является ли символ оператором
int isOperator(char symbol);

// Функция для определения приоритета оператора
int getPriority(char symbol);

// Функция для преобразования инфиксного выражения в постфиксное, возвращает 1 при успехе, 0 при ошибке (для булевой логики)
int infixToPostfix(const char* infix, char* postfix, size_t maxSize);

// Вспомогательная функция для добавления оператора в выходную строку
int addOperatorToOutput(char operatorChar, char* postfix, size_t* postfixPos, size_t maxSize);

// Вспомогательная функция для добавления операнда в выходную строку
int addOperandToOutput(char operand, char* postfix, size_t* postfixPos, size_t maxSize);

// Вспомогательная функция для обработки оператора
int handleOperator(char currentSymbol, Stack* stack, char* postfix, size_t* postfixPos, size_t maxSize);

// Вспомогательная функция для обработки закрывающей скобки
int handleClosingBracket(Stack* stack, char* postfix, size_t* postfixPos, size_t maxSize);

// Вспомогательная функция для обработки оставшихся операторов в стеке
int processRemainingOperators(Stack* stack, char* postfix, size_t* postfixPos, size_t maxSize);

// Вспомогательная функция для обработки текущего символа
int processCurrentSymbol(char currentSymbol, Stack* stack, char* postfix, size_t* postfixPos, size_t maxSize);