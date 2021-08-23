#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

typedef vector< vector<char> > Graph;

bool dfs(Graph const &graph, int index_n, vector<int> &matching, vector<char> &busy, int m)
{
    for (int i = 0; i < m; ++i)
        if (graph[index_n][i] && !busy[i])
        {
            busy[i] = 1;

            if (matching[i] == -1 || dfs(graph, matching[i], matching, busy, m))
            {
                matching[i] = index_n;
                return true;
            }
        }
    return false;
}

int main()
{
    ifstream in("matching.in");
    ofstream out("matching.out");

    int n, m, k;
    in >> n >> m >> k;

    Graph graph(n);

    for (auto &v : graph)
        v.resize(m, 0);

    for (int i = 0; i < k; ++i)
    {
        int from = 0, to = 0;
        in >> from >> to;
        graph[from - 1][to - 1] = 1;
    }

    vector<int> matching(m, -1);
    vector<char> busy(m, 0);

    for (int i = 0; i < n; ++i)
    {
        busy.assign(m, 0);
        dfs(graph, i, matching, busy, m);
    }

    out << m - count(matching.begin(), matching.end(), -1);

    return 0;
}
