// Make sure gnuplot.exe is included in the directory in which the application is being ran in
// By Joseph Rugh
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <list>
#include <map>
#include <fstream>

#define PI 3.14159265

using namespace std;

struct Slice {
    double x, y;
    double distance;
    double angle;
};

struct Point
{
    double x, y;
};

const int MAX_NUMBERS_OF_CRACKS = 250;

void initializeCracks(map<Point*, list<Slice>>& cracks, default_random_engine* gen,
                      normal_distribution<double> distanceDist);
void calcCoords(Slice& slice, double dist, double angle);
void continueStraight(normal_distribution<double> distanceDist, Slice& curSlice, list<Slice>& crack,
                      default_random_engine* gen);
void changeDirection(normal_distribution<double> distanceDist, Slice& curSlice, list<Slice>& crack,
                     default_random_engine* gen);
void displayGnuplot(map<Point*, list<Slice>> newCracks);

int main()
{
    srand(time(NULL));

    default_random_engine* gen = new default_random_engine(time(NULL));
    normal_distribution<double> distanceDist(3.0, 1.0);

    map<Point*, list<Slice>> cracks;
    initializeCracks(cracks, gen, distanceDist);

    // Creating the cracks
    map<Point*, list<Slice>> newCracks;
    map<Point*, list<Slice>>::iterator mapItr = cracks.begin();
    int limitCount = 0;
    while (mapItr != cracks.end())
    {
        if (limitCount >= MAX_NUMBERS_OF_CRACKS) break;
        list<Slice> crack = mapItr->second;
        Point* startingLoc = mapItr->first;
        Slice curSlice = *crack.begin();
        while (true)
        {
            int possibility = (rand() % 10) + 1;
            limitCount++;

            // Continue straight
            if (possibility == 1) continueStraight(distanceDist, curSlice, crack, gen);

            // changes direction
            if (possibility > 1 && possibility < 5) changeDirection(distanceDist, curSlice, crack, gen);

            // splits in two
            if (possibility > 4 && possibility < 9)
            {
                double newDistance1 = distanceDist(*gen) + curSlice.distance;
                double newDistance2 = distanceDist(*gen) + curSlice.distance;
                uniform_real_distribution<double> newAngleDist(curSlice.angle - 25.0, curSlice.angle + 25.0);
                double newAngle1 = newAngleDist(*gen);
                double newAngle2 = newAngleDist(*gen);
                Slice newSlice1;
                calcCoords(newSlice1, newDistance1, newAngle1);
                newSlice1.distance = newDistance1;
                newSlice1.angle = newAngle1;
                Slice newSlice2;
                calcCoords(newSlice2, newDistance2, newAngle2);
                newSlice2.distance = newDistance2;
                newSlice2.angle = newAngle2;

                Point* newPoint1 = new Point;
                newPoint1->x = curSlice.x;
                newPoint1->y = curSlice.y;
                list<Slice> newCrack1;
                newCrack1.push_back(newSlice1);
                cracks.insert(cracks.end(), pair<Point*, list<Slice>>(newPoint1, newCrack1));

                Point* newPoint2 = new Point;
                newPoint2->x = curSlice.x;
                newPoint2->y = curSlice.y;
                list<Slice> newCrack2;
                newCrack2.push_back(newSlice2);
                cracks.insert(cracks.end(), pair<Point*, list<Slice>>(newPoint2, newCrack2));
            }

            // terminates
            if (possibility > 8)
            {
                newCracks[startingLoc] = crack;
                break;
            }
        }
        mapItr++;
    }

    displayGnuplot(newCracks);

    delete gen;

    return 0;
}

void initializeCracks(map<Point*, list<Slice>>& cracks, default_random_engine* gen,
                      normal_distribution<double> distanceDist)
{
    int numCracks = (rand() % 3) + 3;
    uniform_real_distribution<double> angleDist(0.0, 360.0);

    // initialize the first 3-5 cracks
    for (int i = 0; i < numCracks; i++)
    {
        list<Slice> crack;

        double angle = angleDist(*gen);
        double distance = distanceDist(*gen);

        Slice firstSlice;
        calcCoords(firstSlice, distance, angle);
        firstSlice.distance = distance;
        firstSlice.angle = angle;

        crack.push_back(firstSlice);
        Point* p = new Point;
        p->x = 0;
        p->y = 0;
        cracks[p] = crack;
    }
}

void continueStraight(normal_distribution<double> distanceDist, Slice& curSlice, list<Slice>& crack,
                      default_random_engine* gen)
{
    double newDistance = distanceDist(*gen) + curSlice.distance;
    Slice newSlice;
    calcCoords(newSlice, newDistance, curSlice.angle);
    newSlice.distance = newDistance;
    newSlice.angle = curSlice.angle;
    crack.push_back(newSlice);
    curSlice = newSlice;
}

void changeDirection(normal_distribution<double> distanceDist, Slice& curSlice, list<Slice>& crack,
                     default_random_engine* gen)
{
    double newDistance = distanceDist(*gen) + curSlice.distance;
    // preventing the slice to loop back around on itself
    uniform_real_distribution<double> newAngleDist(curSlice.angle - 25.0, curSlice.angle + 25.0);
    double newAngle = newAngleDist(*gen);
    Slice newSlice;
    calcCoords(newSlice, newDistance, newAngle);
    newSlice.distance = newDistance;
    newSlice.angle = newAngle;
    crack.push_back(newSlice);
    curSlice = newSlice;
}

void calcCoords(Slice& slice, double dist, double angle)
{
    slice.x = dist * cos(angle*PI/180);
    slice.y = dist * sin(angle*PI/180);
}

void displayGnuplot(map<Point*, list<Slice>> newCracks)
{
    // Printing the data
    ofstream outStream;
    outStream.open("data.txt");
    map<Point*, list<Slice>>::iterator mapItr = newCracks.begin();
    while (mapItr != newCracks.end())
    {
        // starting point of crack
        outStream << mapItr->first->x << " " << mapItr->first->y << "\n";
        for (Slice slice : mapItr->second)
        {
            outStream << slice.x << " " << slice.y << "\n";
        }
        outStream << "\n";
        delete mapItr->first;
        mapItr++;
    }

    outStream.close();

    // Printing the command file
    outStream.open("command.txt");
    outStream << "set style line 1 lc rgb '#0060ad' lt 1 pt 7 ps 1.5\n";
    outStream << "plot 'data.txt' with lines ls 1\n";
    outStream << "pause -1";

    outStream.close();

    system("gnuplot.exe command.txt");
}
