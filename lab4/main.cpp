#include <iostream>
using namespace std;
#include<stdio.h>

int main() {

    setlocale(LC_ALL, "Rus");

    int a=0,b=0,c;

    scanf("%d", &a);
    int diapStart = 65;
    const int diapStop = 87;

    for (; diapStart <= diapStop && b == 0; diapStart++)
    {
        b = diapStart == a;
    }

    switch (b) {
        case 1:
            printf("число входит в диапазон\n ");
            break;
        case 0:
            printf("число не входит в диапазон\n ");
            break;

    }

    cout<<endl;

    int x,y=1;
    scanf("%o",&x);
    printf("%o",(x >> 24)&y);
    return 0;
}