#pragma once
#ifndef LAB3_VECTOR_H
#define LAB3_VECTOR_H

class Vector
{
public:
    Vector(float x_, float y_, float z_ );

    float CalculateVectorLength();
    float GetVectorLength();

    void printVector() const;

    Vector vectorSum(Vector &vector) const;
    Vector vectorSub(Vector &vector) const;

    float GetAngle(Vector &vector);

    float x;
    float y;
    float z;
    float length;
};

#endif //LAB3_VECTOR_H
