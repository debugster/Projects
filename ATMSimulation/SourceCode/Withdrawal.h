#ifndef ATM_SIMULATION_WITHDRAWAL_H
#define ATM_SIMULATION_WITHDRAWAL_H

#include <fstream>
#include "Transaction.h"
#include "CashDispenser.h"
#include "Keypad.h"

using namespace std;

#define CANCELED_W 6

class Withdrawal : public Transaction {
private:
    int amount; // amount to withdraw
    Keypad keypad;
    CashDispenser cashDispenser;

    int displayMenuOfAmounts();

public:
    Withdrawal(int userAccountNumber, Screen atmScreen, BankDB atmBankDB, Keypad atmKeypad, CashDispenser atmCashDispenser);
    void execute();
};


Withdrawal::Withdrawal(int userAccountNumber, Screen atmScreen, BankDB atmBankDB, Keypad atmKeypad, CashDispenser atmCashDispenser) : Transaction(userAccountNumber, atmScreen, atmBankDB) {
    keypad = atmKeypad;
    cashDispenser = atmCashDispenser;
}

/// display a menu of withdrawal amounts and the option to cancel
/// return the chosen amount or 0 if the user chooses to cancel
int Withdrawal::displayMenuOfAmounts() {
    int userChoice = 0; // local variable to return value

    // array of amounts to correspond to menu numbers
    int amounts[] = {0, 500, 1000, 2000, 4000, 10000};

    // loop while no valid choice has been made
    while (userChoice == 0) {
        screen.displayMessageNewLine("\nWithdrawal Menu:");
        screen.displayMessageNewLine("1 - BDT 500");
        screen.displayMessageNewLine("2 - BDT 1000");
        screen.displayMessageNewLine("3 - BDT 2000");
        screen.displayMessageNewLine("4 - BDT 5000");
        screen.displayMessageNewLine("5 - BDT 10000");
        screen.displayMessageNewLine("6 - Cancel Transaction");
        screen.displayMessage("Choose an option : ");

        int input = keypad.getInput();

        // determine how to proceed based on input value
        switch (input) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                userChoice = amounts[input];
                break;
            case CANCELED_W:
                userChoice = CANCELED_W;
                break;
            default:
                screen.displayMessageNewLine("\nInvalid selection. Please Try Again.");
        }
    }
    return userChoice;
}

void Withdrawal::execute() {
    bool cashDispensed = false;
    double availableBalance;

    bankDB.fetchInfoFromDatabase();

    // loop until cash is dispensed or the user cancels
    do {
        // obtain a chosen withdrawal amount from the user
        amount = displayMenuOfAmounts();

        if (amount != CANCELED_W) {
            // get available balance of account involved
            availableBalance = bankDB.getAvailableBalance(accountNumber);

            // check whether the user has enough money in his/her account
            if (amount <= availableBalance) {
                // check whether the cash dispenser has enough money
                if (cashDispenser.isSufficientCashAvailable(amount)) {
                    // proceed to transaction
                    bankDB.debit(accountNumber, amount);
                    bankDB.writeToDatabase();
                    cashDispenser.dispenseCash(amount);
                    cashDispensed = true;

                    /// Keep log about withdrawn amount for further verification
                    fstream fout;
                    fout.open("UserLog.DAT", ios::app);
                    fout << timeNow.getTimeNow() << ": Withdrawn BDT " << amount << " - User " << accountNumber << endl;

                    screen.displayMessageNewLine("\nYour cash has been dispensed. Please take your cash now.");
                }
                // if cash dispenser doesn't have enough money
                else {
                    screen.displayMessageNewLine("\nInsufficient cash available in the ATM.");
                    screen.displayMessageNewLine("\nPlease choose a smaller amount.");
                }
            }
            // if not enough money available in user's account
            else {
                screen.displayMessageNewLine("\nInsufficient funds in your account.");
                screen.displayMessageNewLine("\nPlease choose a smaller amount");
            }
        }
        // if user chose cancel menu option
        else {
            screen.displayMessageNewLine("\nCanceling transaction...");
            return;
        }
    } while(!cashDispensed);
}

#endif //ATM_SIMULATION_WITHDRAWAL_H
