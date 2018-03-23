#ifndef ATM_SIMULATION_BANKDB_H
#define ATM_SIMULATION_BANKDB_H

#include <fstream>
#include <cstdlib>
#include <vector>
#include "Account.h"
#include "Screen.h"

using namespace std;

class BankDB {
private:
    static vector<Account>accounts; /// to hold all available users' information from database
    Account currentAccount;

public:
    BankDB();
    void fetchInfoFromDatabase();
    Account* getAccount(int accountNumber);
    bool authenticateUser(int userAccountNumber, int userPIN);
    double getAvailableBalance(int userAccountNumber);
    double getTotalBalance(int userAccountNumber);
    void credit(int userAccountNumber, double amount);
    void debit(int userAccountNumber, double amount);
    void writeToDatabase();
};

vector<Account> BankDB::accounts;

BankDB::BankDB() {
    /// demo
}

/// retrieve account information from database
void BankDB::fetchInfoFromDatabase()
{
    //accounts[0] = new Account(12345, 4321, 1000.0, 1200.0);
    //accounts[1] = new Account(98765, 5678, 500.0, 500.0);

    ifstream fin;

    /// retrieving user account information
    fin.open("AccountInfo.DAT");

    /// checking whether user account information file exists or not
    if (!fin) {
        Screen screen;
        screen.displayMessageNewLine("Account Information File does not exist!");
        exit(1);
    }

    int accNum, pin, totalAcc;
    double availBalance, totalBalance;
    accounts.clear();

    /// number of accounts available in database
    fin >> totalAcc;
    /// reading user account information file
    for (int i = 1; i <= totalAcc; i++) {
        fin >> accNum >> pin >> availBalance >> totalBalance;
        Account acc(accNum, pin, availBalance, totalBalance);
        accounts.push_back(acc);
    }

    fin.close();
}

/// retrieve Account object containing specified account number
Account* BankDB::getAccount(int accountNumber) {
    bool validUserFound = false;
    int i;

    /// loop through accounts searching for matching account number
    for(i = 0; i < accounts.size(); i++) {
        /// return current account if match found
        if (accounts[i].getAccountNumber() == accountNumber) {
            validUserFound = true;
            break;
        }
    }

    if (validUserFound) {
        return &accounts[i];
    }

    return &currentAccount;
}

/// determine whether user-specified account number and PIN match those of an account in the database
bool BankDB::authenticateUser(int userAccountNumber, int userPIN) {
    /// attempt to retrieve the account with the account number
    Account *userAccount = getAccount(userAccountNumber);

    /// If a valid account number is found
    if(userAccount->getAccountNumber() != 0) {
        return userAccount->validatePIN(userPIN);
    }
    else {
        return false;
    }
}

/// to get the available balance of the retrieved user
double BankDB::getAvailableBalance(int userAccountNumber) {
    return getAccount(userAccountNumber)->getAvailableBalance();
}

/// to get the total balance of the retrieved user
double BankDB::getTotalBalance(int userAccountNumber) {
    return getAccount(userAccountNumber)->getTotalBalance();
}

/// to credit the balance of the retrieved user
void BankDB::credit(int userAccountNumber, double amount) {
    getAccount(userAccountNumber)->credit(amount);
}

/// to debit the balance of the retrieved user
void BankDB::debit(int userAccountNumber, double amount) {
    getAccount(userAccountNumber)->debit(amount);
}

void BankDB::writeToDatabase()
{
    ofstream fout;

    fout.open("AccountInfo.DAT");
    if (!fout) {
        Screen screen;
        screen.displayMessageNewLine("Account Information File does not exist!");
        exit(1);
    }

    int totalAcc = accounts.size();
    fout << totalAcc << endl;

    for (int i = 0; i < totalAcc; i++) {
        fout << accounts[i].getAccountNumber() << " " << accounts[i].getPIN() << " " << accounts[i].getAvailableBalance() << " "  << accounts[i].getTotalBalance() << endl;
    }
    accounts.clear();

    fout.close();
}

#endif //ATM_SIMULATION_BANKDB_H
