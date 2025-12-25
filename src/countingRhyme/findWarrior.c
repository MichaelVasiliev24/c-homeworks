#include "../../include/countingRhyme/circularList.h"
#include "../../include/countingRhyme/findWarrior.h"
#include <stdio.h>
#include <stdlib.h>

int findLastWarriorPosition(CountingParams params)
{
    if (params.warriorsCount <= 0 || params.eliminationStep <= 0) {
        printf("Ошибка: Некорректные входные данные.\n");
        return -1;
    }

    if (params.warriorsCount == 1) {
        return 1;
    }

    Node* circle = createCircularList(params.warriorsCount);
    if (circle == NULL) {
        printf("Ошибка: Не удалось создать список воинов.\n");
        return -1;
    }

    Node* prev = circle;
    while (prev->next != circle) {
        prev = prev->next;
    }

    Node* current = circle;

    while (current->next != current) {
        for (int count = 1; count < params.eliminationStep; count++) {
            prev = current;
            current = current->next;
        }

        prev->next = current->next;

        if (current == circle) {
            circle = current->next;
        }

        Node* toRemove = current;
        current = current->next;
        free(toRemove);
    }

    int lastPosition = current->data;
    free(current);

    return lastPosition;
}