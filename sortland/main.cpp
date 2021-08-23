#include<iostream>
#include<stdio.h>
#include<fstream>
using namespace std;

int main() {
    ifstream fin("sortland.in");
    ofstream fout("sortland.out");
    int a;
    float f;
    fin >> a;
    float mas[a-1];
    short m[a-1];
    short b;
    for (int i = 0; i < a; i++) {
        fin >> mas[i];
        m[i] = i+1;
    }

    for (int i = 0; i < a; i++) {
        for (int j = a - 1; j > i; j--) {
            if (mas[j - 1] > mas[j]) {
                f = mas[j - 1];
                mas[j - 1] = mas[j];
                mas[j] = f;
                b = m[j - 1];
                m[j - 1] = m[j];
                m[j] = b;

            }
        }
    }

    fout <<m[0]<<' '<<m[a / 2]<<' '<<m[a-1]<<endl;
    return 0;
}