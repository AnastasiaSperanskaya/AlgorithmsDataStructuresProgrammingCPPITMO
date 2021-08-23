#include<iostream>
#include<fstream>
using namespace std;



int main()
{
    ifstream fin("sort.in");
    ofstream fout("sort.out");
    int size;
    fin >> size;
    int a[size];

    for (int i = 0; i < size; i++)
        fin >> a[i];

    for (int i = 0; i < size; i++)
    {
        int temp = a[i];
        int j = i - 1;
        while(j >= 0 && a[j] > temp)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = temp;
    }
    for (int i = 0; i < size; i++)
        fout << a[i] << ' ';
    fin.close();
    fout.close();
    return 0;
}