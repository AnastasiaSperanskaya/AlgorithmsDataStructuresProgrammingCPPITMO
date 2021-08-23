#include <queue>
#include <vector>
#include <fstream>
#include <climits>

using namespace std;

long minimum = LONG_MAX;

struct edge
{
    int start;
    int	finish;
    int maxCap;
};

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

void FordFulkerson(int V, vector<vector<int>> &graph, int T)
{
    vector<int> parent(V);

    while (true)
    {
        bool ispath = BFS(parent, V, graph, T);

        if (!ispath)
            break;

        minimum = LONG_MAX;

        GetMin(T, parent, graph);
        DecreasePaths(T, parent, graph);
    }
}

int main()
{
    ifstream fin("circulation.in");
    int V, E;
    fin >> V >> E;

    vector<vector<int>> graph((V + 2), vector<int>(V + 2));
    int stock = V + 1;

    //vector<edge> e(E);//задать размер
    edge * e = new edge[E];

    for (int i = 0; i < E; i++)
    {
        int from, to, minCap, maxCap;
        fin >> from >> to >> minCap >> maxCap;

        graph[from][to] = maxCap - minCap;
        graph[0][to] += minCap;
        graph[from][stock] += minCap;

        //e.push_back({ from, to, maxCap });
        e[i].start = from;
        e[i].finish = to;
        e[i].maxCap = maxCap;
    }
    fin.close();

    FordFulkerson(V + 2, graph, stock);

    ofstream fout("circulation.out");

    for (int i = 0; i < graph.size(); i++)
    {
        if (graph[0][i] != 0)
        {
            fout << "NO";
            fout.close();
            break;
        }
    }

    fout << "YES" << "\n";
    for (int i = 0; i < E; i++)
    {
        edge result = e[i];
        //e.pop_back();
        fout << result.maxCap - graph[result.start][result.finish] << "\n";
    }
}
