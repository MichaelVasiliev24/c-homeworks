#include "../../include/doubleMicroscope/doubleMicroscope.h"
#include <stdio.h>

int main(void)
{
    double number;

    printf("Enter a number: ");
    if (scanf("%lf", &number) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    analyzeDouble(number);
    return 0;
}