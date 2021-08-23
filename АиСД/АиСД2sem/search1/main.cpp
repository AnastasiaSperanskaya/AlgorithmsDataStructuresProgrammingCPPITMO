#include <fstream>
#include <string>
#include <vector>

using namespace std;

void NativeStringMatcher(string &t, string &p, vector<int> &result)
{
    int t_size = t.size();
    int p_size = p.size();

    for (int i = 0; i < t_size - p_size + 1; ++i)
    {
        bool check = true;

        for (int j = 0; j < p_size && check; ++j)
            if (t[i + j] != p[j])
            {
                check = false;
                break;
            }
        if (check)
            result.push_back(i);
    }
}

int main()
{

    ifstream in("search1.in");
    ofstream out("search1.out");

    string p, t;
    in >> p >> t;

    vector<int> result;

    NativeStringMatcher(t, p, result);
    int r_size = result.size();

    out << r_size << '\n';

    for (int i = 0; i < r_size; i++)
        out << result[i] + 1 << ' ';

    out.close();
    in.close();
    return 0;
}