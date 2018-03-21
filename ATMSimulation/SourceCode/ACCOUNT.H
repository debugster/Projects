#ifndef ATM_SIMULATION_ACCOUNT_H
#define ATM_SIMULATION_ACCOUNT_H

class Account {
private:
    int accountNumber;
    int pin;
    double availableBalance;
    double totalBalance;

public:
    Account();
    Account(int theAccountNumber, int thePIN, double theAvailableBalance, double theTotalBalance);
    bool validatePIN(int userPIN);
    void credit(double amount);
    void debit(double amount);
    int getAccountNumber();
    int getPIN();
    double getAvailableBalance();
    double getTotalBalance();
};

Account::Account()
{
    accountNumber = 0;
    pin = 0;
    availableBalance = 0.0;
    totalBalance = 0.0;
}

Account::Account(int theAccountNumber, int thePIN, double theAvailableBalance, double theTotalBalance) {
    accountNumber = theAccountNumber;
    pin = thePIN;
    availableBalance = theAvailableBalance;
    totalBalance = theTotalBalance;
}

/// to validate user PIN
bool Account::validatePIN(int userPIN) {
    if (userPIN == pin) {
        return true;
    }

    return false;
}

/// to credit the balance
void Account::credit(double amount) {
    totalBalance += amount;
}

/// to debit the balance
void Account::debit(double amount) {
    availableBalance -= amount;
    totalBalance -= amount;
}

/// to get the account number
int Account::getAccountNumber() {
    return accountNumber;
}

/// to get the pin number for writing to file purpose
int Account::getPIN()
{
    return pin;
}

/// to get the available balance
double Account::getAvailableBalance() {
    return availableBalance;
}

/// to get the total balance
double Account::getTotalBalance() {
    return totalBalance;
}

#endif //ATM_SIMULATION_ACCOUNT_H
