#include <vector>
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

class CustomVector{

private:
    double x,y;

public:
    CustomVector(double _x, double _y): x(_x), y(_y){}

    double len()
    {
        return sqrt(x * x + y * y);
    }

    bool operator==(const CustomVector &b)
    {
        return x == b.x && y == b.y;
    }

    string to_string()
    {
        ostringstream ss;
        ss << "CustomVector (" << x << ", " << y << ")";
        return ss.str();
    }

};

template<class C>
class Predicate {
public:
    bool operator()(C &collection, typename C::iterator it) = 0;
};

template<class C>
class Comparator {
public:
    int operator()(C &collection, typename C::iterator a, typename C::iteratorb) = 0;
};

template <class T, class Condition>
bool none_of(T &collection, Condition test)
{
    for(typename T::iterator it = collection.begin(); it != collection.end(); it++)
        if(test(*it))
            return false;

    return true;
}

template <class T, class Comparator>
bool is_sorted(T &collection, Comparator comparator)
{
    for(typename T::iterator it = collection.begin(); it + 1 != collection.end(); it++)
        if(comparator(*it, *(it + 1)) > 0)
            return false;

    return true;
}


template <class T>
typename T::iterator find_not(T &collection, typename T::value_type val)
{
    for(typename T::iterator it = collection.begin(); it != collection.end(); it++)
        if(!(*it == val))
            return it;

    return collection.end();
}

int main()
{
    vector<int> v;

    v.push_back(3);
    v.push_back(5);
    v.push_back(7);

    cout << "On vector: " << endl;
    cout << none_of(v, [](int i){ return i % 2 == 0; }) << endl;
    cout << is_sorted(v, [](int a, int b){ return a - b; }) << endl;
    cout << *find_not(v, 5) << endl;

    vector<CustomVector> p;

    p.push_back(CustomVector(0, 0));
    p.push_back(CustomVector(100, 100));
    p.push_back(CustomVector(20, 20));

    cout << "On custom vector: " << endl;
    cout << none_of(p, [](CustomVector vec){ return vec.len() == 0.0; }) << endl;
    cout << is_sorted(p, [](CustomVector a, CustomVector b){ return a.len() - b.len(); }) << endl;
    cout << find_not(p, CustomVector(0, 0))->to_string() << endl;

    return 0;
}