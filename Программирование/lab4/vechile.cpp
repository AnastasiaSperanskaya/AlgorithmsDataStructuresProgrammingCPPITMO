#include "vechile.h"
#include <string>
#include <iostream>

using namespace std;

int Vehicles::getX()
{
    return Vehicles::x;
}

int Vehicles::getY()
{
    return Vehicles::y;
}

int Vehicles::getZ()
{
    return Vehicles::z;
}

void Vehicles::setOffsetVector()
{
    cout << "Insert offset vector" << endl;
    cin >> Vehicles::x >> Vehicles::y >> Vehicles::z;
}

void Vehicles::getOffsetVector()
{
    cout << Vehicles::x << " " << Vehicles::y << " " << Vehicles::z << endl;
}

void Vehicles::getCoordinatesAfterTime(int time, int perm, int period)
{
    int currentX = 0, currentY = 0, currentZ = 0;

    for(int i = 0; i < time; i++)
    {
        currentX += Vehicles::x;
        currentY += Vehicles::y;
        currentZ += Vehicles::z;

        if((i < period) && (perm == 1))
            cout << currentX << " " << currentY << " " << currentZ << endl;
    }
    cout << "Last coordinates are: " << currentX << " " << currentY << " " << currentZ << endl;
}

void Car::setPetrolConsumption()
{
    cout << "Insert petrol consumption" << endl;
    cin >> Car::petrolConsumption;
}

void Car::getPetrolConsumption()
{
    cout << petrolConsumption << endl;
}

void Car::setAmountOfPetrol()
{
    cout << "Insert amount of petrol" << endl;
    cin >> Car::amountOfPetrol;
}

void Car::getAmountOfPetrol()
{
    cout << amountOfPetrol << endl;
}

void Car::getCoordinatesAfterTime(int time, int perm, int period)
{
    int currentX = 0, currentY = 0, currentZ = 0;

    for(int i = 0; i < time; i++)
    {
        if(amountOfPetrol - petrolConsumption < 0)
        {
            refillPetrol();
            if(amountOfPetrol - petrolConsumption < 0)
            {
                cout << "Petrol is gone!" << endl;
                break;
            }
            else
                cout << "Petrol is succesfully refilled!" << endl;
        }
        currentX += this -> x;
        currentY += this -> y;
        currentZ += this -> z;

        if((i < period) && (perm == 1))
            cout << currentX << " " << currentY << " " << currentZ << endl;

        amountOfPetrol -= petrolConsumption;
    }
    cout << "Last coordinates are: " << currentX << " " << currentY << " " << currentZ << endl;
}

void Car::refillPetrol()
{
    int answer;
    cout << "Not enough petrol. Current amount of petrol = " << amountOfPetrol << ". Minimum petrol that needed = " << petrolConsumption - amountOfPetrol << ". Will you refill petrol? (0/1)" << endl;
    cin >> answer;
    if(answer == 0)
        cout << "Ok" << endl;
    else
    {
        cout << "Insert amount of refilling petrol" << endl;
        cin >> answer;
        amountOfPetrol += answer;
    }
}