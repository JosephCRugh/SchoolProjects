#include "repairYard.h"
#include "repairBay.h"
using namespace std;

#include <random>
#include <iostream>
#include <fstream>


/*
* Basic constructor sets every field.
*/
RepairYard::RepairYard(Inventory *passedInInventory)
{
	// number of vehicles fixed in one day.
	fixedToday = 0;
	// number of vehicles fixed since the start of the simulation
	totalFixed = 0;


	inventory = passedInInventory;

	numberOfDays = 0;

	for (int i = 0; i < 3; i++)
			repairBays.push_back(new RepairBay(inventory));
	generateNewArrivals();
	//displayArrived(cout);
}

/*
* Generates a list of new arrivals
* Creates between 1 and 8 vehicles to be fixed in a day.
*/
void RepairYard::generateNewArrivals()
{
	if (rand()%8== 0)
	    srand(time(NULL)+5);
	else if (rand()%3 == 1)
		srand(time(NULL)+rand());
	int numVeh = (rand() % 8 )+1;
	numberOfArrivals= numVeh;
	for (int i=0; i < numVeh; i++)
	{
		arrived.push_back(new Vehicle());
	}
}

/*
*  Makes sure we don't get any of those
*  dreaded memory leaks when to program is finished
*/
RepairYard::~RepairYard()
{
	// iterator to go throught the stl list of repair bays
	bayItr =  repairBays.begin();
	while(bayItr!= repairBays.end())
		// deletes the itr
		delete *bayItr;
		bayItr++;
}
/*
*	This function prints out a report of what has been fixed this day. It is passed an ofs stream
*   that has already been linked with a file.
*/
void RepairYard::outputReport(ofstream &out)
{

	out << "Day Number: " << numberOfDays << endl;
	out << "Vehicles fixed today: " << fixedToday << "\n";
	out << "Total Vehicles fixed: " << totalFixed << "\n";
	out << "Number of vehicles that arrived today:  " << numberOfArrivals << "\n";
}

/*
*  Resets the number of hours and number of
*  vehicle completed in a day.
*/
void RepairYard::endOfDay(ofstream &out)
{
	outputReport(out);
	// adds one to days
	numberOfDays++;
	//
	fixedToday = 0;

	// unnecessary 0's to accentuate the fact this is in military time.
	//hours2400 = 0000;
	generateNewArrivals();

}

/*
 * This adds one to fixed today and total fixed vehicles.
 */
void RepairYard::addFixed()
{
	fixedToday++;
	totalFixed++;
}

// returns total of vehicles that have
// been fixed
int RepairYard::getTotalFixed()
{
	return totalFixed;
}

int RepairYard::getFixedToday()
{
	return fixedToday;
}

vector<Vehicle*> RepairYard::getArrived()
{
	return arrived;
}

vector<Vehicle*>* RepairYard::getWaitingVehicles()
{
    return &m_waitingVehicles;
}


list<RepairBay*> RepairYard::checkBays()
{
	list<RepairBay*> emptyBays;
	// iterator to go through the stl list of repair bays
	bayItr =  repairBays.begin();
	while(bayItr!= repairBays.end())
	{
	 	if ((**bayItr).isOccupied() == true)
			emptyBays.push_back(*bayItr);
		bayItr++;
	}
	return emptyBays;
}

void RepairYard::displayBay(ostream &out)
{
	bayItr =  repairBays.begin();
	while(bayItr!= repairBays.end())
	{
	 	(**bayItr).display(out);
		bayItr++;
	}
}

void  RepairYard::displayQueue(ostream &out)
{
	vector<Vehicle*>tempStorage;

	while(!pQueue.empty())
{
    Vehicle* temp = pQueue.top();
    pQueue.pop();
    std::cout << *temp<<endl;
    tempStorage.push_back(temp);
}
	for(unsigned int i=0; i < tempStorage.size(); i++){
   	pQueue.push(tempStorage[i]);

	}
}

void RepairYard::displayArrived(ostream &out)
{

	for (Vehicle *vehicle : arrived )
			cout << *vehicle;
}

// I am still not sure who should keep time
// I think the yard master should
/*
int RepairYard::getDays()
{
	return days;
}

void RepairYard::setDays(int numbDays)
{
	numberOfDays = numbDays;
}
*/

priority_queue<Vehicle*,vector<Vehicle*>,LessThanByP> *RepairYard::getPQueue()
{
	return &pQueue;
}

Inventory* RepairYard::getInventory()
{
	return inventory;
}

void RepairYard::removeFromArrived()
{
	arrived.erase(arrived.begin());

}
