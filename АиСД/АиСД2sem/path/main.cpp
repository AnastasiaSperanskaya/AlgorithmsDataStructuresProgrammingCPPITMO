
#include <fstream>
#include <iostream>
#include <vector>
#include <forward_list>
#include <climits>
#define INF (LONG_LONG_MAX / 2)

using namespace std;

struct Edge
{
    Edge(int vert, long long w) :
            vert(vert),
            weight(w) {}

    int vert;
    long long weight;
};

struct BellFord
{
    void SetSize()
    {
        dist.resize(v);
        color.resize(v);
        walkable.resize(v);
        adj_lists.resize(v);
        for (int i = 0; i < v; ++i)
            adj_lists[i].clear();
    }

    void Init()
    {
        for (int i = 0; i < v; ++i)
            dist[i] = INF;

        dist[start] = 0;
        walkable[start] = true;
    }

    void Relax(int out, int in, long long w)
    {
        if (dist[out] < INF && dist[out] + w < dist[in])
        {
            if (walkable[out])
                walkable[in] = true;

            dist[in] = dist[out] + w;

            if (dist[in] > INF)
                dist[in] = INF;
            if (dist[in] < -INF)
                dist[in] = -INF;
        }

    }

    void Visit(int vert)
    {
        color[vert] = true;
        for (auto it = adj_lists[vert].begin(); it != adj_lists[vert].end(); ++it)
            if (!color[it->vert])
                Visit(it->vert);
    }

    vector<long double> dist;
    vector<bool>walkable;
    vector<bool>color; // false - path exists
    vector<forward_list<Edge>> adj_lists;

    int start;
    unsigned v;
    unsigned e;

};

int main()
{
    ifstream input("path.in");
    ofstream output("path.out");

    BellFord info;
    input >> info.v >> info.e >> info.start;
    --info.start;

    info.SetSize();
    info.Init();

    long long weight = 0;
    int out = 0;
    int in = 0;

    for (int i = 0; i < info.e; ++i)
    {
        input >> out >> in >> weight;
        info.adj_lists[out - 1].emplace_front(in - 1, weight);
    }

    for (int k = 0; k < info.v - 1; ++k)
        for (int i = 0; i < info.v; ++i)
            for (auto it = info.adj_lists[i].begin(); it != info.adj_lists[i].end(); ++it)
                info.Relax(i, it->vert, it->weight);

    for (int i = 0; i < info.v; ++i)
        for (auto it = info.adj_lists[i].begin(); it != info.adj_lists[i].end(); ++it)
            if (info.walkable[i] && info.dist[i] + it->weight < info.dist[it->vert] && !info.color[it->vert])
                info.Visit(it->vert);

    for (int i = 0; i < info.v; ++i)
    {
        if (!info.walkable[i])
            output << "*" << endl;
        else if (info.color[i])
            output << "-" << endl;
        else output << (long long)info.dist[i] << endl;
    }

    output.close();
    input.close();
}
