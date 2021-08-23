#include<stdio.h>
#include <string.h>

int sum(int n)
{
    int k = 0;
    if(n / 10 == 0)
        return n % 10;
    else
    {
        k += n % 10;
        k += sum(n / 10);
    }
    return k;
}

void DelSpace(char* str, int ind)
{
    int i;
    if ( ((str[ind] == ' ') || (str[ind] == '(') || (str[ind] == '[') || (str[ind] == '{')) && (str[ind+1]) == ' ' )
        DelSpace(str, ind + 1);
    for (i = ind; i < strlen(str) - 1; i++)
    {
        str[i] = str[i + 1];
    }
    str[i] = 0;

}

int main()
{
    //Задание 4

    int n;
    scanf("%d",&n);
    int k = sum(n);
    printf("%d",k);

    //Задание 5

    char str[]={"he  ll  o,    (    World  ,"};
    scanf("->\t%s", str);
    for (int i = 0; i < strlen(str); i++)
    { if ( ((str[i] == ' ') || (str[i] == '(') || (str[i] == '[') || (str[i] == '{')) && (str[i+1]==' ') )
            DelSpace(str, i + 1);
    }

    printf("\n%s", str);

    return 0;
}