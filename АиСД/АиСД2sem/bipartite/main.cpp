#include<iostream>
#include<vector>
#include<stack>

using namespace std;

void dfs(int x, int n, vector<vector<int>> &graf, vector<char> &color, vector<int> &check, bool &flag)
{
    color[x] = 'g';
    int y;

    if(check[x] == 0)
        check[x] = 1;

    for(int i = 0; i < graf[x].size(); i++)
    {
        y = graf[x][i];
        if(check[y] == 0)
        {
            if(check[x] == 1)
                check[y] = 2;
            if(check[x] == 2)
                check[y] = 1;
        }
        if(check[x] == check[y])
            flag = 0;

        if(color[y] == 'w')
            dfs(y, n, graf, color, check, flag);
    }

    color[x] = 'b';

}

int main()
{
    freopen("bipartite.in", "r", stdin);
    freopen("bipartite.out", "w", stdout);

    int n, m, i, j, y, x;
    cin >> n >> m;
    vector<int> check(n + 1);
    vector<vector<int>> graf(n + 1);

    for(i = 0; i < m; i++)
    {
        cin >> x >> y;
        graf[x].push_back(y);
        graf[y].push_back(x);
    }

    vector<char> color(n + 1);

    for(i = 0; i <= n; i++)
        color[i] = 'w';

    stack<int> sort;
    bool flag = 1;
    check[1] = 1;

    for(int i = 1; i <= n; i++)
        if(color[i] != 'b')
            dfs(i, n, graf, color, check, flag);

    if(flag)
        cout << "YES";
    else
        cout << "NO";
}
