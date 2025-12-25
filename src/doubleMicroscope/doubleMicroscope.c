#include "../../include/doubleMicroscope/doubleMicroscope.h"
#include <stdio.h>
#include <math.h>

bool getBit(unsigned long long value, int position)
{
    return (value >> position) & 1;
}

void printBinary64(unsigned long long value)
{
    for (int i = DOUBLE_BITS - 1; i >= 0; i--) {
        printf("%d", getBit(value, i));
        if (i == SIGN_POSITION || i == EXPONENT_POSITION) {
            printf(" ");
        }
    }
    printf("\n");
}

void analyzeDouble(double num)
{
    DoubleUnion doubleUnion;
    doubleUnion.value = num;

    // Извлекаем компоненты
    int sign = doubleUnion.parts.sign;
    int exponent = doubleUnion.parts.exponent;
    unsigned long long mantissa = doubleUnion.parts.mantissa;

    // Специальные случаи
    if (exponent == EXPONENT_MAX) {
        if (mantissa == 0) {
            printf("%sINF\n", sign ? "-" : "+");
            return;
        }
        printf("NaN\n");
        return;
    }

    // Для нормализованных чисел добавляем скрытый бит
    double normalizedMantissa;
    int trueExponent;

    // Конвертируем mantissa в double перед делением
    double mantissaAsDouble = (double)mantissa;
    double powerBase = pow(BASE_TWO, (double)MANTISSA_BITS);

    if (exponent == 0) {
        // Денормализованное число
        normalizedMantissa = mantissaAsDouble / powerBase;
        trueExponent = DENORMALIZED_EXPONENT;
    }
    else {
        // Нормализованное число - явно указываем порядок операций
        normalizedMantissa = 1.0 + (mantissaAsDouble / powerBase);
        trueExponent = exponent - EXPONENT_BIAS;
    }

    // Выводим результат с достаточной точностью
    char signChar = sign ? '-' : '+';
    printf("Result: %c%.19g*2^%d\n", signChar, normalizedMantissa, trueExponent);
}