#include "../../include/countingRhyme/findWarrior.h"
#include <stdio.h>

int main(void)
{
    CountingParams params;

    printf("Введите количество воинов: ");
    scanf("%d", &params.warriorsCount);

    printf("Введите шаг исключения: ");
    scanf("%d", &params.eliminationStep);

    int lastWarrior = findLastWarriorPosition(params);

    if (lastWarrior != -1) {
        printf("Позиция последнего оставшегося воина: %d\n", lastWarrior);
    }
    else {
        printf("Не удалось решить задачу\n");
        return 1;
    }

    return 0;
}