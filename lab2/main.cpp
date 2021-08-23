#include <iostream>
#include<math.h>
#include<stdio.h>
using namespace std;

int main() {
    long double a;
    long double z1;
    long double z2;
    cin>>a;
    z1=(sin(2.0*a)+sin(5.0*a)-sin(3.0*a))/(cos(a)-cos(3.0*a)+cos(5.0*a));
    z2=sin(a*3.0)/cos(3.0*a);
    cout<<z1<<endl;
    cout<<z2<<endl;


    return 0;
}