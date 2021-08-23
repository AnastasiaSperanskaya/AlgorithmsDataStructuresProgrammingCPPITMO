#include "iostream"
#include "math.h"
#include "complex.h"

using namespace std;

Complex::Complex(float real_, float imagine_)
        :real(real_),
         imagine(imagine_)
{
    length = calculateLength();
}

float Complex::calculateLength() {
    float res = sqrt(pow(real,2) + pow(imagine,2));
    return res;
}

void Complex::print() const {
    cout << real;
    if(imagine > 0) cout << "+";
    cout << imagine << "i";
}

Complex Complex::multConst(float num) const {
    float real = this->real * num;
    float imagine = this->imagine * num;
    Complex res(real,imagine);
    return res;
}

float Complex::getLength() {
    return length;
}

Complex Complex::sum(Complex &complex) const {
    float real = this->real + complex.real;
    float imagine = this->imagine + complex.imagine;
    Complex result(real,imagine);
    return result;
}

Complex Complex::multiply(Complex &complex) const {
    float real, imagine;
    imagine = this->real * complex.imagine + this->imagine * complex.real;
    real = this->real * complex.real - this->imagine * complex.imagine;
    Complex result(real, imagine);
    return result;
}