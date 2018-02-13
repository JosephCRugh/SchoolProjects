#ifndef GUN_H
#define GUN_H

using namespace std;
#include <vector>
#include <random>

class Gun
{
public:
    void orderThreats(vector<double> threats);

    void fire(default_random_engine* gen);

private:
    vector<double> m_threatOrder;
};

#endif
