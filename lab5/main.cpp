#include <iostream>
#include<stdio.h>
#include<math.h>
using namespace std;

int main() {
    int a[9];
    int x[2][2],w[2][2],z[2][2];

    for(int i=0;i<9;i++)
        cin>>a[i];
    for(int i=0;i<9;i++)
        cout<<a[i]<<' ';
    cout<<endl;

    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            cin>>x[i][j];

    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            cin>>w[i][j];

    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
        {
            z[i][j]=0;
            for (int k = 0; k < 2; k++)
                z[i][j] += x[i][k] * w[k][j];
        }

    for(int i=0;i<2;i++) {
        cout<<endl;
        for (int j = 0; j < 2; j++)
            cout << z[i][j] << ' ';
    }
    return 0;
}