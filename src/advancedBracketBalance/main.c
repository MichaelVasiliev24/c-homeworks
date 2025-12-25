#include <stdio.h>
#include <stdlib.h>
#include "../../include/advancedBracketBalance/bracketBalance.h"

int main(void)
{
    char inputExpression[MAX_INPUT_STRING_SIZE];

    printf("Введите строку: ");
    if (fgets(inputExpression, sizeof(inputExpression), stdin) == NULL) {
        fprintf(stderr, "Ошибка чтения ввода\n");
        return EXIT_FAILURE;
    }

    cleanInputString(inputExpression);

    bool isBalanced = checkBracketBalance(inputExpression);
    printBalanceResult(isBalanced);

    return isBalanced ? EXIT_SUCCESS : EXIT_FAILURE;
}