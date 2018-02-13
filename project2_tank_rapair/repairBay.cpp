#include  "repairBay.h"
#include  "inventory.h"
#include <algorithm>    // std::find
#include <vector>       // std::vector

RepairBay::RepairBay(Inventory *passedInventory)
{
	// sets the vehicle pointer to null
	vPtr = nullptr;

	// set this equal to the number of objects created
	// from the bay class using a static variable
	id= ++bayNumber;
	inventory = passedInventory;
}

RepairBay::~RepairBay()
{
}

bool RepairBay::isOccupied()
{
		if (vPtr!= nullptr)
		{
			return true;
		}
		return false;
}

bool RepairBay::testVehicle()
{
    if(vPtr->getHoursReq() != 0)
        return false;
    vPtr->setStatus("testing");
    uniform_real_distribution<double> percent(0,1);
    double chance = percent(*engine);
    if(chance > .90)
    {
        vPtr->breakPart();
        return false;
    }
    return true;
}

bool RepairBay::isPartAvailable()
{
	std::vector<int> myvector (inventory->getUsedParts().begin(), inventory->getUsedParts().end());
   // vector<int>::iterator it;
    auto it = inventory->getUsedParts().begin();
    //it = inventory->getUsedParts().begin();
    it = find(inventory->getUsedParts().begin(), inventory->getUsedParts().end(), vPtr->getBrokenParts()[0]);
    if (it!= inventory->getUsedParts().end())
        return true;
    else
        it = find(inventory->getNewParts().begin(), inventory->getNewParts().end(), vPtr->getBrokenParts()[0]);
    if(it != inventory->getNewParts().end())
        return true;
    else
        return false;

}

void RepairBay::placeInBay(Vehicle *vehicle)
{
    vPtr = vehicle;
}

void RepairBay::minusTimeReq()
{
    vPtr->minusTimeReq();
}

Vehicle* RepairBay::setComplete()
{
    if(vPtr->getHoursReq() == 0)
    {
        return vPtr;
    }
}

void RepairBay::display(ostream &out)
{
	if (this->isOccupied())
		out <<"This is the vehicle in the bay: \n" << *vPtr << endl;
	else
		out<< "bay is empty \n";
	out << id << endl;

}
int RepairBay::bayNumber = 0;
