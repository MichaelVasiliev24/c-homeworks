#include <stdio.h>
#define POSSIBLE_SUMS 28
#define MAX_FIGURE 9

int waysToSelectPossibleSums[POSSIBLE_SUMS] = { 0 };
void numberOfWaysToSelectSums(int* ptr);
unsigned int numberOfLuckyTickets(const int* ptr);

int main(void)
{
    numberOfWaysToSelectSums(waysToSelectPossibleSums);
    printf("Количество счастливых билетиков: %u\n", numberOfLuckyTickets(waysToSelectPossibleSums));
    return 0;
}

void numberOfWaysToSelectSums(int* ptr)
{
    for (int number1 = 0; number1 <= MAX_FIGURE; number1++) {
        for (int number2 = 0; number2 <= MAX_FIGURE; number2++) {
            for (int number3 = 0; number3 <= MAX_FIGURE; number3++) {
                ptr[number1 + number2 + number3]++;
            }
        }
    }
}

unsigned int numberOfLuckyTickets(const int* ptr)
{
    unsigned int counter = 0;
    for (unsigned int i = 0; i < POSSIBLE_SUMS; i++) {
        counter += (ptr[i] * ptr[i]);
    }
    return counter;
}