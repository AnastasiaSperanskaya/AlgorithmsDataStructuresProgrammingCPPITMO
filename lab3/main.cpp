#include <iostream>
#include<stdio.h>
using namespace std;


int main() {
    /*
    int a, b;
    scanf("%x", &a);
    scanf("%x", &b);
    printf("%x %d\n", a, a);
    printf("%x %d\n", b, b);
     */

    int x,y;
    scanf("%x",&x);
    printf("%o\n",x);
    printf("%x\n",x);
    printf("%x\n",x >> 4);
    printf("%x\n",x);
    printf("%x\n",~x);

    scanf("%x",&y);
    printf("%x",y^x);



    return 0;
}