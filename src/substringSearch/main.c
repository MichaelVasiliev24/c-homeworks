#include <stdio.h>
#include <string.h>
#define MAX_STRING_SIZE 1000

unsigned int numberOfOccurrences(const char* str, const char* str1);

int main(void)
{
    char stringS[MAX_STRING_SIZE];
    char stringS1[MAX_STRING_SIZE];

    printf("Введите строку S: ");
    fgets(stringS, sizeof(stringS), stdin);
    printf("Введите строку S1: ");
    fgets(stringS1, sizeof(stringS1), stdin);

    stringS[strcspn(stringS, "\n")] = '\0';
    stringS1[strcspn(stringS1, "\n")] = '\0';

    printf("Количество вхождений S1 в S, как подстроки: %u\n", numberOfOccurrences(stringS, stringS1));
    return 0;
}

unsigned int numberOfOccurrences(const char* str, const char* str1)
{
    unsigned int counter = 0;
    const char* ptr = str;
    while ((ptr = strstr(ptr, str1)) != NULL) {
        counter++;
        ptr++;
    }
    return counter;
}