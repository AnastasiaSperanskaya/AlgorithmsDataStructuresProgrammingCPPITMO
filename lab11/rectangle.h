#ifndef LAB11_1_RECTANGLE_H
#define LAB11_1_RECTANGLE_H

struct coord
{
    int x[4];
    int y[4];

};

double SQ(int x[4], int y[4]);
double Per(int x[4], int y[4]);
void input(struct coord *A);

#endif //LAB11_1_RECTANGLE_H
