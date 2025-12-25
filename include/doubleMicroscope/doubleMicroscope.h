#pragma once
#include <stdbool.h>

// Константы для формата IEEE 754 double
#define DOUBLE_BITS 64
#define SIGN_POSITION 63
#define EXPONENT_POSITION 52
#define MANTISSA_BITS 52
#define EXPONENT_BIAS 1023
#define EXPONENT_MAX 0x7FF
#define HIDDEN_BIT (1ULL << MANTISSA_BITS)
#define BASE_TWO 2.0
#define DENORMALIZED_EXPONENT (-1022) // 1 - EXPONENT_BIAS

typedef union DoubleUnion {
    double value;
    struct {
        unsigned long long mantissa : 52;
        unsigned int exponent : 11;
        unsigned int sign : 1;
    } parts;
} DoubleUnion;

void analyzeDouble(double num);
bool getBit(unsigned long long value, int position);
void printBinary64(unsigned long long value);