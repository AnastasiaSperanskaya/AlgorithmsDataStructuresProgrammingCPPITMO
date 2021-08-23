#include <iostream>
#include <fstream>
using namespace std;

const int n=1000;
int a[n][n];
int b[n][n];
int c[n][n];

int main() {

    ifstream fin("turtle.in");
    ofstream fout("turtle.out");

    int h,w,i,j;
    fin>>h>>w;

    for(i=0;i<h;i++)
        for(j=0;j<w;j++)
            fin>>a[i][j];

    for(i=0;i<h;i++){
        for(j=0;j<w;j++){
            b[i][j]=a[h-1-i][j];
        }
    }

    int k=0;
    for(i=0;i<h;i++){
        k+=b[i][0];
        c[i][0]=k;
    }

    k=0;д
    for(j=0;j<w;j++){
        k+=b[0][j];
        c[0][j]=k;
    }

    for(i=1;i<h;i++){
        for(j=1;j<w;j++){
            if (c[i-1][j]>c[i][j-1]){
                c[i][j]=c[i-1][j]+b[i][j];
            }
            else
                c[i][j]=c[i][j-1]+b[i][j];
        }
    }

    fout<<c[h-1][w-1];

    fout.close();
    fout.close();

    return 0;
}

