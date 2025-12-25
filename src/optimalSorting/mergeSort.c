#include "../../include/optimalSorting/mergeSort.h"
#include <stdlib.h>
#include <stdio.h>

void merge(int arr[], int left, int mid, int right)
{
    int idxL;
    int idxR;
    int idxM;
    int sizeL = mid - left + 1;
    int sizeR = right - mid;

    int* tempLeft = (int*)malloc(sizeL * sizeof(int));
    if (tempLeft == NULL) {
        fprintf(stderr, "Ошибка: не удалось выделить память для tempLeft\n");
        return;
    }

    int* tempRight = (int*)malloc(sizeR * sizeof(int));
    if (tempRight == NULL) {
        fprintf(stderr, "Ошибка: не удалось выделить память для tempRight\n");
        free(tempLeft);
        return;
    }

    for (idxL = 0; idxL < sizeL; idxL++) {
        tempLeft[idxL] = arr[left + idxL];
    }
    for (idxR = 0; idxR < sizeR; idxR++) {
        tempRight[idxR] = arr[mid + 1 + idxR];
    }

    idxL = 0;
    idxR = 0;
    idxM = left;

    while (idxL < sizeL && idxR < sizeR) {
        if (tempLeft[idxL] <= tempRight[idxR]) {
            arr[idxM] = tempLeft[idxL];
            idxL++;
        }
        else {
            arr[idxM] = tempRight[idxR];
            idxR++;
        }
        idxM++;
    }

    while (idxL < sizeL) {
        arr[idxM] = tempLeft[idxL];
        idxL++;
        idxM++;
    }

    while (idxR < sizeR) {
        arr[idxM] = tempRight[idxR];
        idxR++;
        idxM++;
    }

    free(tempLeft);
    free(tempRight);
}

void mergeSort(int arr[], int left, int right)
{
    if (arr == NULL) {
        fprintf(stderr, "Ошибка: передан нулевой указатель на массив\n");
        return;
    }

    if (left < 0 || right < 0 || left > right) {
        fprintf(stderr, "Ошибка: некорректные границы массива\n");
        return;
    }

    if (left >= right) {
        return;
    }

    int mid = left + ((right - left) / 2);

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}