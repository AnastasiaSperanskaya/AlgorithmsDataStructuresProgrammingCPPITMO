#include <stdio.h>
#include <math.h>

struct coord
{
    int x[1000];
    int y[1000];
};

void func(int n, int R, struct coord A, int *k1, int *k2, int *k3)
{
    int kk1 = 0;
    int kk2 = 0;
    int kk3 = 0;
    for(int i = 0; i < n; i++)
    {
        if((A.x[i]>=0) && (sqrt(pow(A.x[i],2) + pow(A.x[i],2)) <= R))
            kk1++;
        if(sqrt(pow(A.x[i],2) + pow(A.x[i],2)) <= R)
            kk2++;
        if(sqrt(pow(A.x[i],2) + pow(A.x[i],2)) > R)
            kk3++;
    };
    *k1 = kk1;
    *k2 = kk2;
    *k3 = kk3;
}

int main()
{
    int R;
    int n;

    int k1, k2, k3;

    scanf("%d",&R);
    scanf("%d",&n);

    struct coord A;
    for(int i = 0; i < n; i++)
        scanf("%d%d",&A.x[i], &A.y[i]);
    func(n, R, A, &k1, &k2, &k3);

    printf("Amount of points in the circle with conditions %d\n", k1);
    printf("Amount of all points in the circle %d\n", k2);
    printf("Amount of points out of the circle %d\n", k3);

    return 0;
}