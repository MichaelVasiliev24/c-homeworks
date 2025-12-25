#include "count.h"

int countMovedElements(const int original[], const int sorted[], int n)
{
    int moved = 0;

    for (int i = 0; i < n; i++) {
        if (original[i] != sorted[i]) {
            moved++;
        }
    }

    return moved;
}