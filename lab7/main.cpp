#include <iostream>
#include<math.h>

enum TypeCar
{
    LEGKOVOI = 1,
    GRUZOVOI,
    AVTOBUS,
    GONOCHNIY

};

struct coordRect
{
    int x[4];
    int y[4];

} A;

union status{
    struct{
        unsigned record : 1;
        unsigned pause : 1;
        unsigned play : 1;
    }bits;
    unsigned char data;
};

double SQ(int x[4], int y[4])
{
    double a,b;
    a = sqrt(pow(x[1]-x[0],2)+pow(y[1]-y[0],2));
    b = sqrt(pow(x[1]-x[2],2)+pow(y[1]-y[2],2));
    return a*b;
}

int main()
{
    //Задание 1; Вариант 4
    enum TypeCar a, b, c, d;
    a = LEGKOVOI;
    b = GRUZOVOI;
    c = AVTOBUS;
    d = GONOCHNIY;
    printf("\nAVTOBUS number = %d\n", c);

    //Задание 2; Вариант 2
    A.x[0] = -4; A.y[0] = 2;
    A.x[1] = 3; A.y[1] = 2;
    A.x[2] = 3; A.y[2] = -1;
    A.x[3] = -4; A.y[3] = -1;
    printf("\nArea is equal = %.2f\n", SQ(A.x, A.y));

    //Задание 3; Вариант 3
    printf("\nEnter the number: ");

    union status stat;

    scanf("%hhx", &(stat.data));

    printf("\nMP3-player State:\n");
    printf("Playing: %s\n", (stat.bits.record) ? "ON" : "OFF");
    printf("Pause: %s\n", (stat.bits.pause) ? "ON" : "OFF");
    printf("Record: %s\n", (stat.bits.play) ? "ON" : "OFF");
}