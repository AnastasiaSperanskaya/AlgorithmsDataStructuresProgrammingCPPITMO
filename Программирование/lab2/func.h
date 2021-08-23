#ifndef LAB2_2_FUNC_H
#define LAB2_2_FUNC_H

struct square
{
    int x;
    int y;
    double side;
    int angle;
};

bool operator==(square sq, square sq1);
bool operator!=(square sq, square sq1);
bool operator>(square sq, square sq1);
bool operator<(square sq, square sq1);
square operator*(square sq, double n);
square operator+(square sq);

struct set
{
    int array[10];
};

set operator+(set a, set b);
set operator+=(set &a, int l);
set operator-(set a, int r);
bool operator==(set a, set b);
bool operator!=(set a, set b);


#endif //LAB2_2_FUNC_H
