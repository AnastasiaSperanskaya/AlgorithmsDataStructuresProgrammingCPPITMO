#define arrsize 100000
#define limit 65535
#include  <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

typedef struct label_node
{
	string name;
	int pos;
	label_node *next = nullptr;
} label_node;

typedef struct labels
{
	label_node *first = nullptr;
	label_node *last = nullptr;
} labels;

typedef struct register_node
{
	register_node *next = nullptr;
	char name;
	int val;
} register_node;

typedef struct registers
{
	register_node *first = nullptr;
	register_node *last = nullptr;
} registers;

typedef struct queue_node
{
	int val;
	queue_node *next = nullptr;
} queue_node;

typedef struct queue {
	queue_node *first = nullptr;
	queue_node *last = nullptr;
	int size = 0;
} queue;

void label_put(string name, int position, labels *label_list);
int label_pos_get(string name, labels *label_list);
void register_put(char name, registers *reg_list);
void register_val_put(char name, int val, registers *reg_list);
int register_val_get(char name, registers *reg_list);
void queue_put(queue *q, int val);
int queue_get(queue *q);

int main()
{
	ifstream in("quack.in");
	ofstream out("quack.out");

	string *arr = new string[arrsize];

	queue que;
	labels label_list;
	registers register_list;

	int pos = 0;

	while (!in.eof())
		in >> arr[pos++];
	int data_size = pos;

	for (char name = 'a'; name <= 'z'; name++)
		register_put(name, &register_list);

	pos = 0;
	string buffer;

	int x, y, register_value1, register_value2, number;
	char c, *pEnd;
	int value;

	while (pos < data_size)
	{
		buffer = arr[pos++];

		if (buffer == "")
			continue;

		if (buffer[0] == ':')
			label_put(buffer.substr(1, buffer.length() - 1), pos, &label_list);
	}

	pos = 0;

	while (pos < data_size)
	{
		buffer = arr[pos++];

		if (buffer == "")
			continue;

		if (buffer == "+")
		{
			number = queue_get(&que) + queue_get(&que);
			queue_put(&que, number);
		}

		else if (buffer == "-")
		{
			number = queue_get(&que) - queue_get(&que);
			queue_put(&que, number);
		}

		else if (buffer == "*")
		{
			number = queue_get(&que) *queue_get(&que);
			queue_put(&que, number);
		}

		else if (buffer == "/")
		{
			x = queue_get(&que);
			y = queue_get(&que);

			if (y == 0)
				number = 0;

			else number = x / y;

			queue_put(&que, number);
		}

		else if (buffer == "%")
		{
			x = queue_get(&que);
			y = queue_get(&que);

			if (y == 0)
				number = 0;

			else number = x % y;

			queue_put(&que, number);
		}

		else if (buffer[0] == '>')
			register_val_put(buffer[1], queue_get(&que), &register_list);

		else if (buffer[0] == '<')
			queue_put(&que, register_val_get(buffer[1], &register_list));

		else if (buffer == "P")
			out << queue_get(&que) << endl;

		else if (buffer[0] == 'P')
			out << register_val_get(buffer[1], &register_list) << endl;

		else if (buffer == "C")
			out << (char)(queue_get(&que) % 256);

		else if (buffer[0] == 'C')
			out << (char)(register_val_get(buffer[1], &register_list) % 256);

		else if (buffer[0] == ':');

		else if (buffer[0] == 'J')
			pos = label_pos_get(buffer.substr(1, buffer.length() - 1), &label_list);

		else if (buffer[0] == 'Z')
		{
			register_value1 = register_val_get(buffer[1], &register_list);
			if (register_value1 == 0)
				pos = label_pos_get(buffer.substr(2, buffer.length() - 2), &label_list);
		}

		else if (buffer[0] == 'E')
		{
			register_value1 = register_val_get(buffer[1], &register_list);
			register_value2 = register_val_get(buffer[2], &register_list);
			if (register_value1 == register_value2)
				pos = label_pos_get(buffer.substr(3, buffer.length() - 3), &label_list);
		}

		else if (buffer[0] == 'G')
		{
			register_value1 = register_val_get(buffer[1], &register_list);
			register_value2 = register_val_get(buffer[2], &register_list);
			if (register_value1 > register_value2)
				pos = label_pos_get(buffer.substr(3, buffer.length() - 3), &label_list);
		}

		else if (buffer == "Q")
			break;

		else
		{
			number = stoi(buffer);
			queue_put(&que, number);
		}
	}

}

void register_put(char name, registers *reg_list)
{
	if (reg_list->first == nullptr)
	{
		reg_list->first = new register_node;
		reg_list->last = reg_list->first;
		reg_list->first->name = name;
		reg_list->first->val = 0;
		return;
	}

	register_node *last_node = reg_list->last;
	last_node->next = new register_node;
	reg_list->last = last_node->next;
	last_node->next->name = name;
	last_node->next->val = 0;
}

void label_put(string name, int position, labels *label_list)
{
	if (label_list->first == nullptr)
	{
		label_list->first = new label_node;
		label_list->last = label_list->first;
		label_list->first->name = name;
		label_list->first->pos = position;
		return;
	}

	label_node *last_node = label_list->last;
	last_node->next = new label_node;
	label_list->last = last_node->next;
	last_node->next->name = name;
	last_node->next->pos = position;

}

int label_pos_get(string name, labels *label_list)
{
	label_node *node = label_list->first;

	while (node->name != name)
		node = node->next;

	return node->pos;
}

void register_val_put(char name, int val, registers *reg_list)
{
	val = val & limit;
	register_node *node = reg_list->first;

	while (node->name != name)
		node = node->next;

	node->val = val;
}

int register_val_get(char name, registers *reg_list)
{
	register_node *node = reg_list->first;

	while (node->name != name)
		node = node->next;

	return node->val & limit;
}

int queue_get(queue *q)
{
	int val;

	if (q->size == 1)
	{
		val = q->first->val;
		delete q->first;
		q->first = nullptr;
		q->last = nullptr;
		q->size = 0;
		return val & limit;
	}

	val = q->first->val;
	queue_node *change = q->first->next;
	delete q->first;
	q->first = change;

	if (q->size == 2)
		q->last = change;

	q->size--;

	return val & limit;
}

void queue_put(queue *q, int val)
{
	val = val & limit;

	if (q->size == 0)
	{
		q->first = new queue_node;
		q->first->val = val;
		q->last = q->first;
		q->size = 1;
		return;
	}

	queue_node *last = q->last;
	last->next = new queue_node;
	last->next->val = val;
	q->last = last->next;
	q->size++;
}