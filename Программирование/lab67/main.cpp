#include <iostream>
#include "stack.h"

using namespace std;

template <typename T, int M>
T pow(T* a){
    T t = *a;
    for(int i = 1; i < M; i++)
        t *= *a;
    return t;
}

int main()
{

    int a = 5;

    cout << pow<int, 4>(&a) << endl << endl;

    Stack<int> s(3);

    s.printStack();
    try {
        s.push(5);
        s.push(3);
        s.push(2);
        s.push(1);
    } catch(stack_exception& e){
        cout << e.what() << endl;
    }

    try {
        for(int i = 0; i < 5; i++)
            s.pop();
    } catch(stack_exception& e){
        cout << e.what() << endl;
    }

    return 0;
}