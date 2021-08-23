#include <iostream>
#include <fstream>
#include <forward_list>
#include <queue>
#include <string>
using namespace std;

struct vertex
{
    bool visited = false;
    bool finish = false;
    int x, y;
    string way = "";
    int distance = -1;
};

vertex * bfs(vertex ** map, int x, int y, int n, int m)
{
    vertex * start = &map[x][y];
    bool finish_found = false;
    queue<vertex *> queue;

    start->distance = 0;
    start->visited = true;
    start->way = "";
    queue.push(start);
    vertex * vert = nullptr;

    int count = 0;

    while(!queue.empty())
    {
        count++;
        vert = queue.front();
        queue.pop();

        if (vert->finish)
        {
            finish_found = true;
            break;
        }

        if (vert->x > 0 && !map[vert->x - 1][vert->y].visited)
        {
            queue.push(&map[vert->x - 1][vert->y]);
            map[vert->x - 1][vert->y].visited = true;
            map[vert->x - 1][vert->y].distance = vert->distance + 1;
            map[vert->x - 1][vert->y].way = vert->way + "L";
        }

        if (vert->x < (m - 1) && !map[vert->x + 1][vert->y].visited)
        {
            queue.push(&map[vert->x + 1][vert->y]);
            map[vert->x + 1][vert->y].visited = true;
            map[vert->x + 1][vert->y].distance = vert->distance + 1;
            map[vert->x + 1][vert->y].way = vert->way + "R";
        }

        if (vert->y > 0 && !map[vert->x][vert->y - 1].visited)
        {
            queue.push(&map[vert->x][vert->y - 1]);
            map[vert->x][vert->y - 1].visited = true;
            map[vert->x][vert->y - 1].distance = vert->distance + 1;
            map[vert->x][vert->y - 1].way = vert->way + "U";
        }

        if (vert->y < (n - 1) && !map[vert->x][vert->y + 1].visited)
        {
            queue.push(&map[vert->x][vert->y + 1]);
            map[vert->x][vert->y + 1].visited = true;
            map[vert->x][vert->y + 1].distance = vert->distance + 1;
            map[vert->x][vert->y + 1].way = vert->way + "D";
        }

    }

    if (finish_found)
        return vert;
    else
        return nullptr;

}

int main()
{
    ifstream input("input.txt");
    ofstream output("output.txt");

    int n, m;
    input >> n >> m;

    vertex ** map = new vertex * [m];

    for (int k = 0; k < m; k++)
        map[k] = new vertex[n];

    char ch;
    int x, y;

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < m; i++)
        {
            input >> ch;

            map[i][j].x = i;
            map[i][j].y = j;

            if (ch == '#')
                map[i][j].visited = true;
            else if (ch == 'S')
            {
                x = i;
                y = j;
            }
            else if (ch == 'T')
                map[i][j].finish = true;
        }
    }

    vertex * vert = bfs(map, x, y, n, m);

    if (vert != nullptr && vert->finish)
    {
        output << vert->distance << endl;
        output << vert->way;
    }
    else
        output << -1;

    input.close();
    output.close();

    return 0;
}
