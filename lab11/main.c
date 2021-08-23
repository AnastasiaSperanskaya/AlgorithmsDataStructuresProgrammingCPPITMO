#include "rectangle.h"
#include<stdio.h>
#include<math.h>

int main()
{
    struct coord A;

    input(&A);

    printf("\nArea is equal = %.2f\n", SQ(A.x, A.y));
    printf("\nPerimeter is equal = %.2f\n", Per(A.x, A.y));


    return 0;
}