#include<iostream>
#include<vector>
#include<stack>

using namespace std;

void dfs(int x, int n ,vector<vector<int>> &graf,vector<char> &color, stack<int> &sort,bool &flag)
{
    color[x] = 'g';
    int y;

    for(int i = 0; i < graf[x].size(); i++)
    {
        y = graf[x][i];
        if(color[y] == 'w')
            dfs(y, n, graf, color, sort, flag);

        if(color[y] == 'g')
            flag = 0;
    }

    color[x] = 'b';
    sort.push(x);
}

int main()
{
    freopen("topsort.in", "r", stdin);
    freopen("topsort.out", "w", stdout);

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
    bool flag = 1;

    for(int i = 1; i <= n; i++)
        if(color[i] != 'b')
            dfs(i, n, graf, color, sort, flag);

    if(flag)
    {
        while(!sort.empty())
        {
            cout << sort.top() << " ";
            sort.pop();
        }
    } else
        cout << "-1";

}
