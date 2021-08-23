#ifndef LAB4_VECHILE_H
#define LAB4_VECHILE_H

#include <stdio.h>
#pragma once
#include <string>

using namespace std;

class Vehicles {
public:
    void setOffsetVector();
    void getOffsetVector();
    void getCoordinatesAfterTime(int, int, int);

    int getX();
    int getY();
    int getZ();

protected:
    int x, y, z;
};

class Car : public Vehicles {
public:
    void setPetrolConsumption();
    void getPetrolConsumption();
    void setAmountOfPetrol();
    void getAmountOfPetrol();
    void getCoordinatesAfterTime(int, int, int);
    void refillPetrol();

private:
    int amountOfPetrol, petrolConsumption;
};

#endif //LAB4_VECHILE_H
