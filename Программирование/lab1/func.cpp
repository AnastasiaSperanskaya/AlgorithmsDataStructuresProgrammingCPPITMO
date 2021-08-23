#include "func.h"
#include <iostream>
#include <stdio.h>
using namespace std;

void  third1(int *a, int *b)
{
    if(*a > *b)
    {
        *a = *a % *b;
    }
    else
    {
        *b = *b % *a;
    }
}

void  third2(int &a, int &b)
{
    if(a > b)
    {
        a = a % b;
    }
    else
    {
        b = b % a;
    }
}

void eighth1(double *m)
{
    *m = 1/ *m;
}

void eighth2(double &m)
{
    m = 1/m;
}

void eleventh1(struct circle *c, double n)
{
    c->R -= n;
}

void eleventh2(struct circle &c, double n)
{
    c.R = c.R - n;
}

void sixteenth1(int **A, int M, int N, int q, int p)
{
    for(int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            cin >> A[i][j];

    int s;
    for(int i = 0; i < N; i++)
    {
        s = A[q][i];
        A[q][i] = A[p][i];
        A[p][i] = s;
    }

    cout << endl;

    for(int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
            cout << A[i][j] << " ";

        cout << endl;
    }

}

void swap1(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
};

void sixteenth2(int &matrix, int str1, int str2, int width)
{
    int *i = &matrix + (str2 - 1) * width;
    int *j = &matrix + (str1 - 1) * width;

    for(int k = 0; k < width; k++){
        swap1(i,j);
        i++;
        j++;
    }
}

