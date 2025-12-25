#include <stdio.h>
#include <stdlib.h>

int incompleteQuotient(int varA, int varB);

int main(void)
{
    int numberA;
    int numberB;

    printf("Введите целое число a: ");
    scanf("%d", &numberA);
    printf("Введите целое число b: ");
    scanf("%d", &numberB);

    if (numberB == 0) {
        printf("Ошибка, на ноль делить нельзя\n");
        return 1;
    }

    printf("Неполное частное от деления a на b: %d\n", incompleteQuotient(numberA, numberB));
    return 0;
}

int incompleteQuotient(int varA, int varB)
{
    int absA = abs(varA);
    int absB = abs(varB);

    int qTemp = 0;
    while (absA >= absB) {
        absA -= absB;
        qTemp++;
    }

    int sign = (varA * varB >= 0) ? 1 : -1;

    int needPlusOne = (varA < 0) && (absA > 0);

    return sign * (qTemp + needPlusOne);
}