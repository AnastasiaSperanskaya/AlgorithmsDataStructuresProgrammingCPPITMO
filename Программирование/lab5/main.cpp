#include <vector>
#include <stdio.h>
#include <string>
#include <iostream>
#include "BaseCObject.h"
#include "Triangle.h"
#include "Circle.h"

using namespace std;


int main(){

    vector<BaseCObject*> objects;

    while(true)
    {
        string action;
        cin >> action;


        if("create" == action)
        {
            string type;
            cin >> type;
            BaseCObject *object;

            if ("triangle" == type)
                object = new Triangle();
            else if ("circle" == type)
                object = new Circle();

            if (object != nullptr)
            {
                dynamic_cast<IDialogInitiable *>(object)->initFromDialog();
                objects.push_back(object);
                cout << "Added object of type " << type << endl;
            }
        } else if("show" == action)
        {
            int i = 0;
            for(auto it = objects.begin(); it != objects.end(); it++)
            {
                cout << (i++ + 1) << ") ";
                dynamic_cast<IPrintable *>(*it)->draw();
            }
        } else if("area" == action)
        {
            double sum = 0.0;
            for(auto it = objects.begin(); it != objects.end(); it++)
                sum += dynamic_cast<IGeoFig*>(*it)->square();
            cout << "Total area: " << sum << endl;
        } else if("perimeter" == action)
        {
            double sum = 0.0;

            for(auto it = objects.begin(); it != objects.end(); it++)
                sum += dynamic_cast<IGeoFig*>(*it)->perimeter();

            cout << "Total perimeter: " << sum << endl;
        } else if("center" == action)
        {
            CVector2D sumOfCenters(0.0, 0.0);
            int count = 0;

            for(auto it = objects.begin(); it != objects.end(); it++)
            {
                auto pos = dynamic_cast<IPhysObject *>(*it)->position();
                sumOfCenters.x += pos.x;
                sumOfCenters.y += pos.y;
                count++;
            }

            count = max(1, count);
            cout << "Center of mass: (" << (sumOfCenters.x / count) << ", " << (sumOfCenters.y / count) << ")" << endl;
        } else if("memory" == action)
        {
            int total = 0;

            for(auto it = objects.begin(); it != objects.end(); it++)
                total += (*it)->size();

            cout << "Total memory: " << total << " bytes" << endl;
        } else if("sort" == action)
        {
            sort(objects.begin(), objects.end());
            cout << "Sorted objects:" << endl;
            int i = 0;

            for(auto it = objects.begin(); it != objects.end(); it++)
            {
                cout << (i++ + 1) << ") ";
                dynamic_cast<IPrintable *>(*it)->draw();
            }
        } else if("exit" == action)
            break;

    }



}
