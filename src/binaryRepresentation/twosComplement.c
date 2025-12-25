#include "../../include/binaryRepresentation/twosComplement.h"

size_t getUnsignedIntBits(void)
{
    return sizeof(unsigned int) * BITS_PER_BYTE;
}

unsigned int getHighBitMask(void)
{
    return (BITS == getUnsignedIntBits())
        ? HIGH_BIT_MASK_32BIT
        : 1U << (BITS - 1);
}

void toBinaryTwosComplement(int num, char* binary)
{
    if (BITS > getUnsignedIntBits()) {
        binary[0] = '\0';
        return;
    }

    unsigned int unum = (unsigned int)num;
    unsigned int mask = getHighBitMask();

    for (int i = 0; i < BITS; i++) {
        binary[i] = (unum & mask) ? '1' : '0';
        mask >>= 1;
    }
    binary[BITS] = '\0';
}

void binaryAddition(const char* bin1, const char* bin2, char* result)
{
    int carry = 0;

    for (int i = BITS - 1; i >= 0; i--) {
        int bit1 = (bin1[i] == '1') ? 1 : 0;
        int bit2 = (bin2[i] == '1') ? 1 : 0;

        int sum = bit1 + bit2 + carry;
        result[i] = (sum & 1) ? '1' : '0';
        carry = sum >> 1;
    }

    result[BITS] = '\0';
}

int fromBinaryTwosComplement(const char* binary)
{
    unsigned int temp = 0;

    for (int i = 0; i < BITS; i++) {
        temp = (temp << 1) | (binary[i] - '0');
    }

    unsigned int highBitMask = getHighBitMask();

    if (!(temp & highBitMask)) {
        return (int)temp;
    }

    int signBitWeight = 1 << (BITS - 1);
    return (int)temp - (2 * signBitWeight);
}