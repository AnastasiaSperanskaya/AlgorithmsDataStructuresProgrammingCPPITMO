#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream input("input.txt");
    ofstream output("output.txt");

    int n;
    input >> n;

    int ** matrix = new int * [n];

    for (int i = 0; i < n; i++)
        matrix[i] = new int[n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            input >> matrix[i][j];
    }

    bool not_orient = true;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((i == j && matrix[i][j] == 1) || (matrix[i][j] != matrix[j][i]))
            {
                not_orient = false;
                break;
            }
        }
    }

    if (not_orient)
        output << "YES" << endl;
    else output << "NO" << endl;

    for (int i = 0; i < n; i++)
        delete[] matrix[i];

    delete[] matrix;

    input.close();
    output.close();

    return 0;
}
