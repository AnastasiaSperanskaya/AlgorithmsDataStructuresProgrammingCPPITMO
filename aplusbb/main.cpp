#include <iostream>
#include <fstream>

int main()
{
    std::ifstream fin("aplusbb.in");
    std::ofstream fout("aplusbb.out");
    long long a, b;
    fin >> a >> b;
    fout << a + b*b << std::endl;
    return 0;
}