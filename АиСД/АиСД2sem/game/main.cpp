#include<iostream>
#include<vector>
#include<stack>

using namespace std;

void dfs(int x, vector<vector<int>> &graf, vector<char> &color, vector<bool> &check)
{
    color[x] = 'g';
    int y;

    if(graf[x].size() == 0)
        check[x] = 0;

    for(int i = 0; i < graf[x].size(); i++)
    {
        y = graf[x][i];

        if(color[y] == 'w')
            dfs(y, graf, color, check);

        if((!check[x]) && (!check[y]))
            check[x] = 1;
    }
    color[x] = 'b';
}

int main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);

    int n, m, v, i, j, y, x;
    cin >> n >> m >> v;

    vector<vector<int>> graf(n + 1);

    for(i = 0; i < m; i++)
    {
        cin >> x >> y;
        graf[x].push_back(y);
    }

    vector<char> color(n + 1);
    vector<bool> check(n + 1);

    for(i = 0; i <= n; i++)
    {
        color[i] = 'w';
        check[i] = 0;
    }

    dfs(v, graf, color, check);

    if(check[v])
        cout << "First player wins";
    else
        cout << "Second player wins";
}
