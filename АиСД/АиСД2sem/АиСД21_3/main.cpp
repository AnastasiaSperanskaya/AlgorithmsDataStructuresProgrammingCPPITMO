#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream input("input.txt");
    ofstream output("output.txt");

    int n, m;

    input >> n >> m;

    int ** matrix = new int * [n];

    for (int i = 0; i < n; i++)
        matrix[i] = new int[n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            matrix[i][j] = 0;
    }

    int i, j;

    for (int k = 0; k < m; k++)
    {
        input >> i >> j;

        if (i == j)
            matrix[i - 1][j - 1]++;
        else
        {
            matrix[i - 1][j - 1]++;
            matrix[j - 1][i - 1]++;
        }
    }

    bool not_parallel = true;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            if (matrix[i][j] > 1)
            {
                not_parallel = false;
                break;
            }
    }

    if (not_parallel)
        output << "NO";
    else output << "YES";

    for (int i = 0; i < n; i++)
        delete[] matrix[i];

    delete[] matrix;

    input.close();
    output.close();

    return 0;
}
