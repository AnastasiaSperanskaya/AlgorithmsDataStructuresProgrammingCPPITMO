#include "func.h"
#include <iostream>
#include <stdio.h>
using namespace std;

bool operator==(square sq, square sq1)
{
    if(sq.side == sq1.side)
        return 1;
    else
        return 0;
}

bool operator!=(square sq, square sq1)
{
    if(sq.side != sq1.side)
        return 1;
    else
        return 0;
}

bool operator>(square sq, square sq1)
{
    if(sq.side > sq1.side)
        return 1;
    else
        return 0;
}

bool operator<(square sq, square sq1)
{
    if(sq.side < sq1.side)
        return 1;
    else
        return 0;
}

square operator*(square sq, double n)
{
    return square{sq.x, sq.y, sq.side * n, sq.angle};
}

square operator+(square sq)
{
    int x, y;
    cin >> x >> y;
    return square{sq.x + x, sq.y + y, sq.side, sq.angle};
}

set operator+(set a, set b)
{
    set c;

    for(int i = 0; i < 10; i++)
        c.array[i] = -1;

    for(int i = 0; i < 10; i++)
    if(a.array[i] == i || b.array[i] == i)
        c.array[i] = i;
    return c;
}

set operator+=(set &a, int l)
{
    a.array[l] = l;
    return a;
}

set operator-(set a, int r)
{
    set c;
    for(int i = 0; i < 10; i++)
        c.array[i] = a.array[i];
    c.array[r] = -1;
    return c;
}

bool operator==(set a, set b)
{
    bool f = 1;
    for(int i = 0; i < 10; i++)
        if(a.array[i] != b.array[i])
            f = 0;
    return f;
}

bool operator!=(set a, set b)
{
    bool f = 1;
    for(int i = 0; i < 10; i++)
        if(a.array[i] != b.array[i])
            f = 0;
    if(f)
        return 0;
    else
        return 1;
}

