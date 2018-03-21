#ifndef ATM_SIMULATION_BALANCEINQUIRY_H
#define ATM_SIMULATION_BALANCEINQUIRY_H

#include "Transaction.h"

class BalanceInquiry : public Transaction {
public:
    BalanceInquiry(int userAccountNumber, Screen atmScreen, BankDB atmBankDB);
    void execute();
};

BalanceInquiry::BalanceInquiry(int userAccountNumber, Screen atmScreen, BankDB atmBankDB) : Transaction(userAccountNumber, atmScreen, atmBankDB) {
    /// empty body
}

void BalanceInquiry::execute() {
    bankDB.fetchInfoFromDatabase();
    double availableBalance = bankDB.getAvailableBalance(accountNumber);
    double totalBalance = bankDB.getTotalBalance(accountNumber);

    // display the balance info on the screen
    screen.displayMessageNewLine("\nBalance Information :");
    screen.displayMessage(" - Available Balance\t: ");
    screen.displayBDTAmount(availableBalance);
    screen.displayMessage(" - Total Balance\t: ");
    screen.displayBDTAmount(totalBalance);
    screen.displayMessage("\n");
}

#endif //ATM_SIMULATION_BALANCEINQUIRY_H
