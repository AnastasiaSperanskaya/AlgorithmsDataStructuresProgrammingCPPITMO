#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


struct DSU
{
private:
    unsigned long long size;
    vector<unsigned long long> parents;
    vector<unsigned long long> set_size;

public:
    explicit
    DSU(unsigned long long size) : size(size)
    {
        parents.resize(size);
        set_size.resize(size, 0);

        for (size_t i = 0; i < size; ++i)
            parents[i] = i;
    }

    void union_set(unsigned long long a, unsigned long long b)
    {
        unsigned long long set_a = get_set(a);
        unsigned long long set_b = get_set(b);

        if (set_a == set_b)
            return;

        if (set_size[set_a] < set_size[set_b])
            swap(set_a, set_b);

        parents[set_b] = set_a;
        set_size[set_a] += set_size[set_b];
    }

    unsigned long long get_set(unsigned long long a)
    {
        return a == parents[a] ? a : parents[a] = get_set(parents[a]);
    }
};


int main()
{
    ifstream in("spantree2.in");
    ofstream out("spantree2.out");

    vector< pair< long long, pair<long long, long long> > > graph;

    unsigned long long n = 0, m = 0;
    in >> n >> m;

    for (int i = 0; i < m; ++i)
    {
        long long from = 0, to = 0, w = 0;
        in >> from >> to >> w;

        graph.push_back({ w, {from - 1, to - 1} });
    }

    DSU components(n);

    sort(graph.begin(), graph.end());

    long long mst = 0;

    for (auto edge : graph)
    {
        int u = edge.second.first;
        int v = edge.second.second;
        int w = edge.first;

        if (components.get_set(u) != components.get_set(v))
        {
            components.union_set(u, v);
            mst += w;
        }
    }

    out << mst;

    return 0;
}
