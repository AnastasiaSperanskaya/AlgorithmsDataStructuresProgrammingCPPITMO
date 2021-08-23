#include <iostream>
#include <fstream>
#include <queue>
#include <forward_list>
using namespace std;

struct vertex
{
    bool visited = false;
    int distance = -1;
    forward_list<int> graph;
};

int bfs(vertex *verts, int n)
{
    queue<int> queue;

    int vert = 0;
    verts[vert].visited = true;
    verts[vert].distance = 0;
    queue.push(vert);

    int comp;

    while (!queue.empty())
    {
        vert = queue.front();
        queue.pop();

        while (!verts[vert].graph.empty())
        {
            comp = verts[vert].graph.front();
            verts[vert].graph.pop_front();

            if (!verts[comp].visited)
            {
                verts[comp].visited = true;
                verts[comp].distance = verts[vert].distance + 1;
                queue.push(comp);
            }

        }

    }

    return 0;
}

int main()
{
    ifstream input("pathbge1.in");
    ofstream output("pathbge1.out");

    int m, n;
    input >> n >> m;
    vertex verts[n];

    int i, j;

    for (int k = 0; k < m; k++)
    {
        input >> i >> j;
        verts[i - 1].graph.push_front(j - 1);

        if (i != j)
            verts[j - 1].graph.push_front(i - 1);
    }

    bfs(verts, n);

    for (int k = 0; k < n; k++)
        output << verts[k].distance << " ";

    input.close();
    output.close();

    return 0;
}
