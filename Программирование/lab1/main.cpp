#include "func.h"
#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
    //3
    int a,b;
    cin >> a >> b;
    third1(&a,&b);
    cout << a << " " << b << endl;
    third2(a,b);
    cout << a << " " << b << endl;

    //8
    double m;
    cin >> m;
    eighth1(&m);
    cout << m << endl;
    eighth2(m);
    cout << m << endl;

    //11
    double n;
    circle c;
    cin >> c.x >> c.y >> c.R >> n;
    eleventh1(&c,n);
    cout << c.R << endl;
    eleventh2(c,n);
    cout << c.R << endl;

    //16
    int q,p;
    int M,N;

    cin >> q >> p >> M >> N;

    int **A = new int*[M];
    for(int i = 0; i < M; i++)
        A[i] = new int[N];

    sixteenth1(A,M,N,q,p);

    for(int i = 0; i < M; i++)
        delete []A[i];

    delete []A;

    int w,h,k,l;

    cin >> w >> h >> k >> l;

    int arr[w*h];

    for (int i = 0; i< w*h; i++) cin >> arr[i];

    sixteenth2(*arr,k,l,w);

    for (int i = 0; i < w*h; i++)
    {
        cout << arr[i]<< " ";
        if ((i+1) % w == 0) cout << endl;
    }
}