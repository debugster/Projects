#ifndef ATM_SIMULATION_DEPOSIT_H
#define ATM_SIMULATION_DEPOSIT_H

#include <fstream>
#include "Transaction.h"
#include "DepositSlot.h"
#include "Keypad.h"

using namespace std;

#define CANCELED_D 0

class Deposit : public Transaction {
private:
    int amount; // amount to deposit
	Keypad keypad;
	DepositSlot depositSlot;

	int promptForDepositAmount();

public:
    Deposit(int userAccountNumber, Screen atmScreen, BankDB atmBankDB, Keypad atmKeypad, DepositSlot atmDepositSlot);
    void execute();
};

Deposit::Deposit(int userAccountNumber, Screen atmScreen, BankDB atmBankDB, Keypad atmKeypad, DepositSlot atmDepositSlot) : Transaction(userAccountNumber, atmScreen, atmBankDB) {
    keypad = atmKeypad;
    depositSlot = atmDepositSlot;
}

/// get the amount user wants to deposit
int Deposit::promptForDepositAmount() {
    int userChoice;

    screen.displayMessageNewLine("\nPlease enter a deposit amount in BDT (or 0 to cancel) : ");
    int input = keypad.getInput();

    // check whether the user canceled or entered a valid amount
    if (input == CANCELED_D) {
        userChoice = CANCELED_D;
    }
    else if (input < 0) {
        screen.displayMessageNewLine("Invalid amount. Please enter a valid amount.");
    }
    else {
        userChoice = input;
    }
    return userChoice;
}

void Deposit::execute() {
    bankDB.fetchInfoFromDatabase();

    // get deposit amount from user
    amount = promptForDepositAmount();

    // check whether user entered a deposit amount or canceled
    if (amount != CANCELED_D) {
        screen.displayMessage("\nPlease insert a deposit envelope containing ");
        screen.displayBDTAmount(amount);
        screen.displayMessageNewLine(" in the Deposit Slot.");

        // receive deposit envelope
        bool envelopeReceived = depositSlot.isEnvelopeReceived();

        // check whether deposit envelope was received
        if (envelopeReceived) {
            screen.displayMessageNewLine("\nYour envelope has been received.");
            screen.displayMessageNewLine("NOTE : The money just deposited will not be available until we verify the amount of any enclosed cash and your checks clear.\n");
            // credit account to reflect the deposit
            // bankDB.credit(getAccountNumber(), amount);
            bankDB.credit(accountNumber, (double) amount);
            bankDB.writeToDatabase();

            /// Keep log about deposited amount for further verification
            fstream fout;
            fout.open("DepositLog.DAT", ios::app);
            fout << timeNow.getTimeNow() << ": Deposited BDT " << amount << " - User " << accountNumber << endl;
        }
        // if deposit envelope was not received
        else {
            screen.displayMessageNewLine("\nYou didn't insert an envelope, so the ATM has canceled your transaction.");
        }
    }
    // if user canceled the transaction
    else {
        screen.displayMessageNewLine("\nCanceling transaction...");
    }
}

#endif //ATM_SIMULATION_DEPOSIT_H
