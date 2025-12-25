#pragma once

typedef struct {
    int warriorsCount;
    int eliminationStep;
} CountingParams;

int findLastWarriorPosition(CountingParams params);