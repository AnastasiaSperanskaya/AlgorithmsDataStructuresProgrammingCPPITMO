#include <fstream>
#include <vector>
using namespace std;

static int i = 0, j = 0;

void partition(vector<int> &arr, int &l, int &r)
{
    int k = (l + r) / 2;
    int key = arr[k];
    i = l;
    j = r;

    while (i <= j)
    {
        while (arr[i] < key)
            i++;
        while (key < arr[j])
            j--;

        if (i <= j)
        {
            int t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
            i++;
            j--;
        }
    }
}

int kth(vector<int> &arr, int l, int r, int k)
{

    if (r < l)
    {
        return arr[l];
    }

    partition(arr, l, r);

    if (j + 1 <= k && k <= i - 1)
    {
        return arr[j + 1];
    }
    else if (l <= k && k <= j)
    {
        return kth(arr, l, j, k);
    }
    else
    {
        return kth(arr, i, r, k);
    }
}

int main()
{
    ifstream fin("kth.in");
    ofstream fout("kth.out");
    int n, k, A, B, C;
    fin >> n >> k >> A >> B >> C;
    --k;

    vector<int> arr(n);
    fin >> arr[0];
    fin >> arr[1];

    for (int i = 2; i < n; i++)
    {
        arr[i] = A * arr[i - 2] + B * arr[i - 1] + C;
    }

    int result = kth(arr, 0, arr.size() - 1, k);

    fout << result;
     return 0;
}