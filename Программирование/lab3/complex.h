#pragma once
#ifndef LAB3_COMPLEX_H
#define LAB3_COMPLEX_H

class Complex
{
public:
    Complex(float real_, float imagine_);

    float calculateLength();

    void print() const;

    Complex multConst(float num) const;

    float getLength();

    Complex sum(Complex &complex) const;

    Complex multiply(Complex &complex) const;


    float real;
    float imagine;
    float length;
};

#endif //LAB3_COMPLEX_H
