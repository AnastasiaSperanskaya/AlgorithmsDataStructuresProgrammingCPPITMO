#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<int> PrefixFunction(string &sum_of_t_p, vector<int> &pref_func)
{
	pref_func[0] = 0;

	for (int i = 1; i <= sum_of_t_p.size() - 1; i++)
	{
		int k = pref_func[i - 1];

		while (k > 0 && sum_of_t_p[i] != sum_of_t_p[k])
			k = pref_func[k - 1];

		if (sum_of_t_p[i] == sum_of_t_p[k])
			k++;

		pref_func[i] = k;

	}

	return pref_func;
}

vector<int> KnuthMorrisPratt(string &pattern, string &text, string &sum_of_t_p, vector<int> &pref_func)
{
	int p_size = pattern.size();
	int t_size = text.size();

	vector<int> pf = PrefixFunction(sum_of_t_p, pref_func);
	vector<int> res;
	int count = 0;

	for (int i = 0; i <= t_size - 1; i++)
		if (pf[p_size + i + 1] == p_size)
		{
			res.resize(count + 1);
			res[count++] = i - p_size + 2;
		}
	return res;
}

int main()
{
	ifstream in("search2.in");
    ofstream out("search2.out");

	string text, pattern, sum_of_t_p;
	in >> pattern >> text;

	string symbol = "#";
	sum_of_t_p = pattern + symbol + text;

	int s_of_t_p_size = sum_of_t_p.size();

	vector<int> pref_func(s_of_t_p_size);

	vector<int> result = KnuthMorrisPratt(pattern, text, sum_of_t_p, pref_func);

	int r_size = result.size();

	out << r_size << "\n";

	for (int i = 0; i < r_size; i++)
		out << result[i] << ' ';

	out.close();
    in.close();
	return 0;
}