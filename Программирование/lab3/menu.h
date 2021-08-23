#pragma once

#ifndef LAB3_MENU_H
#define LAB3_MENU_H

#include "string"
#include "complex.h"
#include "vector.h"

class Menu{
public:

    void showNumbers(Complex &complex1, Complex &complex2);
    void showVector(Vector &vector1, Vector &vector2);

    Complex enterOperand(bool isFirst);
    Vector enterVector(bool isFirst);

    void run();
};

#endif //LAB3_MENU_H
