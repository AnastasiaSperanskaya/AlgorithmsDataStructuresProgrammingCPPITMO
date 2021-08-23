#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

struct vertex;

struct graph_node
{
    graph_node * next = nullptr;
    vertex * vert = nullptr;
};

struct vertex
{
    int color = 0; // 0 - white; 1 - grey; 2 - black
    int distance = -1;
    int components = 0;
    bool visited = false;
    int degree = 0;
    graph_node * graph_first = nullptr;
    vertex * parent = nullptr;
};

void graph_add(vertex * verts, int i, int j)
{
    verts[i].degree++;
    verts[j].degree++;

    graph_node * node = verts[i].graph_first;

    while(node != nullptr && node->next != nullptr)
        node = node->next;

    if (node == nullptr)
    {
        verts[i].graph_first = new graph_node;
        verts[i].graph_first->vert = &verts[j];
    }
    else
    {
        node->next = new graph_node;
        node->next->vert = &verts[j];
    }

    if (i != j)
    {
        node = verts[j].graph_first;

        while (node != nullptr && node->next != nullptr)
            node = node->next;

        if (node == nullptr)
        {
            verts[j].graph_first = new graph_node;
            verts[j].graph_first->vert = &verts[i];
        }
        else
        {
            node->next = new graph_node;
            node->next->vert = &verts[i];
        }
    }

}

int bfs(vertex * verts, int n)
{
    queue<vertex *> queue;

    int components = 1;

    for (int k = 0; k < n; k++)
    {
        if (verts[k].color != 0)
            continue;

        vertex * vert = &verts[k];
        vert->color = 1;
        vert->parent = nullptr;
        vert->distance = 0;
        vert->components = components++;

        queue.push(vert);

        graph_node * node;
        vertex * comp_vert;

        while (!queue.empty())
        {
            vert = queue.front();
            queue.pop();

            node = vert->graph_first;

            while (node != nullptr)
            {
                comp_vert = node->vert;

                if (comp_vert->color == 0)
                {
                    comp_vert->color = 1;
                    comp_vert->distance = vert->distance + 1;
                    comp_vert->parent = vert;
                    comp_vert->components = vert->components;
                    queue.push(comp_vert);
                }

                node = node->next;
            }

            vert->color = 2;
        }


    }

    return components - 1;
}

int main()
{
    ifstream input("components.in");
    ofstream output("components.out");

    int m, n;
    input >> n >> m;
    vertex verts[n];

    int i, j;

    for (int k = 0; k < m; k++)
    {
        input >> i >> j;
        graph_add(verts, i - 1, j - 1);
    }

    output << bfs(verts, n) << endl;

    for (int k = 0; k < n; k++)
        output << verts[k].components << " ";

    input.close();
    output.close();
    return 0;
}

