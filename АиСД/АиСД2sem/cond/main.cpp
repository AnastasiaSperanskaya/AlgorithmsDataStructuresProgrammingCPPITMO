#include<iostream>
#include<vector>
#include<stack>

using namespace std;

void dfs(int &x, vector<vector<int>> &graf, vector<char> &color, stack<int> &sort)
{
    color[x] = 'g';
    int y;

    for(int i = 0; i < graf[x].size(); i++)
    {
        y = graf[x][i];
        if(color[y] == 'w')
            dfs(y, graf, color, sort);
    }

    color[x] = 'b';
    sort.push(x);
}

void dfs2(int &x, vector<vector<int>> &graf2, vector<int> &comp, int &col)
{
    comp[x] = col;
    int y;

    for(int i = 0; i < graf2[x].size(); i++)
    {
        y = graf2[x][i];
        if(comp[y] == 0)
            dfs2(y, graf2, comp, col);
    }

}

int main()
{
    freopen("cond.in", "r", stdin);
    freopen("cond.out", "w", stdout);

    int n, m, i, j, y, x;
    cin >> n >> m;

    vector<vector<int>> graf(n + 1);
    vector<vector<int>> graf2(n + 1);

    for(i = 0; i < m; i++)
    {
        cin >> x >> y;
        graf[x].push_back(y);
        graf2[y].push_back(x);
    }

    vector<char> color(n + 1);
    vector<int> comp(n + 1);
    for(i = 0; i <= n; i++)
    {
        color[i] = 'w';
        comp[i] = 0;
    }

    stack<int> sort;

    for(int i = 1; i <=n ; i++)
        if(color[i] != 'b')
            dfs(i, graf, color, sort);

    int col = 0;

    while(!sort.empty())
    {
        x = sort.top();

        if(comp[x] == 0)
        {
            col++;
            dfs2(x, graf2, comp, col);
        }

        sort.pop();
    }

    cout << col << endl;

    for(i = 1; i < comp.size(); i++)
        cout << comp[i] << " ";
}
