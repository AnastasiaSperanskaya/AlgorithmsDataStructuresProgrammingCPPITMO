#include<stdio.h>

int main()
{
    freopen("/Users/anastasia/Desktop/CLionProjects/lab12/file12.txt", "w", stdout);

    int a,b,c;
    scanf("%d%d",&a,&b);
    c = a + b;

    printf("%d", c);

    fclose(stdout);

    return 0;
}