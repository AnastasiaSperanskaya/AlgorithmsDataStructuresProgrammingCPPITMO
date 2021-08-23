#include<iostream>
#include<vector>
#include<stack>

using namespace std;

void dfs(int x, int n, vector<vector<int>> &graf, vector<char> &color, stack<int> &sort)
{
    color[x] = 'g';
    int y;

    for(int i = 0; i < graf[x].size(); i++)
    {
        y = graf[x][i];
        if(color[y] == 'w')
            dfs(y, n, graf, color, sort);
    }

    color[x] = 'b';
    sort.push(x);
}

int main()
{
    freopen("hamiltonian.in", "r", stdin);
    freopen("hamiltonian.out", "w", stdout);

    int n, m, i, j, y, x;
    cin >> n >> m;

    vector<vector<int>> graf(n + 1);

    for(i = 0; i < m; i++)
    {
        cin >> x >> y;
        graf[x].push_back(y);
    }

    vector<char> color(n + 1);

    for(i = 0; i <= n; i++)
        color[i] = 'w';
    stack<int> sort;

    for(int i = 1; i <= n; i++)
        if(color[i] != 'b')
            dfs(i, n, graf, color, sort);

    bool flag = 1;

    if(!sort.empty())
    {
        x = sort.top();
        sort.pop();
    }

    while((!sort.empty()) && (flag))
    {
        y = sort.top();
        sort.pop();
        flag = 0;

        for(i = 0; i < graf[x].size(); i++)
            if(graf[x][i] == y)
                flag = 1;
        x = y;
    }

    if(flag)
        cout << "YES";
    else
        cout << "NO";

}
