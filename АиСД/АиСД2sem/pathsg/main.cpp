#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

#define INF LLONG_MAX

using namespace std;

int main()
{
    ifstream fin("pathsg.in");
    ofstream fout("pathsg.out");
    int V, E;
    fin >> V >> E;

    vector<vector<long long>> matrix(V, vector<long long>(V));

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
        {
            if (i == j)
                matrix[i][j] = 0;
            else
                matrix[i][j] = INF;
        }

    int v1, v2, d;

    for (int i = 0; i < E; i++)
    {
        fin >> v1 >> v2 >> d;
        --v1;
        --v2;
        matrix[v1][v2] = d;
    }

    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (matrix[i][k] < INF && matrix[k][j] < INF)
                    matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
            fout << matrix[i][j] << " ";
        fout << endl;
    }

    fin.close();
    fout.close();

    return 0;
}
