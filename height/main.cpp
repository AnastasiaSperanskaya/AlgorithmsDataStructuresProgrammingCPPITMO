#include <stdio.h>

typedef struct vershina
{
    long long value = 0;
    int left = 0;
    int right = 0;
    int before = 0;
} V;

int main()
{
    int tree_size;

    FILE * in = fopen("height.in", "r");
    FILE *  out = fopen("height.out", "w");

    fscanf(in, "%d", &tree_size);

    if(tree_size < 3)
        fprintf(out, "%d", tree_size);
    else
    {
        V *arr = new V[tree_size];

        long long value;
        int left, right, current, height = 0;

        for(int current = 0; current < tree_size; current++)
        {
            fscanf(in, "%lld %d %d", &value, &left, &right);

            right--;
            left--;
            arr[current].right = right;
            arr[current].left = left;
            arr[current].value = value;

            if (arr[current].before > height)
                height = arr[current].before;

            if (arr[current].left > -1)
                arr[left].before = arr[current].before + 1;

            if (arr[current].right > -1)
                arr[right].before = arr[current].before + 1;
        }

        fprintf(out, "%d", height + 1);
        delete[] arr;

    }
    return 0;
}