#pragma once
#include <stddef.h>

#define BITS 32
#define BITS_PER_BYTE 8
#define HIGH_BIT_MASK_32BIT 0x80000000U

// Преобразование числа в двоичную строку (дополнительный код)
void toBinaryTwosComplement(int num, char* binary);

// Сложение двух двоичных чисел в столбик
void binaryAddition(const char* bin1, const char* bin2, char* result);

// Преобразование двоичной строки (дополнительный код) обратно в int
int fromBinaryTwosComplement(const char* binary);

// Вспомогательная функция для получения маски старшего бита
unsigned int getHighBitMask(void);

// Вспомогательная функция для получения размера unsigned int в битах
size_t getUnsignedIntBits(void);