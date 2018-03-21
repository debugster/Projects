#ifndef ATM_SIMULATION_ATMTIME_H
#define ATM_SIMULATION_ATMTIME_H

#include <ctime>
#include <string>

using namespace std;

class ATMTime
{
public:
    string getTimeNow();
};

string ATMTime::getTimeNow()
{
    time_t now = time(0);

    char *dt = ctime(&now);

    string timeNow = dt;

    timeNow[timeNow.size() - 1] = ' ';

    return timeNow;
}

#endif //ATM_SIMULATION_ATMTIME_H
