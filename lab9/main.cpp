#include <stdio.h>

int isPrime(int n){
    int c;
    for (c = 2 ; c <= n - 1; c++) {
        if(n % c == 0)
            break;
    }
    return c == n;
}

int main(int c, char **arg)
{
    //Вариант 4
    printf("Enter last number:\n");

    int n = 0;
    scanf("%d", &n);

    for(int i = 0; i <= n; i++){
        if(isPrime(i))
            printf("%d ", i);
    }

    //Вариант 5
    printf("\nEnter initial amount:\n");
    double sum;
    scanf("%lf", &sum);

    printf("\nEnter the interest rate:\n");
    double perc;
    scanf("%lf", &perc);

    printf("\nEnter the number of months:\n");
    int num;
    scanf("%d", &num);

    for(int i = 1; i <= num; i++)
        sum = sum * (1 + perc / 100);

    printf("\nState of the a/c: %.3lf", sum);
}