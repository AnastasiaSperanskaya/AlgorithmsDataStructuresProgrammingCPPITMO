#include <queue>
#include <vector>
#include <fstream>
#include <climits>

using namespace std;

long minimum = LLONG_MAX;

bool BFS(vector<int> &parent, int V, vector<vector<int>> &graph, int T)
{
    vector<bool> used(V);

    queue<int> q;
    q.push(0);
    used[0] = true;
    parent[0] = -1;
    while (!q.empty())
    {
        int point = q.front();
        q.pop();

        for (int i = 0; i < V; i++)
        {
            if (!used[i] && graph[point][i] > 0)
            {
                q.push(i);
                parent[i] = point;
                used[i] = true;
            }
        }
    }

    return used[T];
}

void GetMin(int point, vector<int> &parent, vector<vector<int>> &graph)
{
    if (point == 0)
        return;

    if (minimum > graph[parent[point]][point])
        minimum = graph[parent[point]][point];

    GetMin(parent[point], parent, graph);
}

void DecreasePaths(int point, vector<int> &parent, vector<vector<int>> &graph)
{
    if (point == 0)
        return;

    graph[parent[point]][point] -= minimum;

    graph[point][parent[point]] += minimum;

    DecreasePaths(parent[point], parent, graph);
}

int FordFulkerson(int V, vector<vector<int>> &graph, int T)
{
    vector<int> parent(V);
    long flow = 0;

    while (true)
    {
        bool ispath = BFS(parent, V, graph, T);

        if (!ispath)
            break;

        minimum = LONG_MAX;

        GetMin(T, parent, graph);
        DecreasePaths(T, parent, graph);

        flow += minimum;
    }
    return flow;
}

int main()
{
    ifstream fin("maxflow.in");
    int V, E;
    fin >> V >> E;
    vector<vector<int>> graph(V, vector<int>(V));
    int T = V - 1;

    for (int i = 0; i < E; i++)
    {
        int start, finish, value;

        fin >> start >> finish >> value;
        start--;
        finish--;
        graph[start][finish] = value;
    }
    fin.close();


    ofstream fout("maxflow.out");

    fout << FordFulkerson(V, graph, T);

    fout.close();
}