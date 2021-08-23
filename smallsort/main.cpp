#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream fin("smallsort.in");
    ofstream fout("smallsort.out");
    int a, f;
    fin >> a;
    int mas[a];
    for(int i=0;i<a;i++)
        fin>>mas[i];

    for( int i=0; i<a; i++) {
        for(int j=a-1; j>i; j--) {
            if (mas[j-1]>mas[j]) {
                f=mas[j-1]; mas[j-1]=mas[j]; mas[j]=f;
            }
        }
    }

    for(int i=0;i<a;i++)
        fout<<mas[i]<<' ';
    return 0;
}