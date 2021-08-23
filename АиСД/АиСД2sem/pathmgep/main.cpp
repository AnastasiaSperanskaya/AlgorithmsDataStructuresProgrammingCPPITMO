#include <fstream>
#include <vector>
#include <forward_list>
#include <climits>
#define INF LONG_LONG_MAX

using namespace std;


int main()
{
    ifstream in("pathmgep.in");
    ofstream out("pathmgep.out");

    int v, s, f;

    in >> v >> s >> f;

    --s;
    --f;

    vector<vector<int>> matrix(v, vector<int>(v));

    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++)
            in >> matrix[i][j];

    vector<long long>distance(v, INF);
    vector<bool>color(v);

    distance[s] = 0;

    for (int i = 0; i < v; i++)
    {
        int vert = -1;

        for (int j = 0; j < v; j++)
            if (!color[j] && (vert == -1 || distance[j] < distance[vert]))
                vert = j;

        if (distance[vert] == INF)
            break;

        color[vert] = true;
        for (int j = 0; j < v; j++)
            if (vert != j && matrix[vert][j] != -1 && distance[j] > distance[vert] + matrix[vert][j])
                distance[j] = distance[vert] + matrix[vert][j];
    }

    if (distance[f] != INF)
        out << distance[f];
    else out << -1;

    out.close();
    in.close();

    return 0;
}

