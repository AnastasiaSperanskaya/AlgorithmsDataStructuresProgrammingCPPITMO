#include <iostream>
#include<stdio.h>
#include<fstream>
using namespace std;

void Merge(int *A, int first, int last)
{
    int middle, start, final, j;
    int *mas=new int[100];
    middle=(first+last)/2;
    start=first;
    final=middle+1;
    for(j=first; j<=last; j++)
        if ((start<=middle) && ((final>last) || (A[start]<A[final])))
        {
            mas[j]=A[start];
            start++;
        }
        else
        {
            mas[j]=A[final];
            final++;
        }

    for (j=first; j<=last; j++) A[j]=mas[j];
    delete[]mas;
};

void MergeSort(int *A, int first, int last)
{
    {
        if (first<last)
        {
            MergeSort(A, first, (first+last)/2);
            MergeSort(A, (first+last)/2+1, last);
            Merge(A, first, last);
        }
    }
};

int main()
{
    ifstream fin("sort.in");
    ofstream fout("sort.out");
    int n;
    fin >> n;
    int *A = new int[n];

    for (int i = 0; i < n; i++)
        fin >> A[i];

    MergeSort(A, 0, n);

    for (int i = 0; i < n; i++)
        fout << A[i] << ' ';

    fin.close();
    fout.close();
    delete []A;
    return 0;
}