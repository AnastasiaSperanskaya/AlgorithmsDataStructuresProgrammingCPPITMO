#ifndef LAB5_CIRCLE_H
#define LAB5_CIRCLE_H

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

class Circle:   public BaseCObject,
                public IDialogInitiable,
                public IGeoFig,
                public IPhysObject,
                public IPrintable {
private:
    double R;
    CVector2D pos;

public:

    Circle(): R(0), pos(CVector2D(0, 0)){}

    Circle(double R, const CVector2D &pos) : R(R), pos(pos) {}

    virtual const char *classname() {
        return "circle";
    }

    virtual unsigned int size() {
        return sizeof(Circle);
    }

    virtual void initFromDialog() {
        cout << "Enter circle radius: " << endl;
        cin >> R;
        cout << "Enter circle center: " << endl;
        cin >> pos.x >> pos.y;
    }

    virtual double square() {
        return R * R * 3.14;
    }

    virtual double perimeter() {
        return 2.0 * R * 3.14;
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
        cout << "Circle with radius " << R << " at (" << pos.x << ", " << pos.y << ")" << endl;
    }

};

#endif //LAB5_CIRCLE_H
