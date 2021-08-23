#include <fstream>
#include <vector>
#include <iomanip>
#include <float.h>
#include <cmath>
using namespace std;

class Node
{
public:
    int x, y;

    double m = DBL_MAX;

    bool isVisited = false;

    bool operator == (Node &g)
    {
        if (this -> x == g.x && this -> y == g.y && this -> m == g.m)
            return true;
        else
            return false;
    }
};

double getDistance(Node v, Node g)
{
    int newx = g.x - v.x;
    int newy = g.y - v.y;
    return (double)sqrt(newx * newx + newy * newy);
}

int main()
{
    ofstream out;
    ifstream in;

    in.open("spantree.in");
    out.open("spantree.out");
    int tops;

    in >> tops;

    vector<Node> nodes;
    nodes.resize(tops);

    for (int i = 0; i < tops; i++)
        in >> nodes[i].x >> nodes[i].y;

    nodes[0].m = 0;
    nodes[0].isVisited = true;

    for (int i = 1; i < tops; i++)
    {
        Node tempNode = nodes[i];
        nodes[i].m = getDistance(nodes[0], tempNode);
    }

    int indexOfVisited;

    for (int i = 1; i < tops - 1; i++)
    {
        Node *v = nullptr;

        for (int j = 0; j < tops; j++)
        {
            Node g = nodes[j];
            if (!g.isVisited && (v == nullptr || g.m < v -> m))
            {
                if(v == nullptr) v = new Node();
                v -> x = g.x;
                v -> y = g.y;
                v -> m = g.m;
                indexOfVisited = j;
            }
        }

        nodes[indexOfVisited].isVisited = true;
        v -> isVisited = true;

        for (int j = 0; j < tops; j++)
        {
            Node g = nodes[j];

            if (g == *v || g.isVisited)
                continue;

            double d = getDistance(*v, g);

            if (d < g.m)
                nodes[j].m = d;
        }
    }

    double s = 0;

    for (int i = 0; i < nodes.size(); i++)
        s += nodes[i].m;

    out << setprecision(20) << (double)s;

    return 0;
}