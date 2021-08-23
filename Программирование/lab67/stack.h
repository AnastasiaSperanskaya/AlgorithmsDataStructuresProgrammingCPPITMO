#ifndef LAB67_STACK_H
#define LAB67_STACK_H

#include <stdexcept>
using namespace std;

class stack_exception : public logic_error {
public:
    explicit stack_exception(const char* message):logic_error(message) {}
};

class stack_is_empty : public stack_exception {
public:
    explicit stack_is_empty() : stack_exception("Stack is empty") {}
};

class stack_limit_reached : public stack_exception {
public:
    explicit stack_limit_reached() : stack_exception("Stack limit reached") {}
};

template <typename T>
class Stack
{
private:
    T *stackPtr;
    const int size;
    int top;

public:
    Stack(int = 10);

    void push(const T &value)
    {
        if(top >= size)
            throw stack_limit_reached();

        stackPtr[top++] = value;
    }

    T pop()
    {
        if(top == 0)
            throw stack_is_empty();

        stackPtr[--top];
    }

    void printStack()
    {
        for (int ix = top - 1; ix >= 0; ix--)
            cout << stackPtr[ix] << endl;
    }
};

template <typename T>
Stack<T>::Stack(int maxSize) :
        size(maxSize)
{
    stackPtr = new T[size];
    top = 0;
}

#endif //LAB67_STACK_H
