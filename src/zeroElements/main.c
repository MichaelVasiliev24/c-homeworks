#include <stdio.h>
#include <stdlib.h>

int* getAnArrayOfIntegers(unsigned int* size);
unsigned int calculateTheNumberOfZeroElemets(const int* inputArr, unsigned int len);

int main(void)
{
    int* inputArray;
    unsigned int lenInputArr;

    inputArray = getAnArrayOfIntegers(&lenInputArr);

    if (inputArray != NULL) {
        printf("Количество нулевых элементов в массиве: %u\n", calculateTheNumberOfZeroElemets(inputArray, lenInputArr));
        free(inputArray);
        return 0;
    }
    else {
        printf("Ошибка выделения памяти для массива\n");
        return 1;
    }
}

int* getAnArrayOfIntegers(unsigned int* size)
{
    printf("Введите размер массива: ");
    scanf("%u", size);

    int* createdArray = (int*)malloc(*size * sizeof(int));

    if (createdArray != NULL) {
        for (unsigned int i = 0; i <= *size - 1; i++) {
            printf("Введите %u число массива: ", i + 1);
            scanf("%d", createdArray + i);
        }
        return createdArray;
    }
    else {
        return NULL;
    }
}

unsigned int calculateTheNumberOfZeroElemets(const int* inputArr, unsigned int len)
{
    unsigned int counter = 0;
    for (unsigned int i = 0; i <= len - 1; i++) {
        if (inputArr[i] == 0) {
            counter++;
        }
    }
    return counter;
}