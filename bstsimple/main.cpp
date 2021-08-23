#define strsize 20
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct vershina
{
	long long value = 0;
	vershina *parent = nullptr;
	vershina *left = nullptr;
	vershina *right = nullptr;
} V;

int tree_size = 0;

void insert_key(V *tree, long long value)
{
    if (tree_size <= 0)
    {
        tree->value = value;
        tree_size = 1;
        return;
    }

    if (value < tree->value && tree->left == nullptr)
    {
        tree->left = new V;
        tree->left->value = value;
        tree->left->parent = tree;
        tree_size++;
        return;
    }

    if (value > tree->value && tree->right == nullptr)
    {
        tree->right = new V;
        tree->right->value = value;
        tree->right->parent = tree;
        tree_size++;
        return;
    }

    V *parent = nullptr;
    V *vert = tree;

    while (vert != nullptr)
    {
        if (value < vert->value)
        {
            parent = vert;
            vert = vert->left;
        }

        else if (value > vert->value)
        {
            parent = vert;
            vert = vert->right;
        }
        else return;
    }

    vert = new V;
    vert->value = value;
    vert->parent = parent;

    if (value < parent->value)
        parent->left = vert;
    else parent->right = vert;

    tree_size++;
}

bool exists_key(V *tree, long long value)
{
    if (tree_size <= 0)
        return false;

    if (value == tree->value)
        return true;

    V *vert = tree;

    while (vert != nullptr)
    {
        if (value < vert->value)
            vert = vert->left;

        else if (value > vert->value)
            vert = vert->right;

        else return true;
    }

    return false;
}

void delete_key(V *tree, long long value);

void delete_root(V *tree)
{
    V *vert = tree;

    if (tree_size <= 0)
        return;

    if (vert->left == nullptr && vert->right == nullptr)
    {
        tree_size = 0;
        return;
    }

    if (tree_size == 1)
    {
        tree_size = 0;
        return;
    }

    if (vert->left != nullptr && vert->right != nullptr)
    {
        V *swap = vert->right;

        while (swap->left != nullptr)
            swap = swap->left;

        long long tmp = swap->value;

        delete_key(tree, swap->value);

        vert->value = tmp;

        return;
    }

    V *change;

    if (vert->left != nullptr)
        change = vert->left;

    else
        change = vert->right;

    *tree = *change;

    if (change->left != NULL)
        change->left->parent = tree;

    if (change->right != NULL)
        change->right->parent = tree;

    tree_size--;
    delete change;
}

void delete_key(V *tree, long long value)
{
    if (tree_size <= 0)
        return;

    if (tree->value == value)
    {
        delete_root(tree);
        return;
    }

    V *vert = tree;

    while (vert != nullptr)
    {
        if (value < vert->value)
            vert = vert->left;
        else if (value > vert->value)
            vert = vert->right;
        else break;
    }

    if (vert == nullptr)
        return;

    if (vert->left == nullptr && vert->right == nullptr)
    {
        if (vert->parent->left == vert)
            vert->parent->left = nullptr;
        else vert->parent->right = nullptr;
        delete vert;
        tree_size--;
    }

    else if (vert->left != nullptr && vert->right != nullptr)
    {
        V *swap = vert->right;
        while (swap->left != nullptr)
            swap = swap->left;

        long long tmp = swap->value;
        delete_key(tree, swap->value);
        vert->value = tmp;
    }

    else
    {
        V *change;
        if (vert->left != nullptr)
            change = vert->left;
        else
            change = vert->right;

        if (vert->parent->left == vert)
            vert->parent->left = change;
        else
            vert->parent->right = change;

        change->parent = vert->parent;

        delete vert;

        tree_size--;
    }
}

V *next_key(V *tree, long long cur_value)
{
    if (tree_size <= 0)
        return nullptr;

    if (tree_size == 1)
    {
        if (cur_value < tree->value)
            return tree;
        else return nullptr;
    }

    V *vert = tree;

    while (vert != nullptr)
    {
        if (cur_value < vert->value)
            if (vert->left != nullptr)
                vert = vert->left;
            else break;

        else if (cur_value > vert->value)
            if (vert->right != nullptr)
                vert = vert->right;
            else break;

        else break;
    }

    if (vert == nullptr)
        return nullptr;

    if (cur_value < vert->value)
        return vert;

    if (vert->right != nullptr)
    {
        vert = vert->right;
        while (vert->left != nullptr)
            vert = vert->left;
        return vert;
    }

    V *check = vert;
    V *parent = vert->parent;

    while (true)
    {
        if (parent == nullptr)
            return nullptr;

        else if (check == parent->right)
        {
            check = parent;
            parent = parent->parent;
        }

        else if (check == parent->left)
            return parent;

        else return nullptr;
    }
}

V *prev_key(V *tree, long long cur_value)
{
    if (tree_size <= 0)
        return nullptr;

    if (tree_size == 1)
    {
        if (cur_value > tree->value)
            return tree;
        else return nullptr;
    }

    V *vert = tree;

    while (vert != nullptr)
    {
        if (cur_value < vert->value)
            if (vert->left != nullptr)
                vert = vert->left;
            else break;

        else if (cur_value > vert->value)
            if (vert->right != nullptr)
                vert = vert->right;
            else break;

        else break;
    }

    if (vert == nullptr)
        return nullptr;

    if (cur_value > vert->value)
        return vert;

    if (vert->left != nullptr)
    {
        vert = vert->left;

        while (vert->right != nullptr)
            vert = vert->right;

        return vert;
    }

    V *check = vert;
    V *parent = vert->parent;

    while (true)
    {
        if (parent == nullptr)
            return nullptr;

        else if (check == parent->left)
        {
            check = parent;
            parent = parent->parent;
        }
        else if (check == parent->right)
            return parent;

        else return nullptr;
    }
}

int main()
{
	FILE *in = fopen("bstsimple.in", "r");
	FILE *out = fopen("bstsimple.out", "w");

	V tree;
	char command[strsize];
	char arg[strsize];
	char *pEnd;
	long long current_value;
	V *check = nullptr;

	fscanf(in, "%s", command);
	fscanf(in, "%s", arg);
	current_value = strtoll(arg, &pEnd, 10);

	while (true)
	{
		if (strcmp(command, "insert") == 0)
			insert_key(&tree, current_value);

		else if (strcmp(command, "exists") == 0)
			if (exists_key(&tree, current_value))
				fprintf(out, "true\n");
			else fprintf(out, "false\n");

		else if (strcmp(command, "delete") == 0)
			delete_key(&tree, current_value);

		else if (strcmp(command, "next") == 0)
		{
			check = next_key(&tree, current_value);
			if (check != nullptr)
				fprintf(out, "%lld\n", check->value);
			else fprintf(out, "none\n");
		}

		else if (strcmp(command, "prev") == 0)
		{
			check = prev_key(&tree, current_value);
			if (check != nullptr)
				fprintf(out, "%lld\n", check->value);
			else fprintf(out, "none\n");
		}

		if (feof(in))
			break;

		strcpy(command, "");
		fscanf(in, "%s", command);
		fscanf(in, "%s", arg);
        current_value = strtoll(arg, &pEnd, 10);
	}

	fclose(in);
	fclose(out);
	return 0;
}

