#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_STRING_SIZE 1000

bool checkBracketsBalance(const char* str, char openBracket, char closeBracket, unsigned int len);

int main(void)
{
    char inputString[MAX_STRING_SIZE];
    char openBracket;
    char closeBracket;
    unsigned int lenInputString;

    printf("Введите строку: ");
    fgets(inputString, sizeof(inputString), stdin);
    inputString[strcspn(inputString, "\n")] = '\0';
    lenInputString = strlen(inputString);

    printf("Введите открывающую скобку того типа, для которого проверяется баланс: ");
    scanf("%c", &openBracket);
    printf("Введите закрывающую скобку того типа, для которого проверяется баланс: ");
    scanf(" %c", &closeBracket);

    if (checkBracketsBalance(inputString, openBracket, closeBracket, lenInputString) == true) {
        printf("Баланс для скобок %c%c есть\n", openBracket, closeBracket);
        return 0;
    }
    else if (checkBracketsBalance(inputString, openBracket, closeBracket, lenInputString) == false) {
        printf("Баланса для скобок %c%c нет\n", openBracket, closeBracket);
        return 1;
    }
}

bool checkBracketsBalance(const char* str, char openBracket, char closeBracket, unsigned int len)
{
    int counter = 0;
    for (unsigned int i = 0; i <= len - 1; i++) {
        if (str[i] == openBracket) {
            counter++;
        }
        else if (str[i] == closeBracket && counter == 0) {
            return false;
        }
        else if (str[i] == closeBracket && counter != 0) {
            counter--;
        }
    }

    if (counter == 0) {
        return true;
    }
    else {
        return false;
    }
}