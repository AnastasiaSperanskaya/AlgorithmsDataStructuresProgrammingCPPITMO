#include <iostream>
#include <vector>
#include <algorithm>
#define INF LLONG_MAX
using namespace std;

struct edge{
    long long from, to, cost;
};

int main()
{
    long long n;
    cin >> n;
    vector <edge> E;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            long long x;
            cin >> x;
            E.push_back({i,j,x});
        }
    }

    long long x;

    vector<long long> d(n, INF), p(n, -1);

    d[0] = 0;

    for(int i = 0; i < n; i++)
    {
        x = -1;
        for(int j = 0; j < E.size(); j++)
        {
            long long from = E[j].from;
            long long to = E[j].to;
            long long cost = E[j].cost;

            if(d[to] > d[from] + cost )
            {
                d[to] = max(d[from] + cost, -INF);
                p[to] = from;
                x = to;
            }
        }
    }

    if(x == -1)
        cout << "NO" << endl;
    else
    {
        long long y = x;
        for(int i = 0; i < n; i++)
            y = p[y];

        vector <long long> path;

        for(long long cur = y;; cur = p[cur])
        {
            path.push_back(cur);
            if(cur == y && path.size() > 1)
                break;
        }

        reverse(path.begin(), path.end());

        cout << "YES" << endl;
        cout << path.size() << endl;

        for(int i = 0; i < path.size(); i++)
        {
            cout << path[i] + 1;
            if(i != path.size()-1)
                cout << ' ';
        }
        cout << endl;
    }
    return 0;
}
