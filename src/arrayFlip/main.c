#include <stdio.h>
#include <stdlib.h>

int* getArray(unsigned int* lengthInitialSegment, unsigned int* lengthFinalSegment);
void printArray(int* ptr, unsigned int len);
void swap(int* variable1, int* variable2);
void reverseArray(int* ptr, unsigned int startedPos, unsigned int len);

int main(void)
{
    unsigned int lenM;
    unsigned int lenN;

    int* inputArray = getArray(&lenM, &lenN);
    if (inputArray != NULL && lenM + lenN != 1) {
        reverseArray(inputArray, 0, lenM + lenN);
        reverseArray(inputArray, 0, lenN);
        reverseArray(inputArray, lenN, lenM);
        printf("Массив после перестановки начала и конца:\n");
        printArray(inputArray, lenM + lenN);
        printf("\n");
        free(inputArray);
        return 0;
    }
    else if (inputArray != NULL && lenM + lenN == 1) {
        printf("Массив после перестановки начала и конца:\n");
        printArray(inputArray, lenM + lenN);
        printf("\n");
        free(inputArray);
        return 0;
    }
    else if (inputArray == NULL) {
        printf("Оишбка выделения памяти для массива\n");
        return 1;
    }
}

int* getArray(unsigned int* lengthInitialSegment, unsigned int* lengthFinalSegment)
{
    printf("Введите размер начала массива (m): ");
    scanf("%u", lengthInitialSegment);
    printf("Ввдеите размер конца массива (n): ");
    scanf("%u", lengthFinalSegment);

    int* newArray = (int*)malloc(sizeof(int) * (*lengthInitialSegment + *lengthFinalSegment));

    if (newArray != NULL) {
        for (unsigned int i = 0; i < *lengthInitialSegment + *lengthFinalSegment; i++) {
            printf("Введите %u число массива: ", i + 1);
            scanf("%d", &newArray[i]);
        }
        return newArray;
    }
    else {
        return NULL;
    }
}

void printArray(int* ptr, unsigned int len)
{
    for (unsigned int i = 0; i < len; i++) {
        printf("%d", ptr[i]);
    }
}

void swap(int* variable1, int* variable2)
{
    int tempVariable = *variable1;
    *variable1 = *variable2;
    *variable2 = tempVariable;
}

void reverseArray(int* ptr, unsigned int startedPos, unsigned int len)
{
    for (unsigned int i = startedPos, finalPos = startedPos + len - 1; i < startedPos + (len / 2); i++, finalPos--) {
        swap(&ptr[i], &ptr[finalPos]);
    }
}