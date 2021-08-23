#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define hsize 1000000

typedef struct chain
{
    chain* prev;
    chain* next;
    long long val;
    bool ex;
} chain;

double root5 = pow(5, 0.5);
double A = (root5 - 1) / 2.0;
int hash_func(long long key, chain ** htable);
bool val_exists(chain ** htable, long long val);
void val_insert(chain ** htable, long long val);
void val_delete(chain ** htable, long long val);

long size = 0;

int main()
{
    FILE * in, *out;
    in = fopen("set.in", "r");
    out = fopen("set.out", "w");

    chain * hash[hsize];
    for (int i = 0; i < hsize; i++)
        hash[i] = NULL;

    char command[7];
    long long arg;
    fgets(command, 7, in);
    fscanf(in, "%lld", &arg);
    while (true) {
        if (command[0] == 'i') // insert
            val_insert(&hash[0], arg);
        else if (command[0] == 'd') // delete
            val_delete(&hash[0], arg);
        else if (command[0] == 'e') // exists
            fprintf(out, "%s", val_exists(&hash[0], arg) ? "true\n" : "false\n");
        if (feof(in))
            break;
        fgets(command, 7, in);
        fscanf(in, "%lld", &arg);
    }

    fclose(in);
    fclose(out);
    return 0;
}

int hash_func(long long key, chain ** htable)
{
    double tmp;
    int result = abs((int)(floor(hsize * modf(key * A, &tmp))));
    return (result >= hsize || result < 0 ? (hsize / 2) : result); // 500 000 if result >= hsize || result < 0
}

bool val_exists(chain ** htable, long long val)
{
    if (size <= 0)
        return false;

    int val_hash = hash_func(val, htable); // doesn't exist
    if (htable[val_hash] == NULL)
        return false;

    chain * check = htable[val_hash]; // 1st
    if (check->val == val)
        return true;

    while (check->next != NULL) // 1 -> last
    {
        if (check->next->val == val)
            return true;
        check = check->next;
    }
    return false;
}

void val_insert(chain ** htable, long long val)
{
    int val_hash = hash_func(val, htable);
    if (htable[val_hash] == NULL) // doesn't exist
    {
        htable[val_hash] = (chain*)malloc(sizeof(chain));
        *htable[val_hash] = { NULL, NULL, val, true };
        size++;
        return;
    }

    chain * check = htable[val_hash];
    if (check->val == val) // 1st
        return;
    while (check->next != NULL) // 1 -> last
    {
        if (check->next->val == val)
            return;
        check = check->next;
    }
    check->next = (chain*)malloc(sizeof(chain)); // found last -> add new
    *check->next = { check, NULL, val, true };
    size++;
}

void val_delete(chain ** htable, long long val)
{

    if (size <= 0)
        return;

    int val_hash = hash_func(val, htable);
    if (htable[val_hash] == NULL) // doesn't exist
        return;

    chain * check = htable[val_hash];

    if (check->val == val) // 1st
    {
        if (check->next == NULL)
        {
            htable[val_hash] = NULL;
            size--;
            free(check);
            return;
        }
        htable[val_hash] = check->next;
        check->next->prev = NULL;
        free(check);
        size--;
        return;
    }

    while (true) // 1 -> last
    {
        if (check->next != NULL && check->val == val)
        {
            check->prev->next = check->next;
            check->next->prev = check->prev;
            free(check);
            size--;
            return;
        }
        else if (check->next == NULL && check->val == val) // last
        {
            check->prev->next = NULL;
            free(check);
            return;
        }
        else if (check->next != NULL)
            check = check->next;
        else if (check->next == NULL)
            break;
    }
}