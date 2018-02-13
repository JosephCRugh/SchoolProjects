// By Joseph Rugh
#include "gun.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

int main()
{
    srand(time(NULL));
    int numTargets = (rand() % 6) + 4;
    vector<double> threats;

    default_random_engine* gen = new default_random_engine(time(NULL));
    normal_distribution<double> threatDist(100.0, 15.0);

    for (int i = 0; i < numTargets; i++)
    {
        threats.push_back(threatDist(*gen));
    }

    Gun gun;
    gun.orderThreats(threats);
    gun.fire(gen);

    delete gen;

    return 0;
}
