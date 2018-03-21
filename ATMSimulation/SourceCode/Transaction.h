#ifndef ATM_SIMULATION_TRANSACTION_H
#define ATM_SIMULATION_TRANSACTION_H

#include "Screen.h"
#include "BankDB.h"
#include "ATMTime.h"

class Transaction {
protected:
    int accountNumber;
	Screen screen;
	ATMTime timeNow;
	static BankDB bankDB;

public:
    Transaction(int userAccountNumber, Screen atmScreen, BankDB atmBankDB);
    virtual void execute() = 0;
};

BankDB Transaction::bankDB;

Transaction::Transaction(int userAccountNumber, Screen atmScreen, BankDB atmBankDB) {
    accountNumber = userAccountNumber;
    screen = atmScreen;
    bankDB = atmBankDB;
}

#endif //ATM_SIMULATION_TRANSACTION_H
