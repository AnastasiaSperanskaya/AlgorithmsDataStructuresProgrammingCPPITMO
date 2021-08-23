#include <stdio.h>
#include <limits.h>

typedef struct vershina
{
    long long value = 0;
    int left = 0;
    int right = 0;
} V;

bool check_v(V *arr, int cur, long long min, long long max)
{
    if (arr[cur].value <= min)
        return false;

    if (arr[cur].value >= max)
        return false;

    if (arr[cur].left > 0)
        if (!check_v(arr, arr[cur].left, min, arr[cur].value))
            return false;

    if (arr[cur].right > 0)
        if (!check_v(arr, arr[cur].right, arr[cur].value, max))
            return false;

    return true;
}

bool is_tree(V *arr)
{
    if (arr[0].left > 0)
        if (!check_v(arr, arr[0].left, LLONG_MIN, arr[0].value))
            return false;

    if (arr[0].right > 0)
        if (!check_v(arr, arr[0].right, arr[0].value, LLONG_MAX))
            return false;

    return true;
}

int main()
{
    int tree_size;

    FILE * in = fopen("check.in", "r");
    FILE *  out = fopen("check.out", "w");

    fscanf(in, "%d", &tree_size);
    if (tree_size < 2)
        fprintf(out, "YES");
    else
    {
        V *arr = new V[tree_size];

        int left, right;
        long long value;

        fscanf(in, "%lld %d %d", &value, &left, &right);

        arr[0].value = value;
        arr[0].left = left - 1;
        arr[0].right = right - 1;

        for (int current = 1; current < tree_size; current++)
        {
            fscanf(in, "%lld %d %d", &value, &left, &right);
            right--;
            left--;

            arr[current].right = right;
            arr[current].left = left;
            arr[current].value = value;
        }

        if (!is_tree(arr))
            fprintf(out, "NO");
        else
            fprintf(out, "YES");
    }

    return 0;
}


