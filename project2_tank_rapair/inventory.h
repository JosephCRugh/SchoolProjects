#ifndef INVENTORY_H
#define INVENTORY_H

#include "vehicle.h"
#include <list>
#include <random>

using namespace std;

class Inventory
{
public:

    list<int> getNewParts();

    list<int> getUsedParts();

    void addVehicleToStrip(Vehicle* veh);

    int numberOfNewParts();

    int numberOfUsedParts();

    void generateArrivingParts(default_random_engine* engine);

private:
    list<int> m_newParts;
    list<int> m_usedParts;
};


#endif // INVENTORY_h
