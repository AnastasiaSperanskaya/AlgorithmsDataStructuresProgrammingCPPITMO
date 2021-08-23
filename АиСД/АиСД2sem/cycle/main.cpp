#include<iostream>
#include<vector>
#include<stack>

using namespace std;

bool dfs(int x, int n, vector<vector<int>> &graf, vector<char> &color, vector<int> &prev)
{
    color[x] = 'g';
    int y;

    for(int i = 0; i < graf[x].size(); i++)
    {
        y = graf[x][i];
        prev[y] = x;

        if(color[y] == 'w')
        {
            if(dfs(y,n,graf,color,prev))
                return true;
        }

        if(color[y] == 'g')
        {
            prev[0] = y;
            prev[n + 1] = x;
            return true;
        }
    }

    color[x] = 'b';
    return false;
}

int main()
{
    freopen("cycle.in", "r", stdin);
    freopen("cycle.out", "w", stdout);

    int n, m, i, j, y, x;
    cin >> n >> m;

    vector<vector<int>> graf(n + 1);

    for(i = 0; i < m; i++)
    {
        cin >> x >> y;
        graf[x].push_back(y);
    }

    vector<char> color(n + 1);
    vector<int> prev(n + 2);

    for(i = 0; i <= n; i++)
    {
        color[i] = 'w';
        prev[i] = 0;
    }

    vector <int> sort;
    bool flag = 0;

    for(int i = 1; i <= n; i++)
    {
        if(dfs(i, n, graf, color, prev))
        {
            flag = 1;
            break;
        }
    }

    if(flag)
    {

        int start,end;
        start = prev[0];
        end = prev[n + 1];

        cout << "YES" << endl;
        sort.push_back(start);
        for(x = end; x != start; x = prev[x])
            sort.push_back(x);

        while(!sort.empty())
        {
            cout << sort.back() << " ";
            sort.pop_back();
        }
    } else
        cout << "NO";
}
