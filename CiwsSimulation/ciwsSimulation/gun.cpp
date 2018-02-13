#include "gun.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

void Gun::orderThreats(vector<double> threats)
{
    m_threatOrder = threats;
    sort(m_threatOrder.begin(), m_threatOrder.end());
    reverse(m_threatOrder.begin(), m_threatOrder.end());
}

void Gun::fire(default_random_engine* gen)
{
    uniform_real_distribution<double> flipDist(0.0, 1.0);
    for (unsigned int i = 0; i < m_threatOrder.size(); i++)
    {
        cout << "Target " << (i+1) << setw(5) << " ";
        cout << "threat " << m_threatOrder[i];
        double flip = 1.0;
        int fires = 0.0;
        while (flip > 0.85)
        {
            flip = flipDist(*gen);
            fires++;
        }

        cout << setw(5) << fires << " burst" << (fires > 1 ? "s" : "") << "\n\n";
    }
}
