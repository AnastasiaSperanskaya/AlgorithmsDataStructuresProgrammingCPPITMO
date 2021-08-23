#include <vector>
#include <fstream>
#include <queue>
#include <limits>
#include <iostream>
#include <list>
#define INF LLONG_MAX

using namespace std;

typedef pair< long long, list<int> > Decomposition;

struct Edge
{
    int from, to, number, id;
    long long capacity, flow;
    Edge(int from, int to, long long cap, long long flow, int number, int id)
            : from(from), to(to), capacity(capacity), flow(flow), number(number), id(id) {}

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

    void add_edge(int from, int to, long long capacity, int number)
    {
        adj[from].push_back(edges.size());
        edges.emplace_back(from, to, capacity, 0, number, edges.size());
        adj[to].push_back(edges.size());
        edges.emplace_back(to, from, 0, 0, number, edges.size());
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


int64_t dfs(Graph & graph, int u, int sink, long long flow)
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

void decomposition(Graph & graph, Decomposition &p)
{
    p.first = -1;
    p.second.clear();

    vector<char> used(graph.size());
    int v = 0;

    while (!used[v])
    {
        if (v == graph.size() - 1)
            break;

        int edge_id = -1;

        for (auto u : graph[v])
            if (graph.edges[u].flow > 0)
            {
                edge_id = u;
                break;
            }

        if (edge_id == -1)
        {
            p.first = -1;
            p.second.clear();
            return;
        }

        p.second.push_back(edge_id);
        used[v] = 1;
        v = graph.edges[edge_id].to;
    }

    if (used[v])
        while (graph.edges[p.second.front()].from != v)
            p.second.pop_front();

    long long decomposition_flow = INF;

    for (auto edge_id : p.second)
        if (graph.edges[edge_id].flow < decomposition_flow)
            decomposition_flow = graph.edges[edge_id].flow;


    for (auto edge_id : p.second)
        graph.edges[edge_id].flow -= decomposition_flow;

    p.first = decomposition_flow;
}

int main()
{
    ifstream in("decomposition.in");
    ofstream out("decomposition.out");

    int n = 0, m = 0;
    in >> n >> m;

    Graph graph(n);

    for (long long i = 0; i < m; i++)
    {
        int from, to;
        long long capacity = 0;
        in >> from >> to >> capacity;
        graph.add_edge(from - 1, to - 1, capacity, i + 1);
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

    vector<Decomposition> decompositions;

    Decomposition p;

    decomposition(graph, p);

    while (p.first != -1)
    {
        decompositions.emplace_back(p.first, p.second);
        decomposition(graph, p);
    }

    out << decompositions.size() << endl;

    for (auto const &decomp : decompositions)
    {
        out << decomp.first << ' ' << decomp.second.size() << ' ';

        for (auto const &edge_id : decomp.second)
            out << graph.edges[edge_id].number << ' ';

        out << endl;
    }

    return 0;
}