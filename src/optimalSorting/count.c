#include "count.h"
#include <stdio.h>

int countMovedElements(const int original[], const int sorted[], int n)
{
    int moved = 0;

    if (original == NULL || sorted == NULL || n <= 0) {
        return 0; // Явный возврат при некорректных параметрах
    }

    for (int i = 0; i < n; i++) {
        if (original[i] != sorted[i]) {
            moved++;
        }
    }

    return moved; // Гарантированный возврат
}