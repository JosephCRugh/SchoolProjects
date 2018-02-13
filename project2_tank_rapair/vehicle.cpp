#include "vehicle.h"
#include <iostream>
#include <list>
#include <ctime>
#include <algorithm>    // std::unique, std::distance
#include <vector>       // std::vector

///TO-DO
// I need a set bay function in the vehicle class that will set the bay the
// vehicle has been moved to and print to and vehicles ID, status = in repair, etc..

int Vehicle::m_idCount = 0;

Vehicle::Vehicle(int type)
    : m_idNum(m_idCount), m_type(type)
{
    m_idCount++;
    m_status = "arrived";
}

int Vehicle::getHoursReq()
{
	return  m_hoursNeeded;
}

void Vehicle::setHoursReq(int hours)
{
	m_hoursNeeded = hours;
}

void Vehicle::minusTimeReq()
{
	m_hoursNeeded= m_hoursNeeded- 100;
}

/// Copy constructor
Vehicle::Vehicle( const Vehicle &src)
{
    this->m_idNum = src.m_idNum;
    this->m_type = src.m_type;
    this-> m_workingParts = m_workingParts;
    this->m_brokenParts = m_brokenParts;
    this->m_hoursNeeded = m_hoursNeeded;
}

Vehicle::Vehicle()
:m_idNum(m_idCount)
{
	    engine = new default_random_engine(time(NULL));
	    uniform_int_distribution<int> typeOfVehicle(0, 5);
	    if (m_idCount %2 == 0)
	    	srand(time(NULL)+m_idCount);
	    else if (m_idCount %2 == 1)
		    	srand(time(NULL)+rand());

	    m_type= (rand() % 5 );
	    m_idCount++;
	    m_status ="arrived";
	   assignPartsToType();

}

Vehicle::~Vehicle()
{
}

void Vehicle::assignPartsToType()
{

	//cout << "inside assignPartsToType\n";
	engine = new default_random_engine(rand());
	if (m_idCount %2 == 0)
	    	srand(time(NULL)+m_idCount);
	    else if (m_idCount %2 == 1)
		    	srand(time(NULL)+rand());
    int numberOfParts = m_type + 3;
    uniform_int_distribution<int> randomBrokenParts(1, numberOfParts);
    int numberOfBrokenParts = randomBrokenParts(*engine);
    //cout << "number of broken parts " << numberOfBrokenParts;
    vector<int> parts = PART_TYPES[m_type];


   for (int i=0; i < numberOfParts; i++)
   {
        m_workingParts.push_back(parts[i]);
   }

   for (int i=0; i < numberOfBrokenParts; i++)
   {
   		breakPart();
   }
}

vector<int> Vehicle::getWorkingParts()
{
    return m_workingParts;
}

vector<int> Vehicle::getBrokenParts()
{
    return m_brokenParts;
}

bool Vehicle::operator<( Vehicle *rhs)
{
	cout << "-------------------------------------------------------------------";
	cout << endl <<endl <<endl << "THIS WAS CALLED" << endl	<<endl<<endl;
   return this->m_hoursNeeded > rhs->getHoursReq();

}

/*
*	Whenever a vehicles status has been changed the vehicle will be displayed to screen.
*/
void Vehicle::setStatus(const char* status)
{
    m_status = status;
    display(cout);
}

void Vehicle::display(ostream &outs)
{
    cout << "Vehicle: " << m_idNum << " has status: " << m_status << "\n";
    cout << "type: " << m_type << " vehicle" <<endl;
    cout << "Repair Time: " << m_hoursNeeded<< endl;
    cout << endl;
}

//default_random_engine* engine I want to see if there is a way around passing this thing around
void Vehicle::breakPart()
{
    int numberOfWorkingParts = m_workingParts.size();
    uniform_int_distribution<int> breakRandomPart(0, numberOfWorkingParts - 1);
    int brokenIndex = breakRandomPart(*engine);
    int part = m_workingParts[brokenIndex];
    m_brokenParts.push_back(part);
    m_workingParts.erase(m_workingParts.begin() + brokenIndex);
}

void Vehicle::displayTest(std::ofstream& out)
{
    const char* ss = "this string";
    out << ss;
}
