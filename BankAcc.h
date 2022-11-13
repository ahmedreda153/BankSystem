#ifndef BankAcc_H
#define BankAcc_H

#pragma once

#include "Client.h"
#include <iostream>
#include <string>

using namespace std;

class Client;

class BankAcc
{
protected:
    string accountID;
    double balance;
    string type;
    Client *bankClient;

public:
    static int accountCount;
    BankAcc();
    BankAcc(double bal);
    void setAccountID(string ID);
    virtual bool setBalance(double bal);
    void setType(string t);
    void setClient(Client &c);
    string getAccountID();
    double getBalance();
    string getType();
    Client *getClient();
    virtual bool withdraw(double amount);
    virtual bool deposit(double amount);
};

#endif