#include "yardMaster.h"
#include <iostream>
#include <fstream>

 void YardMaster::addHour()
 {
 	if (hours2400 >= 2400)
	{
 		hours2400 =0000;
		// generates new arrivals and increments days
		beginNewDay();
		cout << "Day number: " << numDays <<endl;

	}
	else
	{
		//cout << "added an hour\n";
		hours2400= hours2400+100;
	}
 }

void YardMaster::beginNewDay()
{
	cout << "\nBegin new day function" <<endl;
    numDays++;
	// calls the repair yards end of day to start a new day
	// and create a report to file and generate new vehicles
	repairYard->endOfDay(out);
	calculateHoursOfWork(repairYard->getArrived());
	repairYard->generateNewArrivals();
	calculateHoursOfWork(repairYard->getArrived());
	//cout << "number of days " << numDays+1 << endl;
	//cout << endl << endl<< endl<< endl ;
	repairYard->displayArrived(cout);

}

YardMaster::YardMaster(RepairYard *incomingRepairYard,  int desiredDays, string filename)
{
    this->desiredDays = desiredDays;
	numDays = 0;
	hours2400 = 0;
	repairYard = incomingRepairYard;
  	out.open(filename);

}

YardMaster::~YardMaster()
{
	out.close();
}

void YardMaster::manageYard()
{
	while ( numDays < desiredDays)
	{
		addHour();

	}
}

// the name of this function needs to be changed to manage arrials
// yes this function does calculate the number of hours of work
// but it now calls scrap or repair with that information
// and send the vehicle and the hours to another function
// that will place the vehicle in the priority queue or to the
// scrapyard i.e. the inventory object.
void YardMaster::calculateHoursOfWork(vector<Vehicle*> newArrivals)
{
	cout << "-------calculateHoursOfWork-------\n";
	for(auto aVeh: newArrivals)
	{
		aVeh->display(cout);
		cout << endl<<endl;
		vector<int>brokenParts = aVeh->getBrokenParts();
		vector<int>goodParts = aVeh->getWorkingParts();

		int totalPartHours=0;
		int totalBrokenParts=0;
		int totalWorkingParts=0;
		int i = 0;

		cout << "Working parts:\n";
		for (auto workingPart: aVeh->getWorkingParts())
		{

			cout << "  "<<i<<"." << "part :" << workingPart<<endl;
			totalPartHours += workingPart;
			totalWorkingParts += workingPart;
			i++;
		}

		cout << "Broken parts\n";
		for (auto aBrokenPart: aVeh->getBrokenParts())
		{
			cout << "  "<<i<<"." << "part :" << aBrokenPart<<endl;
			totalPartHours += aBrokenPart;
			totalBrokenParts += aBrokenPart;
			i++;
		}
			cout << "total of workingParts is " << totalWorkingParts << endl;
			cout << "the total of the broken parts is "<< totalBrokenParts<< endl;
			cout << "the total of all parts is "<< totalPartHours<< endl;

			aVeh->setHoursReq(totalBrokenParts);
			double partsRatio = totalBrokenParts/totalPartHours;
			repairYard->removeFromArrived();

			repairOrScrap(aVeh, partsRatio);
	}
}

void YardMaster::anotherRun()
{
	desiredDays++;

}

RepairYard* YardMaster::getRepairYard()
{
	return	repairYard;
}

void YardMaster::repairOrScrap(Vehicle * aVeh, int partsRatio)
{
	if (partsRatio <= .7)
	{
		aVeh->setStatus("In RepairQueue");
		vector<int> brokenParts = aVeh->getBrokenParts();
		Inventory* inventory = repairYard->getInventory();
		list<int> newParts = inventory->getNewParts();
		list<int> usedParts = inventory->getUsedParts();
		list<int>::iterator partsItr;
		bool foundEveryPart = true;
		// Used to check if the part is in the list
		auto checkForPart = [](list<int>::iterator& itr, list<int>& parts, bool& pf, int bp) {
            itr = parts.begin();
            while (itr != parts.end())
            {
                if (*itr == bp)
                {
                    pf = true;
                    break;
                }
                itr++;
            }
		};
		// Checking if every broken part has an associated used/new part
		for (int brokenPart : brokenParts)
        {
            bool partFound = false;
            checkForPart(partsItr, usedParts, partFound, brokenPart);
            if (partFound) continue; // No need to check new parts if it was found in the used parts
            checkForPart(partsItr, newParts, partFound, brokenPart);
            // If the part is still not found it needs to go to the waiting list
            if (!partFound)
            {
                foundEveryPart = false;
                break;
            }
        }

        if (foundEveryPart)
        {
            repairYard->getPQueue()->push(aVeh);
        }
        else
        {
            repairYard->getWaitingVehicles()->push_back(aVeh);
        }

		//repairYard->displayQueue(cout);
		cout << "size of the pque" << repairYard->getPQueue()->size() << endl;
	}
	else
	{
		// should put this vehicle in the inventory to be stripped for its good parts.
		aVeh->setStatus("being stripped for parts and thrown away.");
		repairYard->getInventory();//.addVehicleToStrip(aVeh);

	}
}
