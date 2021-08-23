#include <iostream>
using namespace std;

int main() {
    char a[]="Hello";
    char *ptra;
    ptra=&a[0];
    for(*ptra=a[0];ptra<=&a[4];ptra++)
        cout<<*ptra<<' ';

    cout<<endl;

    char *ptr=new char[4];
    ptr[0]='H';
    ptr[1]='e';
    ptr[2]='l';
    ptr[3]='l';
    ptr[4]='o';
    for(int i=0;i<=4;i++)
        cout<<ptr[i]<<' ';
    delete[]ptr;

    return 0;
}