#ifndef ATM_SIMULATION_ATM_H
#define ATM_SIMULATION_ATM_H

#include <fstream>
#include "Screen.h"
#include "Keypad.h"
#include "CashDispenser.h"
#include "DepositSlot.h"
#include "BankDB.h"
#include "BalanceInquiry.h"
#include "Deposit.h"
#include "Withdrawal.h"
#include "ATMTime.h"

using namespace std;

// macros corresponding to Main Menu selection
#define BALANCE_INQUIRY 1
#define WITHDRAWAL 2
#define DEPOSIT 3
#define EXIT 4

class ATM {
private:
    bool userAuthenticated;
    int currentAccountNumber;
    Screen screen;
    Keypad keypad;
    CashDispenser cashDispenser;
    DepositSlot depositSlot;
    BankDB bankDB;
    ATMTime timeNow;

    void authenticateUser();
    int displayMainMenu();
    void performTransactions();
    //Transaction& createTarnsaction(int type);

public:
    ATM();
    void run();
};

ATM::ATM() {
    userAuthenticated = false;
    currentAccountNumber = 0;
    bankDB.fetchInfoFromDatabase();
}

/// attempts to authenticate user against bank database
void ATM::authenticateUser() {
    screen.displayMessage("\nPlease Enter Your Account Number : ");
    int accountNumber = keypad.getInput();
    screen.displayMessage("\nEnter Your PIN : ");
    int pin = keypad.getInput();

    // set userAuthenticated to boolean value returned by bank database
    userAuthenticated = bankDB.authenticateUser(accountNumber, pin);

    // check whether authentication succeeded
    if (userAuthenticated) {
        currentAccountNumber = accountNumber;
    }
    else {
        screen.displayMessageNewLine("Invalid Account Number or PIN. Please Try Again.");
    }
}

/// display the Main Menu and return an input selection
int ATM::displayMainMenu() {
    screen.displayMessageNewLine("\nMain Menu :");
    screen.displayMessageNewLine("1 - View My Balance");
    screen.displayMessageNewLine("2 - Withdraw Cash");
    screen.displayMessageNewLine("3 - Deposit Funds");
    screen.displayMessageNewLine("4 - Exit\n");
    screen.displayMessage("Enter a choice : ");
    return keypad.getInput();
}

/// display the Main Menu and perform Transaction
void ATM::performTransactions() {
    Transaction *currentTransaction;
    BalanceInquiry objBI(currentAccountNumber, screen, bankDB);
    Withdrawal objW(currentAccountNumber, screen, bankDB, keypad, cashDispenser);
    Deposit objD(currentAccountNumber, screen, bankDB, keypad, depositSlot);

    bool userExited = false; // user has not chosen to exit

    // loop while user has not chosen option to exit the system
    while (!userExited) {
        // show Main Menu and get user selection
        int mainMenuSelection = displayMainMenu();

        // decide how to proceed based on user's menu selection
        switch (mainMenuSelection) {
            case BALANCE_INQUIRY:
                currentTransaction = &objBI;
                currentTransaction->execute();
                break;

            case WITHDRAWAL:
                currentTransaction = &objW;
                currentTransaction->execute();
                break;

            case DEPOSIT:
                currentTransaction = &objD;
                currentTransaction->execute();
                break;

            case EXIT:
                screen.displayMessageNewLine("\nExiting The System...");
                userExited = true;
                break;

            default:
                screen.displayMessageNewLine("\nYou did not enter a valid selection. Try again.");
                break;
        }
    }
}

/// start ATM
void ATM::run() {
    while (true) {
        while (!userAuthenticated) {
            screen.displayMessageNewLine("\nWelcome !");
            authenticateUser();
        }

        /// user is now authenticated
        /// write user logged in time
        fstream fout;
        fout.open("UserLog.DAT", ios::app);
        fout << timeNow.getTimeNow() << ": Logged In - User " << currentAccountNumber << endl;
        fout.close();

        performTransactions();

        /// write user logged out time
        fout.open("UserLog.DAT", ios::app);
        fout << timeNow.getTimeNow() << ": Logged Out - User " << currentAccountNumber << endl;
        fout.close();

        userAuthenticated = false; // reset before next ATM session
        currentAccountNumber = 0; // reset before next ATM session
        screen.displayMessageNewLine("\nThank You! Goodbye!");
    }
}

#endif //ATM_SIMULATION_ATM_H
