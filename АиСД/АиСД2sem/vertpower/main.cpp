#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream in;
    ofstream out;

    in.open("input.txt");
    out.open("output.txt");

    int tops, edges;

    in >> tops >> edges;

    vector<vector<int>> graph;

    graph.resize(tops);

    int top1, top2;

    for (int i = 0; i < edges; i++)
    {
        in >> top1 >> top2;
        graph[top1 - 1].push_back(top2);
        graph[top2 - 1].push_back(top1);
    }

    for (int i = 0; i < tops; i++)
        out << graph[i].size() << " ";

    return 0;
}