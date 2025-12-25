#include "../../include/optimalSorting/count.h"
#include <stdio.h>

int countMovedElements(const int original[], const int sorted[], int n)
{
    if (original == NULL || sorted == NULL) {
        return 0;
    }

    if (n <= 0 || n > MAX_ELEMENTS) {
        return 0;
    }

    int usedFlags[MAX_ELEMENTS];
    for (int idx = 0; idx < MAX_ELEMENTS; idx++) {
        usedFlags[idx] = 0;
    }

    int movedCount = 0;

    for (int origIdx = 0; origIdx < n; origIdx++) {
        int foundPosition = -1;

        for (int sortIdx = 0; sortIdx < n; sortIdx++) {
            if (sorted[sortIdx] == original[origIdx] && usedFlags[sortIdx] == 0) {
                foundPosition = sortIdx;
                usedFlags[sortIdx] = 1;
                break;
            }
        }

        if (foundPosition != -1 && origIdx != foundPosition) {
            movedCount++;
        }
    }

    return movedCount;
}