#include <vector>
#include <fstream>
#include <queue>
#include <limits>
#include <iostream>
#include <list>
#define INF LLONG_MAX
using namespace std;

struct Edge
{
    int from, to;
    bool true_edge;
    long long capacity, flow;
    Edge(int from, int to, long long capacity, long long flow, bool true_edge)
            : from(from), to(to), capacity(capacity), flow(flow), true_edge(true_edge) {}

    long long available_capacity() const
    {
        return capacity - flow;
    }
};

struct Graph
{
    vector< vector<int> > adj;
    vector<Edge> edges;
    vector<int> levels;
    vector<int> ptr;

    explicit
    Graph(int n)
    {
        adj.resize(n);
        levels.resize(n);
        ptr.resize(n);
    }

    vector<int> &operator [] (int index)
    {
        return adj[index];
    }

    void add_edge(int from, int to, long long capacity)
    {
        adj[from].push_back(edges.size());
        edges.emplace_back(from, to, capacity, 0, (from != 0 && to != size() - 1));
        adj[to].push_back(edges.size());
        edges.emplace_back(to, from, 0, 0, 0);
    }

    size_t size() const
    {
        return adj.size();
    }
};


bool bfs(Graph & graph, int source, int sink)
{
    graph.levels.assign(graph.size(), -1);

    queue<int> queue;

    queue.push(source);
    graph.levels[source] = 0;

    while (!queue.empty() && graph.levels[sink] == -1)
    {
        int from = queue.front();
        queue.pop();

        for (auto id : graph[from])
        {
            int to = graph.edges[id].to;

            if (graph.levels[to] == -1 && graph.edges[id].available_capacity() > 0)
            {
                queue.push(to);
                graph.levels[to] = graph.levels[from] + 1;
            }
        }
    }

    return graph.levels[sink] != -1;
}


long long dfs(Graph & graph, int u, int sink, long long flow)
{
    if (flow == 0)
        return 0;

    if (u == sink)
        return flow;

    while (graph.ptr[u] < graph[u].size())
    {
        int id = graph[u][graph.ptr[u]];
        int v = graph.edges[id].to;

        if (graph.levels[u] + 1 != graph.levels[v])
        {
            graph.ptr[u]++;
            continue;
        }

        long long pushed_flow = dfs(graph, v, sink, min(flow, graph.edges[id].available_capacity()));

        if (pushed_flow != 0)
        {
            graph.edges[id].flow += pushed_flow;
            graph.edges[id ^ 1].flow -= pushed_flow;
            return pushed_flow;
        }

        graph.ptr[u]++;
    }

    return 0;
}

int main()
{
    ifstream in("circulation.in");
    ofstream out("circulation.out");

    int n, m;
    in >> n >> m;

    Graph graph(n + 2);

    for (size_t i = 0; i < m; i++)
    {
        int from = 0, to = 0;
        long long min_capacity = 0, max_capacity = 0;
        in >> from >> to >> min_capacity >> max_capacity;
        graph.add_edge(0, to, min_capacity);
        graph.add_edge(from, to, max_capacity - min_capacity);
        graph.add_edge(from, graph.size() - 1, min_capacity);
    }

    long long max_flow = 0;

    while (true)
    {
        if (!bfs(graph, 0, graph.size() - 1))
            break;

        graph.ptr.assign(graph.size(), 0);

        long long flow = dfs(graph, 0, graph.size() - 1, INF);
        while (flow != 0)
        {
            max_flow += flow;
            flow = dfs(graph, 0, graph.size() - 1, INF);
        }
    }

    bool F = true;

    for (auto edge : graph.edges)
        if (edge.from == 0)
            if (edge.flow < edge.capacity)
                F = false;

    if (F)
    {
        out << "YES" << endl;
        for (long long id = 0; id < graph.edges.size(); ++id)
        {
            auto edge = graph.edges[id];
            if (edge.true_edge)
                out << edge.flow + graph.edges[id-2].capacity << endl;
        }
    }
    else
        out << "NO";

    return 0;
}
