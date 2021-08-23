#include<iostream>
#include<fstream>
#include<stdio.h>
using namespace std;

 int firstSearch(int z, int a[], int n)
 {
        int l = 0;
        int r = n - 1;
        int m;
        while (l < r) {
            m = l + (r - l) / 2;
            if (a[m] < z)
                l = m + 1;
            else
                r = m;
        }
        if(a[l] == z)
            return l + 1;
        else
            return -1;
 }

int lastSearch(int z, int a[], int n)
{
        int l = 0;
        int r = n - 1;
        int m;
        while (l < r) {
            m = r - (r - l) / 2;
            if (a[m] > z)
                r = m - 1;
            else
                l = m;
        }
        if(a[l] == z)
            return l + 1;
        else
            return -1;
}

int main()
{
    ifstream fin("binsearch.in");
    ofstream fout("binsearch.out");

    int n;
    fin >> n;
    int a[n];

    for (int i = 0; i < n; i++)
        fin >> a[i];

    int m;

    fin >> m;

    int z, first, last;

    for (int i = 0; i < m; i++)
    {
        fin >> z;
        first = firstSearch(z, a, n);
        last = lastSearch(z, a, n);
        fout << first << " " << last << endl;
    }
 }