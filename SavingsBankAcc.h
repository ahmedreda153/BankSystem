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
    int lockPeriod; // Period in months during which withdrawals are restricted

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
    void setLockPeriod(int months);
    int getLockPeriod() const;
    bool withdrawWithLockCheck(double amount, int currentMonth);
    double calculateCompoundInterest(int months) const;
};

#endif