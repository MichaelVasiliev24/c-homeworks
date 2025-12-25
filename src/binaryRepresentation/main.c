#include "../../include/binaryRepresentation/twosComplement.h"
#include <stdio.h>

int main(void)
{
    int num1;
    int num2;

    // Ввод чисел
    printf("Введите первое число: ");
    scanf("%d", &num1);

    printf("Введите второе число: ");
    scanf("%d", &num2);

    // Подготовка буферов
    char bin1[BITS + 1];
    char bin2[BITS + 1];
    char binSum[BITS + 1];

    // 1. Переводим в двоичное представление
    toBinaryTwosComplement(num1, bin1);
    toBinaryTwosComplement(num2, bin2);

    printf("\nДвоичное представление (%d бит):\n", BITS);
    printf("Число 1: %s\n", bin1);
    printf("Число 2: %s\n", bin2);

    // 2. Складываем в двоичном виде
    binaryAddition(bin1, bin2, binSum);

    printf("\nСумма в двоичном виде:\n");
    printf("%s\n", binSum);

    // 3. Переводим сумму обратно в десятичное
    int sum = fromBinaryTwosComplement(binSum);

    printf("\nСумма в десятичном виде: %d\n", sum);

    // 4. Проверка
    printf("\nПроверка: %d + %d = %d\n", num1, num2, num1 + num2);

    return 0;
}