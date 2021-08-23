#include <cstdlib>
#include <iostream>
#include<fstream>
using namespace std;

int partition(int arr[], int low, int high)
{
    int pivot = arr[low];
    int i = low - 1, j = high + 1;

    while (true)
    {

        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j)
            return j;

        swap(arr[i], arr[j]);
    }
}

int partition_r(int arr[], int low, int high)
{
    int random = low + rand() % (high - low);

    swap(arr[random], arr[low]);

    return partition(arr, low, high);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        int pi = partition_r(arr, low, high);
        quickSort(arr, low, pi);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{
    ifstream fin("sort.in");
    ofstream fout("sort.out");
    int n;
    fin>>n;
    int a[n];
    for (int i = 0; i < n; i++)
        fin >> a[i];

    quickSort(a, 0, n - 1);

    for (int i = 0; i < n; i++)
        fout << a[i] << ' ';
    return 0;
}
