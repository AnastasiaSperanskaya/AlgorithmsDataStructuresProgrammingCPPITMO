#ifndef LAB2_1_1_FUNC_H
#define LAB2_1_1_FUNC_H

struct circle
{
    double x;
    double y;
    double R;
};

void  third1(int *a, int *b);
void  third2(int &a, int &b);
void eighth1(double *m);
void eighth2(double &m);
void eleventh1(struct circle *c, double n);
void eleventh2(struct circle &c, double n);
void sixteenth1(int **A, int M, int N, int q, int p);
void swap1(int *a, int *b);
void sixteenth2(int &matrix, int N, int q, int p);

#endif //LAB2_1_1_FUNC_H
