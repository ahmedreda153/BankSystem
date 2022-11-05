#ifndef Client_H
#define Client_H

#pragma once

#include "BankAcc.h"
#include <iostream>
#include <string>

using namespace std;

class BankAcc;

class Client
{
private:
    string name;
    string address;
    string phone;
    BankAcc *bankAccount;

public:
    Client();
    void setName(string n);
    void setAddress(string a);
    void setPhone(string p);
    void setBankAccount(BankAcc &acc);
    string getName();
    string getAddress();
    string getPhone();
    BankAcc *getBankAccount();
};

#endif