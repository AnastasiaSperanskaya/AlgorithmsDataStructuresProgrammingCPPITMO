#include <fstream>
#include <vector>
#include <set>
#define INF LLONG_MAX
using namespace std;

int main()
{
    ifstream in;
    ofstream out;

    in.open("pathbgep.in");
    out.open("pathbgep.out");

    int V, E;

    in >> V >> E;

    vector<vector<pair<int, int>>> adj(V + 1);

    vector<long long> d(V + 1, INF);
    vector<bool> used(V + 1, false);

    set <pair<int, int>> Set;

    int f, s, weight;

    for (int i = 0; i < E; i++)
    {
        in >> f >> s >> weight;
        adj[f].push_back({ s, weight });
        adj[s].push_back({ f, weight });
    }

    Set.insert({ 1, 1 });
    d[1] = 0;

    while (!Set.empty())
    {
        pair<int,int> currentEdge = *(Set.begin());
        int currentTop = currentEdge.second;
        Set.erase(Set.begin());

        for (auto v : adj[currentTop])
        {
            int weight = v.second,
                    to = v.first;
            
            if (d[currentTop] + weight < d[to])
            {
                Set.erase({ d[to], to });
                d[to] = d[currentTop] + weight;
                Set.insert({ d[to], to });
            }
        }
    }

    for (int i = 1; i < d.size(); i++)
        out << d[i] << ' ';


    return 0;
}
