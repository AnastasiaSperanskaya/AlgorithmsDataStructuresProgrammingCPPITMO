#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Stack {
public:

    Stack() {
        size = 10;
        it = 0;
        data = new char[size];
    }

    ~Stack()
    {
        delete[] data;
    }

    void push_back(int Value) {
        if (it == size) {
            resize();
        }
        data[it] = Value;
        ++it;
    }

    char eraseAndGet() {
        int temp = data[--it];
        return temp;
    }

    char GetLast() {
        return data[it - 1];
    }

    void resize()
    {
        size = 2 * size;
        char *temp = new char[size];
        for (int i = 0; i < it; ++i)
        {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }

    bool checkEmpty() {
        if (it == 0)
        {
            return true;
        }
        else {
            return false;
        }
    }

private:
    char* data;
    int it;
    int size;
};


int main() {


    ifstream FIN("brackets.in");
    string string1;
    ofstream FOUT("brackets.out");

    while (getline(FIN, string1)) {
        Stack stack;
        bool check = 1;
        for (int i = 0; i < string1.size(); ++i) {
            if ((string1[i] == ')' || string1[i] == ']') && !stack.checkEmpty()) {
                if ((string1[i] == ')' && stack.GetLast() == '(') || (string1[i] == ']' && stack.GetLast() == '[')) {
                    stack.eraseAndGet();
                    continue;
                }
                else {
                    check = 0;
                    break;
                }
            }
            else {
                stack.push_back(string1[i]);
            }
        }
        if (check && stack.checkEmpty()) {
            FOUT << "YES\n";
        }
        else {
            FOUT << "NO\n";
        }
    }

    FIN.close();
    FOUT.close();
    return 0;
}