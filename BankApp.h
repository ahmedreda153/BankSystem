#ifndef BankApp_H
#define BankApp_H

#pragma once

#include "Client.h"
#include "BankAcc.h"
#include "SavingsBankAcc.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BankApp
{
private:
    vector<BankAcc*> vecAccounts;
    vector<Client*> vecClients;

public:
    bool addClient();
    void listClients();
    void withdraw();
    void deposit();
    void run();
};

#endif