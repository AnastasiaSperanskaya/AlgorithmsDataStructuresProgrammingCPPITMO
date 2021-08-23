#include<iostream>
#include <fstream>
using namespace std;

class queue
{
private:
    int head;
    int tail;
    int *elements;

public:

    queue(int n)
        {
            elements = new int[n];
            head = n;
            tail = head - 1;

        }


    void push(int a)
        {
            elements[tail] = a;
            if(tail != 0)
                --tail;

        }

    int pop()
        {
            if(head != tail)
                return elements[--head];
            else
                return -1;
        }

};

int main()
{
    ifstream fin("queue.in");
    ofstream fout("queue.out");

    int n;

    fin >> n;

    queue my_queue(n);

    char operations;
    int var;

    for(int i=0; i < n; i++)
    {
        fin >> operations;

        if(operations == '+')
        {
            fin >> var;
            my_queue.push(var);
        }

        if(operations == '-')
        {
            fout << my_queue.pop() << endl;
        }
    }



}
