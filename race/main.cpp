#include <fstream>
#include <string>
#include <vector>
using namespace std;

void merge(vector<string> &countries, vector<string> &surnames, int left, int middle, int right)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    vector<string> Lcountries;
    vector<string> Lsurnames;
    vector<string> Rcountries;
    vector<string> Rsurnames;
    for (i = 0; i < n1; i++)
    {
        Lcountries.push_back( countries[left + i] );
        Lsurnames.push_back( surnames[left + i] );
    }
    for (j = 0; j < n2; j++)
    {
        Rcountries.push_back( countries[middle + 1 + j] );
        Rsurnames.push_back( surnames[middle + 1 + j] );
    }

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (Lcountries[i] <= Rcountries[j])
        {
            countries[k] = Lcountries[i];
            surnames[k] = Lsurnames[i];
            k++;
            i++;
        }
        else
        {
            countries[k] = Rcountries[j];
            surnames[k] = Rsurnames[j];
            k++;
            j++;
        }
    }

    while (i < n1)
    {
        countries[k] = Lcountries[i];
        surnames[k] = Lsurnames[i];
        k++;
        i++;
    }
    while (j < n2)
    {
        countries[k] = Rcountries[j];
        surnames[k] = Rsurnames[j];
        k++;
        j++;
    }
}

void mergeSort(vector<string> &countries, vector<string> &surnames, int left, int right)
{
    if (right > left)
    {
        int middle = (right + left) / 2;
        mergeSort(countries, surnames, left, middle);
        mergeSort(countries, surnames, middle + 1, right);

        merge(countries, surnames, left, middle, right);
    }
}
int main()
{
    vector<string> arrOfSurnamesRunners;
    vector<string> arrOfCountriesRunners;
    fstream fs;

    fs.open("race.in", fstream::in);
    string surname;
    string country;
    int size;
    fs >> size;
    for (int i = 0; i < size; ++i)
    {
        fs >> country;
        arrOfCountriesRunners.push_back(country);

        fs >> surname;
        arrOfSurnamesRunners.push_back(surname);
    }

    fs.close();

    mergeSort(arrOfCountriesRunners, arrOfSurnamesRunners, 0, arrOfCountriesRunners.size() - 1);

    fs.open("race.out", fstream::out);
    for (int i = 0; i < size; i++)
    {
        if (i == 0)
        {
            fs << "=== " << arrOfCountriesRunners[i] << " ===" << endl;
            fs << arrOfSurnamesRunners[i] << endl;
        }
        else if (arrOfCountriesRunners[i] == arrOfCountriesRunners[i - 1])
        {
            fs << arrOfSurnamesRunners[i] << endl;
        }
        else
        {
            fs << "=== " << arrOfCountriesRunners[i] << " ===" << endl;
            fs << arrOfSurnamesRunners[i] << endl;
        }
    }
    fs.close();



    return 0;
}