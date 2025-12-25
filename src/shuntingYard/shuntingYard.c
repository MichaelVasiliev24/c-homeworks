#include "../../include/shuntingYard/shuntingYard.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

int isOperator(char symbol)
{
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}

int getPriority(char symbol)
{
    switch (symbol) {
        case '*':
        case '/':
            return 2; // Высокий приоритет
        case '+':
        case '-':
            return 1; // Низкий приоритет
        case '(':
            return 0; // Скобка имеет самый низкий приоритет
        default:
            return -1; // Не оператор
    }
}

int addOperatorToOutput(char operatorChar, char* postfix, size_t* postfixPos, size_t maxSize)
{
    if (*postfixPos + 2 >= maxSize) {
        return 0; // Ошибка: переполнение буфера
    }

    postfix[*postfixPos] = ' ';
    (*postfixPos)++;
    postfix[*postfixPos] = operatorChar;
    (*postfixPos)++;

    return 1; // Успех
}

int addOperandToOutput(char operand, char* postfix, size_t* postfixPos, size_t maxSize)
{
    // Добавляем пробел перед операндом (кроме первого)
    if (*postfixPos > 0 && postfix[*postfixPos - 1] != ' ') {
        if (*postfixPos + 1 >= maxSize) {
            return 0; // Ошибка: переполнение буфера
        }
        postfix[*postfixPos] = ' ';
        (*postfixPos)++;
    }

    if (*postfixPos >= maxSize) {
        return 0; // Ошибка: переполнение буфера
    }

    postfix[*postfixPos] = operand;
    (*postfixPos)++;

    return 1;
}

int handleOperator(char currentSymbol, Stack* stack, char* postfix, size_t* postfixPos, size_t maxSize)
{
    // Выталкиваем из стека операторы с большим или равным приоритетом
    while (!isStackEmpty(stack) && isOperator(peek(stack)) && getPriority(peek(stack)) >= getPriority(currentSymbol)) {

        if (!addOperatorToOutput(pop(stack), postfix, postfixPos, maxSize)) {
            return 0; // Ошибка: переполнение буфера
        }
    }

    push(stack, currentSymbol);
    return 1;
}

int handleClosingBracket(Stack* stack, char* postfix, size_t* postfixPos, size_t maxSize)
{
    // Выталкиваем все операторы до открывающей скобки
    while (!isStackEmpty(stack) && peek(stack) != '(') {
        if (!addOperatorToOutput(pop(stack), postfix, postfixPos, maxSize)) {
            return 0; // Ошибка: переполнение буфера
        }
    }

    // Проверяем, что стек не пуст и на вершине действительно '('
    if (!isStackEmpty(stack)) {
        assert(peek(stack) == '(');
        pop(stack); // Удаляем '(' из стека
        return 1; // Успех
    }

    // Если стек пуст - несбалансированные скобки
    return 0;
}

int processRemainingOperators(Stack* stack, char* postfix, size_t* postfixPos, size_t maxSize)
{
    while (!isStackEmpty(stack)) {
        char operatorChar = pop(stack);

        // Проверяем, что не осталось незакрытых скобок
        if (operatorChar == '(') {
            return 0; // Несбалансированные скобки
        }

        if (!addOperatorToOutput(operatorChar, postfix, postfixPos, maxSize)) {
            return 0; // Ошибка: переполнение буфера
        }
    }

    return 1;
}

int processCurrentSymbol(char currentSymbol, Stack* stack, char* postfix, size_t* postfixPos, size_t maxSize)
{
    // Пропускаем пробелы во входной строке
    if (currentSymbol == ' ') {
        return 1; // Успех - пробел проигнорирован
    }

    // Если это цифра (операнд)
    if (currentSymbol >= '0' && currentSymbol <= '9') {
        return addOperandToOutput(currentSymbol, postfix, postfixPos, maxSize);
    }

    // Если это оператор
    if (isOperator(currentSymbol)) {
        return handleOperator(currentSymbol, stack, postfix, postfixPos, maxSize);
    }

    // Если это открывающая скобка
    if (currentSymbol == '(') {
        push(stack, currentSymbol);
        return 1;
    }

    // Если это закрывающая скобка
    if (currentSymbol == ')') {
        return handleClosingBracket(stack, postfix, postfixPos, maxSize);
    }

    // Недопустимый символ
    return 0;
}

int infixToPostfix(const char* infix, char* postfix, size_t maxSize)
{
    Stack stack;
    initializeStack(&stack);

    size_t infixLen = strlen(infix);
    size_t postfixPos = 0;

    // Обрабатываем каждый символ входного выражения
    for (size_t i = 0; i < infixLen; i++) {
        char currentSymbol = infix[i];

        if (!processCurrentSymbol(currentSymbol, &stack, postfix,
                &postfixPos, maxSize)) {
            deleteStack(&stack);
            return 0; // Ошибка
        }
    }

    // Обрабатываем оставшиеся операторы в стеке
    if (!processRemainingOperators(&stack, postfix, &postfixPos, maxSize)) {
        deleteStack(&stack);
        return 0; // Ошибка
    }

    // Завершаем строку
    if (postfixPos >= maxSize) {
        deleteStack(&stack);
        return 0;
    }

    postfix[postfixPos] = '\0';
    deleteStack(&stack);

    return 1;
}