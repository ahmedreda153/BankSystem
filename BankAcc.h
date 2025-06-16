#ifndef BankAcc_H
#define BankAcc_H

#pragma once

#include "Client.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Client;

class BankAcc
{
protected:
    string accountID;
    double balance;
    string type;
    Client *bankClient;
    vector<double> feeHistory;
    bool active;
    string currency;

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
    bool transferFunds(BankAcc &destinationAccount, double amount);
    vector<double> getFeeHistory() const;
    bool setActive(bool status);
    bool isActive() const;
    bool setCurrency(string curr);
    string getCurrency() const;
    double getTotalFees() const;
};

#endif