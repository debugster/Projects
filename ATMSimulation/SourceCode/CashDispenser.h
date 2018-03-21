#ifndef ATM_SIMULATION_CASHDISPENSER_H
#define ATM_SIMULATION_CASHDISPENSER_H

/// Initially ATM has 2000 notes of BDT 500, in total BDT 1,000,000
#define INITIAL_COUNT 2000

class CashDispenser {
private:
    static int count;

public:
    bool isSufficientCashAvailable(int amount);
    void dispenseCash(int amount);
};

/// to keep track how many BDT 500 notes are available inside ATM
/// this information has been made static because all the instances of CashDispenser should share same data
int CashDispenser::count = INITIAL_COUNT;


/// to check whether sufficient money is available inside ATM or not
bool CashDispenser::isSufficientCashAvailable(int amount) {
    int billsRequired = amount / 500;

    /// there are available notes
    if(count >= billsRequired) {
        return true;
    }
    /// insufficient notes
    else {
        return false;
    }
}

/// to dispense cash
void CashDispenser::dispenseCash(int amount) {
    int billsRequired = amount / 500; // number of BDT 500 notes required
    count -= billsRequired;
}

#endif //ATM_SIMULATION_CASHDISPENSER_H
