#include <iostream>
#include<fstream>
#include<cstring>

using namespace std;

int main()
{
    ifstream fin("/Users/anastasia/Desktop/CLionProjects/draft(1)/file.in.txt");
    ofstream fout("/Users/anastasia/Desktop/CLionProjects/draft(1)/file.out.txt");

    string s;
    fin >> s;

    while(!fin.eof())
    {
        fout << s << endl;
        fin >> s;
    }

    return 0;
}