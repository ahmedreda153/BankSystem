#ifndef SavingsBankAcc_H
#define SavingsBankAcc_H

#pragma once

#include "BankAcc.h"
#include <iostream>
#include <string>

using namespace std;

class SavingsBankAcc : public BankAcc
{
private:
    double minimumBalance;
    double interestRate;

public:
    SavingsBankAcc();
    double setMinimumBalance(double min);
    double getMinimumBalance();
    bool setBalance(double bal);
    bool withdraw(double amount);
    bool deposit(double amount);
    void setInterestRate(double rate);
    double getInterestRate() const;
    double calculateInterest(int months) const;
};

#endif