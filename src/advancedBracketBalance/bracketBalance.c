#include "../../include/advancedBracketBalance/bracketBalance.h"
#include <stdio.h>
#include <string.h>

bool isOpenBracket(char bracket)
{
    return (bracket == '(' || bracket == '{' || bracket == '[');
}

bool isCloseBracket(char bracket)
{
    return (bracket == ')' || bracket == '}' || bracket == ']');
}

bool areMatchingBrackets(char openBracket, char closeBracket)
{
    switch (openBracket) {
        case '(':
            return closeBracket == ')';
        case '{':
            return closeBracket == '}';
        case '[':
            return closeBracket == ']';
        default:
            return false;
    }
}

void cleanInputString(char* input)
{
    // Удаляем символ новой строки, если он есть
    size_t length = strlen(input);
    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    }
}

void printBalanceResult(bool isBalanced)
{
    if (isBalanced) {
        printf("Баланс есть\n");
    }
    else {
        printf("Баланса нет\n");
    }
}

bool checkBracketBalance(const char* expression)
{
    Stack bracketStack;
    initializeStack(&bracketStack);

    size_t length = strlen(expression);

    for (size_t i = 0; i < length; i++) {
        char currentChar = expression[i];

        if (isOpenBracket(currentChar)) {
            push(&bracketStack, currentChar);
        }
        else if (isCloseBracket(currentChar)) {
            if (isStackEmpty(&bracketStack)) {
                deleteStack(&bracketStack);
                return false; // Закрывающая скобка без открывающей
            }

            if (areMatchingBrackets(peek(&bracketStack), currentChar)) {
                pop(&bracketStack);
            }
            else {
                deleteStack(&bracketStack);
                return false; // Несоответствующие скобки
            }
        }
        // Игнорируем все остальные символы
    }

    bool result = isStackEmpty(&bracketStack);
    deleteStack(&bracketStack);
    return result;
}