#include "inventory.h"

list<int> Inventory::getNewParts()
{

    return m_newParts;
}

list<int> Inventory::getUsedParts()
{
    return m_usedParts;
}

void Inventory::addVehicleToStrip(Vehicle *veh)
{
    vector<int> workingParts = veh->getWorkingParts();
    for (unsigned int i = 0; i < workingParts.size(); i++)
    {
        m_usedParts.push_back(workingParts[i]);
    }
}

int Inventory::numberOfNewParts()
{
    return m_newParts.size();
}

int Inventory::numberOfUsedParts()
{
    return m_usedParts.size();
}

void Inventory::generateArrivingParts(default_random_engine* engine)
{
    uniform_int_distribution<int> numNewPartsRan(1, 4);
    int numNewParts = numNewPartsRan(*engine);
    uniform_int_distribution<int> genNewParts(1, 17);
    for (int i = 0; i < numNewParts; i++)
    {
        m_newParts.push_back(genNewParts(*engine));
    }
}
