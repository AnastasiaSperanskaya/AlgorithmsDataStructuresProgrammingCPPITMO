#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

int main()
{
    FILE *in, *out;

    in = fopen("postfix.in", "r");
    out = fopen("postfix.out", "w");

    char buffer[200];
    long long stack[200];
    int top = -1;

    while (fscanf(in, "%s", buffer) != EOF)
    {

        switch (buffer[0])
        {
            case '-':
                stack[top - 1] -= stack[top];
                top--;
                break;
            case '+':
                stack[top - 1] += stack[top];
                top--;
                break;
            case '*':
                stack[top - 1] *= stack[top];
                top--;
                break;
            default:
                stack[++top] = atoi(buffer);
        }
    }

    fprintf(out, "%lld", stack[0]);
    fclose(in);
    fclose(out);
}