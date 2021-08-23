#include <iostream>
#include <iostream>
#include "vechile.h"

using namespace std;

int main()
{
    Vehicles vehicle;

    int time, perm, period;
    vehicle.setOffsetVector();
    cout << "Inputted offset vector: ";
    vehicle.getOffsetVector();

    cout << "Input time" << endl;
    cin >> time;
    cout << "Allow tracking? (0/1)" << endl;
    cin >> perm;

    if(perm == 0)
        period = 1;
    else
    {
        cout << "Input period of tracking " << endl;
        cin >> period;
    }
    vehicle.getCoordinatesAfterTime(time, perm, period);

    Car car;

    car.setOffsetVector();
    cout << "Inputted offset vector: ";
    car.getOffsetVector();

    car.setPetrolConsumption();
    cout << "Inputted petrol consumption: ";
    car.getPetrolConsumption();

    car.setAmountOfPetrol();
    cout << "Inputted amount of petrol: ";
    car.getAmountOfPetrol();

    cout << "Input time" << endl;
    cin >> time;
    cout << "Allow tracking? (0/1)" << endl;
    cin >> perm;
    if(perm == 0)
        period = 1;
    else
    {
        cout << "Input period of tracking " << endl;
        cin >> period;
    }
    car.getCoordinatesAfterTime(time, perm, period);

    return 0;
}
