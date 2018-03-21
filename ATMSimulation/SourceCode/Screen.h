#ifndef ATM_SIMULATION_SCREEN_H
#define ATM_SIMULATION_SCREEN_H

#include <iomanip>
#include <iostream>

using namespace std;

class Screen {
public:
    void displayMessage(const char *message);
    void displayMessageNewLine(const char *message);
    void displayBDTAmount(double amount);
};

/// to display message without a newline
void Screen::displayMessage(const char *message) {
    cout << message;
}

/// to display message with a newline
void Screen::displayMessageNewLine(const char *message) {
    cout << message << endl;
}

/// to display money amount
void Screen::displayBDTAmount(double amount) {
    cout << setprecision(2) << fixed << "BDT " << amount << endl;
}

#endif //ATM_SIMULATION_SCREEN_H
