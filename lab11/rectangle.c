#include <stdio.h>
#include <math.h>
#include "rectangle.h"

double SQ(int x[4], int y[4])
{
    double a,b,c,p;
    a = sqrt(pow(x[1] - x[0],2) + pow(y[1] - y[0],2));
    b = sqrt(pow(x[1] - x[2],2) + pow(y[1] - y[2],2));
    c = sqrt(pow(x[0] - x[2],2) + pow(y[0] - y[2],2));
    p = (a + c + b) / 2;
    return 2 * sqrt(p * (p - a) * (p - b) * (p - c));
}

double Per(int x[4], int y[4])
{
    double a,b;
    a = sqrt(pow(x[1] - x[0],2) + pow(y[1] - y[0],2));
    b = sqrt(pow(x[1] - x[2],2) + pow(y[1] - y[2],2));
    return 2 * (a + b);
}

void input(struct coord *A)
{
    scanf("%d%d",&A -> x[0],&A -> y[0]);
    scanf("%d%d",&A -> x[1],&A -> y[1]);
    scanf("%d%d",&A -> x[2],&A -> y[2]);
    scanf("%d%d",&A -> x[3],&A -> y[3]);
}

