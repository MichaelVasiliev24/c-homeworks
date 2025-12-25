#include "shuntingYard.h"
#include "stackOnPointers.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool isOperator(char symbol)
{
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}

int operatorPriority(char symbol)
{
    switch (symbol) {
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        case '(':
            return 0;
        default:
            return -1;
    }
}

bool addToOutput(char symbol, bool needSpace, char* output, size_t* outputPos, size_t maxSize)
{
    if (*outputPos + (needSpace ? 2 : 1) >= maxSize) {
        return false;
    }

    if (needSpace) {
        output[(*outputPos)++] = ' ';
    }

    output[(*outputPos)++] = symbol;
    return true;
}

bool infixToPostfix(const char* infix, char* postfix, size_t maxSize)
{
    Stack stack;
    initializeStack(&stack);

    size_t infixLen = strlen(infix);
    size_t outputPos = 0;
    bool lastWasDigit = false;
    bool error = false;

    for (size_t i = 0; i < infixLen && !error; i++) {
        char symbol = infix[i];

        // Пропускаем пробелы
        if (symbol == ' ') {
            continue;
        }

        // Обработка цифр (операндов)
        if (isdigit((unsigned char)symbol)) {
            if (!addToOutput(symbol, lastWasDigit, postfix, &outputPos, maxSize)) {
                error = true;
                break;
            }
            lastWasDigit = true;
            continue;
        }

        // Обработка операторов
        if (isOperator(symbol)) {
            // Выталкиваем из стека операторы с более высоким или равным приоритетом
            while (!isStackEmpty(&stack) && isOperator(peek(&stack)) && operatorPriority(peek(&stack)) >= operatorPriority(symbol)) {

                if (!addToOutput(pop(&stack), true, postfix, &outputPos, maxSize)) {
                    error = true;
                    break;
                }
            }

            if (!error) {
                push(&stack, symbol);
            }
            lastWasDigit = false;
            continue;
        }

        // Обработка открывающей скобки
        if (symbol == '(') {
            push(&stack, symbol);
            lastWasDigit = false;
            continue;
        }

        // Обработка закрывающей скобки
        if (symbol == ')') {
            // Выталкиваем операторы до открывающей скобки
            while (!isStackEmpty(&stack) && peek(&stack) != '(') {
                if (!addToOutput(pop(&stack), true, postfix, &outputPos, maxSize)) {
                    error = true;
                    break;
                }
            }

            if (!error) {
                if (isStackEmpty(&stack)) {
                    error = true; // Несбалансированные скобки
                }
                else {
                    pop(&stack); // Удаляем '('
                }
            }
            lastWasDigit = false;
            continue;
        }

        // Недопустимый символ
        error = true;
    }

    // Обработка оставшихся операторов в стеке
    if (!error) {
        while (!isStackEmpty(&stack)) {
            char op = pop(&stack);
            if (op == '(') {
                error = true; // Несбалансированные скобки
                break;
            }
            if (!addToOutput(op, true, postfix, &outputPos, maxSize)) {
                error = true;
                break;
            }
        }
    }

    // Завершаем строку
    if (!error && outputPos < maxSize) {
        postfix[outputPos] = '\0';
    }
    else {
        error = true;
    }

    deleteStack(&stack);
    return !error;
}