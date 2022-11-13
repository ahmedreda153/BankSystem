#ifndef SavingsBankAcc_H
#define SavingsBankAcc_H

#pragma once

#include "BankAcc.h"
#include <iostream>
#include <string>

using namespace std;

class SavingsBankAcc: public BankAcc
{
private:
    double minimumBalance;

public:
    SavingsBankAcc();
    double setMinimumBalance(double min);
    double getMinimumBalance();
    bool setBalance(double bal);
    bool withdraw(double amount);
    bool deposit(double amount);
};

#endif