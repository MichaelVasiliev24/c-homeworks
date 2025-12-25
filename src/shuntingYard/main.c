#include "../../include/shuntingYard/shuntingYard.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    char inputExpression[MAX_INPUT_STRING_SIZE];
    char outputExpression[MAX_OUTPUT_STRING_SIZE];

    printf("Введите выражение в инфиксной форме: ");

    if (fgets(inputExpression, sizeof(inputExpression), stdin) == NULL) {
        printf("Ошибка чтения ввода\n");
        return 1;
    }

    // Удаляем символ новой строки
    size_t len = strlen(inputExpression);
    if (len > 0 && inputExpression[len - 1] == '\n') {
        inputExpression[len - 1] = '\0';
    }

    int result = infixToPostfix(inputExpression, outputExpression, MAX_OUTPUT_STRING_SIZE);

    if (result == 1) {
        printf("Выражение в постфиксной форме:%s\n", outputExpression);
    }
    else {
        printf("Ошибка преобразования выражения. Проверьте корректность ввода\n");
        return 1;
    }

    return 0;
}