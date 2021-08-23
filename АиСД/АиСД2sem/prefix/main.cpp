#include <fstream>
#include <string>
#include <vector>

using namespace std;

void PrefixFunction(string &s, vector<int> &result)
{
	result[0] = 0;

	for (int i = 1; i <= s.size() - 1; i++)
	{
		int k = result[i - 1];

		while (k > 0 && s[i] != s[k])
			k = result[k - 1];

		if (s[i] == s[k])
			k++;

		result[i] = k;
	}
}

int main()
{
	ifstream in("prefix.in");
    ofstream out("prefix.out");

	string s;
	in >> s;
	int size = s.size();

	vector <int> result(size);
	int r_size = result.size();

	PrefixFunction(s, result);

	for (int i = 0; i < r_size; i++)
		out << result[i] << " ";

	out.close();
    in.close();
	return 0;
}