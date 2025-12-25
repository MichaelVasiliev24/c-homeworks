#include <stdio.h>

int main(void)
{
    int varX;

    printf("Введите переменную x: ");
    scanf("%d", &varX);

    int intermediateResult = varX * varX;
    int result = ((intermediateResult + varX) * (intermediateResult + 1)) + 1;
    printf("Значение формулы x^4 + x^3 + x^2 + x + 1, полученное за два умножения: %d\n", result);
    return 0;
}