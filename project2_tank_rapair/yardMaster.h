#ifndef YARDMASTER_H
#define YARDMASTER_H
#include "vehicle.h"
#include "repairBay.h"
#include "repairYard.h"
#include <iostream>
#include <fstream>

class YardMaster
{
	public:
	YardMaster(RepairYard *repairYard, int desiredDays,  string fileName);
	~YardMaster();
	void addHour();

	void manageYard();
	void anotherRun();

	RepairYard* getRepairYard();

	private:
	// A private pointer to the repair yard passed into the constructor
	RepairYard *repairYard;

	ofstream out;
	// This is the number days that the
	// program should run for
	int desiredDays;

	// running total of days
	// number of days since start of simulation.
	// the yard master is the bad boss that hovers over your shoulder and says
	// is the iPhone fixed yet and you say no I am testing it
	// and then she says well the lady is waiting in the lobby and looks
	// annoyed. Then comes through every hour and sticks her nose in everyones buisness
	// and complains about how we are slow and suck.
	int numDays;

	// simulation runs on military time
	int hours2400;

	// decides which new arrivals are any good
	void calculateHoursOfWork(vector<Vehicle*> newArrivals);

	void repairOrScrap(Vehicle * aVeh, int partsRatio);

    void sendToScrap();

	bool checkStatus();

	bool checkInventory();

	void addVehicleToBay(Vehicle Vehicle);

	// This function adds one today and
	// generates new incoming vehicles.
	void beginNewDay();
};

#endif
