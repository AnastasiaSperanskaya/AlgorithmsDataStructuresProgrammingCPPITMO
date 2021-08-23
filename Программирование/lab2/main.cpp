#include "func.h"
#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
 /*   //2
    square sq;
    square sq1;
    cin >> sq.x >> sq.y >> sq.side >> sq.angle;
    cin >> sq1.x >> sq1.y >> sq1.side >> sq1.angle;

    if(operator==(sq,sq1))
        cout << "first square area equals second square area" << endl;
    if(operator!=(sq,sq1))
        cout << "first square area is not equal second square area" << endl;
    if(operator>(sq,sq1))
        cout << "first square area is bigger than second square area" << endl;
    if(operator<(sq,sq1))
        cout << "first square area is smaller than second square area" << endl;

    double n;
    cin >> n;
    //sq1 = operator*(sq, n);
    sq1 = sq * n;
    cout << sq1.x << " " << sq1.y << " " << sq1.side << " " << sq1.angle << endl;

    sq1 = operator+(sq);
    cout << sq1.x << " " << sq1.y << " " << sq1.side << " " << sq1.angle << endl;
*/

    //7
    set a;
    set b;
    set c;
    int p, q;
    cin >> p >> q;
    int element;

    for(int i = 0; i < 10; i++)
    {
        a.array[i] = -1;
        b.array[i] = -1;
        c.array[i] = -1;
    }

    for(int i = 0; i < p; i++)
    {
        cin >> element;
        a.array[element] = element;
    }

    for(int i = 0; i < q; i++)
    {
        cin >> element;
        b.array[element] = element;
    }

    if(operator==(a, b))
        cout << "set 1 equals set 2" << endl;

    if(operator!=(a, b))
        cout << "set 1  does not equal set 2" << endl;

    c = operator+(a, b);

    for(int i = 0; i < 10; i++)
        if(c.array[i] == i)
            cout << c.array[i] << " ";
    cout << endl;

    int l;
    cin >> l;

    //c = operator+(c, l);
    c += l;

    for(int i = 0; i < 10; i++)
        if(c.array[i] == i)
            cout << c.array[i] << " ";
    cout << endl;

    int r;
    cin >> r;

    c = operator-(c, r);

    for(int i = 0; i < 10; i++)
        if(c.array[i] == i)
            cout << c.array[i] << " ";
    cout << endl;
}