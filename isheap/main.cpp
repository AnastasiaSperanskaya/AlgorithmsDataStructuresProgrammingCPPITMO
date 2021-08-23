#include<iostream>
#include<stdio.h>
#include<fstream>
#include<vector>
using namespace std;

int main()
{
    int n, k;

    ifstream fin("isheap.in");
    ofstream fout("isheap.out");

    fin >> n;
    vector<int> Arr(n);
    for (int i = 0; i < n; ++i)
    {
        fin >> Arr[i];
    }

    k = 0;
    for (int i = 0; i < (n/2) -1; ++i)
    {
        if ((Arr[i] > Arr[(2 * i) + 1]) || (Arr[i] > Arr[(2 * i) + 2]))
            ++k;
    }

    if(k==0)
        fout << "YES" << endl;
    else
        fout << "NO" << endl;
}
