//#include "pch.h"
#include <queue>
#include <vector>
#include <fstream>
#include <climits>

using namespace std;

bool BFS(vector<int> &parent, int V_all, vector<vector<bool>> &graph, int T)
{
    vector<bool> used(V_all);

    queue<int> q;
    q.push(0);
    used[0] = true;
    parent[0] = -1;

    while (!q.empty())
    {
        int point = q.front();
        q.pop();

        for (int i = 0; i < V_all; i++)
        {
            if (!used[i] && graph[point][i])
            {
                q.push(i);
                parent[i] = point;
                used[i] = true;
            }
        }
    }

    return used[T];
}

void DecreasePaths(int point, vector<int> &parent, vector<vector<bool>> &graph)
{
    if (point == 0)
        return;

    graph[parent[point]][point] = false;

    graph[point][parent[point]] = true;

    DecreasePaths(parent[point], parent, graph);
}

int FordFulkerson(int V_all, vector<vector<bool>> &graph, int T)
{
    vector<int> parent(V_all);

    long matching = 0;

    while (true)
    {
        bool ispath = BFS(parent, V_all, graph, T);

        if (!ispath)
            break;


        DecreasePaths(T, parent, graph);

        matching++;
    }
    return matching;
}

int main()
{
    ifstream fin("matching.in");
    int leftside, rightside, E;
    fin >> leftside >> rightside >> E;

    int V_all = leftside + rightside + 2;//count of all vertex because of addition of sourсe and stock

    vector<vector<bool>> graph(V_all, vector<bool>(V_all));

    int T = leftside + rightside + 1;//count of stock

    for (int i = 0; i < E; i++)
    {
        int start, finish;

        fin >> start >> finish;
        finish += leftside;

        graph[start][finish] = true;
    }
    fin.close();

    for (int i = 1; i <= leftside; i++)
    {
        graph[0][i] = true;
    }

    for (int i = leftside + 1; i < T; i++)
    {
        graph[i][T] = true;
    }

    ofstream fout("matching.out");

    fout << FordFulkerson(V_all, graph, T);

    fout.close();
}