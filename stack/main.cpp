#include<iostream>
#include <fstream>
using namespace std;

class stack
{
private:
	int top = 0;
	int *elements;

public:

	stack(const int size)
	{
		elements = new int[size];
	}

	void push(const int number)
	{
		elements[top++] = number;
	}

	int pop()
	{
		return elements[--top];
	}

	~stack()
	{
		delete[] elements;
	}
};

int main()
{
	int size;
	int var;
	char command;

    ifstream fin("stack.in");
    ofstream fout("stack.out");

	fin >> size;

	stack my_stack(size);

	for (int i = 0; i < size; i++)
	{
		fin >> command;

		if (command == '+')
		{
			fin >> var;
			my_stack.push(var);
		}
		else if (command == '-' && i > 0)
		{
			fout << my_stack.pop() << endl;
		}
	}


	return 0;
}