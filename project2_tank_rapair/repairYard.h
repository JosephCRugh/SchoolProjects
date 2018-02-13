// Raphael J. Sandor
// CS 361 Fall 2017

#ifndef REPAIRYARD_H_INCLUDED
#define REPAIRYARD_H_INCLUDED
#include <list>
#include <queue>
#include <random>
#include <time.h>
#include "repairBay.h"
#include "vehicle.h"
#include "inventory.h"
using namespace std;
struct LessThanByP
{
    bool operator()( Vehicle * lhs, Vehicle * rhs)
    {
        return lhs->getHoursReq() > rhs->getHoursReq();
    }
};
class RepairYard
{

	public:
	RepairYard(Inventory *passedInInventory);
	~RepairYard();
    default_random_engine *  randomEngine = new default_random_engine(time(NULL));


	private:

	// inventory pointer
	Inventory *inventory;

	list<RepairBay*>::iterator bayItr;

    // Three repair bays should be stored in vector or list
	list<RepairBay*> repairBays;

	// Priority Que to store vehicles
	priority_queue<Vehicle*,vector<Vehicle*>, LessThanByP> pQueue;
    // vehicle pointer
	Vehicle *vPtr;


    // list of arrived vehicles that were generated that day in the class.
    std::vector<Vehicle*>arrived;

    // List of vehicles waiting on parts to arrive
    std::vector<Vehicle*> m_waitingVehicles;

    int totalFixed;
	int fixedToday;
	int numberOfDays;
	int numberOfArrivals;

	public:
    // outputs report
	// this will be called from the main function at the end of the day
	// we can format it display total fixed. Fixed that day
	// number of tanks in q to get fixed.
	// this probably needs a output stream passed to it
	void outputReport(ofstream &ofs);

	/*
	 *  Generates a list of tanks that have broken parts
	 *  this uses the vehicle classes create tank function.
	 *  This function uses that capability and stores them.
     */
	void generateNewArrivals();

	// returns repair bay objects
	list<RepairBay*> getRepairBays();

	// returns total fixed since start of application
	int getTotalFixed();

	// get numberFixed that day
	int getFixedToday();

    // adds to the number of fixed in a day
	void addFixed( int numberOfFixed);

    // rests number of fininshed in a day and adds one to days
	void endOfDay(ofstream &out);

	// displays the vehicles that are in the arrived vector
	void displayArrived(ostream &out);

	// displays a bay that is contained in the repairYard
	void displayBay(ostream &out);

	// displays what is waiting to be fixed
	void displayQueue(ostream &out);

	// adds one to the number of fixed
	void addFixed();

	// removes the first element of the arrived list.
	void removeFromArrived();

	// returns the inventory pointer
	Inventory* getInventory();

	// checks if there is an open bay and returns the open bays.
	list<RepairBay*> checkBays();

	// returns the arrived vector
	vector<Vehicle*> getArrived();

	vector<Vehicle*>* getWaitingVehicles();

	priority_queue<Vehicle*,vector<Vehicle*>, LessThanByP>* getPQueue();
};
#endif
