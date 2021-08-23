#include <iostream>
#include<fstream>
using namespace std;

void antiQsort(int a[], int n)
{
for (int i=0; i<n; i++)
    swap(a[i], a[i / 2]);
}

int main()
{
    ifstream fin("antiqs.in");
    ofstream fout("antiqs.out");
    int size;
    fin>>size;
    int a[size];
    for (int i = 0; i < size; i++)
        a[i]=i+1;

    antiQsort(a, size);

    for (int i = 0; i < size; i++)
        fout << a[i] << ' ';
    return 0;
}