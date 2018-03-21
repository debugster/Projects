#ifndef ATM_SIMULATION_KEYPAD_H
#define ATM_SIMULATION_KEYPAD_H

#include <iostream>

using namespace std;

class Keypad
{
private:
    int input;

public:
    int getInput();
};

/// to take input of user choice
int Keypad::getInput()
{
    cin >> input;
    return input;
}

#endif //ATM_SIMULATION_KEYPAD_H
