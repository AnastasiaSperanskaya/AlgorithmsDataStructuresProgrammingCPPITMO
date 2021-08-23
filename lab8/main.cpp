#include <stdio.h>
#include <memory.h>
#include<string.h>

int countSameChars(char *first, char *second)
{
    int j = 0;
    for(int i = 0; i < strlen(first); i++)
    {
        char target = first[i];
        char *ch = strchr(second, target);
        if(ch != NULL)
            j++;
    }
    return j;
}

char SymbolSearch(char *first, char *second)
{
    char b = '_';
    for(int i = 0; i < strlen(first); i++)
    {
        char target = first[i];
        char *ch = strchr(second, target);
        if(ch != NULL)
            b = first[i];
    }
    return b;
}

int main(int c, char **args)
{
    int n1 = 64;

    char first[n1];
    printf("Enter first string:\n");
    scanf("%s", first);

    char second[n1];
    printf("\nEnter second string:\n");
    scanf("%s", second);

    //Вариант 1
    char third[n1];
    strcpy(third, first);
    strcat(third, second);

    printf("\nString 1 + string 2: %s\n", third);

    //Вариант 4
    char *first1 = first;
    char *second1 = second;
    int n;
    printf("\nEnter amount of symbols:\n");
    scanf("%d", &n);
    if(strncmp(first1,second1,n) > 0)
        printf("\nThe first %d symbols from second string is bigger\n", n);
    else if(strncmp(first1,second1,n) < 0)
        printf("\nThe first '%d' symbols from first string is bigger\n", n);
    else
        printf("\nThe first '%d' symbols are equal\n", n);

    //Вариант 7
    int p = strlen(first);
    printf("\nLength of string '%s' is %d\n", first, p);

    //Вариант 10
    char a = SymbolSearch(first, second);
    printf("\nSymbol in first string from the second is %c\n", a);

    //Вариант 11
    int count = countSameChars(first, second);
    printf("\nAmount of chars from '%s' in '%s': %d\n", second, first, count);

    return 0;
}