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

    for (int k = 0; k < n; k++)
        matrix[k] = new int[n];

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
           matrix[k][i] = 0;
    }

    int i, j;

    for (int k = 0; k < m; k++)
    {
        input >> i >> j;
        matrix[i - 1][j - 1] = 1;
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
            output << matrix[k][i] << " ";
        output << endl;
    }

    for (int k = 0; k < n; k++)
        delete[] matrix[k];

    delete[] matrix;

    input.close();
    output.close();

    return 0;
}