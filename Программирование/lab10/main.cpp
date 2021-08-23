#include <iostream>
#include <stack>
#include "tets.h"
using namespace std;

int main() {
    AVLTree<int> tree;
    cout << "Insert element: " << *tree.insert(3) << '\n';
    cout << "Insert element: " << *tree.insert(5) << '\n';
    cout << "Insert element: " << *tree.insert(7) << '\n';
    cout << "Insert element: " << *tree.insert(8) << '\n';
    cout << "First element: " << *tree.begin() << '\n';
    cout << "Second element: " << *tree.begin()++ << '\n';
    cout << "Last element: " << *tree.end() << '\n';
    cout << "Find element: " << *tree.find(5) << '\n';
    cout << "Tree size: " << tree.size() << '\n';
    cout << "Is Empty: " << tree.empty() << '\n';

    for (btIter<int> i = tree.begin(); i != (tree.begin()++)++; i++)
    {
        cout << *i << '\n';
    }

    return 0;
}
