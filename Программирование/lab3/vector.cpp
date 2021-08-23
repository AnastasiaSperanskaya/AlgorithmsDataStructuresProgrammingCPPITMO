#include "iostream"
#include "math.h"
#include "vector.h"

using namespace std;

Vector::Vector(float x_, float y_, float z_)
        :x(x_),
         y(y_),
         z(z_)
{
    length = CalculateVectorLength();
}

float Vector::CalculateVectorLength() {
    float res = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
    return res;
}

float Vector::GetVectorLength() {
    return length;
}

void Vector::printVector() const {
    cout << '(' << x << ',' << y << ',' << z << ')';
}

Vector Vector::vectorSum(Vector &vector) const {
    float x = this->x + vector.x;
    float y = this->y + vector.y;
    float z = this->z + vector.z;
    Vector result(x,y,z);
    return result;
}

Vector Vector::vectorSub(Vector &vector) const {
    float x = this->x - vector.x;
    float y = this->y - vector.y;
    float z = this->z - vector.z;
    Vector result(x,y,z);
    return result;
}

float Vector::GetAngle(Vector &vector) {
    float res;
    res = (this->x * vector.x + this->y * vector.y + this->z * vector.z) / (this->length * vector.length);
    return res;
}