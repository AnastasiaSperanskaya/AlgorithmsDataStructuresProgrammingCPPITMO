#ifndef LAB5_TRIANGLE_H
#define LAB5_TRIANGLE_H

#include "BaseCObject.h"
#include "CVector2D.h"
#include "IDialoginitable.h"
#include "IGeoFig.h"
#include "IPhysObject.h"
#include "IPrintable.h"
#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;

class Triangle: public BaseCObject,
                public IDialogInitiable,
                public IGeoFig,
                public IPhysObject,
                public IPrintable {
private:
    double side;
    CVector2D pos;

public:

    Triangle(): side(0), pos(CVector2D(0, 0)){}

    Triangle(double side, const CVector2D &pos) : side(side), pos(pos) {}

    virtual const char *classname() {
        return "triangle";
    }

    virtual unsigned int size() {
        return sizeof(Triangle);
    }

    virtual void initFromDialog() {
        cout << "Enter triangle side length: " << endl;
        cin >> side;
        cout << "Enter triangle center: " << endl;
        cin >> pos.x >> pos.y;
    }

    virtual double square() {
        return side * side * sqrt(3.0) / 4.0;
    }

    virtual double perimeter() {
        return 3.0 * side;
    }

    virtual double mass() {
        return 0.5 * square();
    }

    virtual CVector2D position() {
        return pos;
    }

    virtual bool operator==(IPhysObject &ob) {
        if(ob.mass() != this->mass())
            return false;
        CVector2D obPos = ob.position();
        CVector2D pos = position();
        return obPos.x != pos.x && obPos.y != obPos.y;
    }

    virtual bool operator<(IPhysObject &ob) {
        return mass() < ob.mass();
    }

    virtual void draw() {
        CVector2D pos = position();
        cout << "Triangle with side " << side << " at (" << pos.x << ", " << pos.y << ")" << endl;
    }

};

#endif //LAB5_TRIANGLE_H
