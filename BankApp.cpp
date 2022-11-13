#include "BankApp.h"
#include "Client.h"
#include "BankAcc.h"
#include "SavingsBankAcc.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

BankAcc::BankAcc()
{
    balance = 0;
}

BankAcc::BankAcc(double bal)
{
    balance = bal;
}

void BankAcc::setAccountID(string ID)
{
    accountID = ID;
}

bool BankAcc::setBalance(double bal)
{
    if (bal >= 0)
    {
        balance = bal;
        return true;
    }
    else
    {
        return false;
    }
}

void BankAcc::setType(string t)
{
    type = t;
}

void BankAcc::setClient(Client &c)
{
    bankClient = &c;
}

string BankAcc::getAccountID()
{
    return accountID;
}

double BankAcc::getBalance()
{
    return balance;
}

string BankAcc::getType()
{
    return type;
}

Client *BankAcc::getClient()
{
    return bankClient;
}

bool BankAcc::withdraw(double amount)
{
    if (amount <= balance && amount > 0)
    {
        balance -= amount;
        return true;
    }
    else
    {
        return false;
    }
}

bool BankAcc::deposit(double amount)
{
    if (amount > 0)
    {
        balance += amount;
        return true;
    }
    else
    {
        return false;
    }
}

SavingsBankAcc::SavingsBankAcc()
{
    minimumBalance = 1000;
}

double SavingsBankAcc::setMinimumBalance(double min)
{
    minimumBalance = min;
}

double SavingsBankAcc::getMinimumBalance()
{
    return minimumBalance;
}

bool SavingsBankAcc::setBalance(double bal)
{
    if (bal >= minimumBalance)
    {
        balance = bal;
        return true;
    }
    else
    {
        return false;
    }
}

bool SavingsBankAcc::withdraw(double amount)
{
    if (balance - amount >= minimumBalance && amount > 0)
    {
        balance -= amount;
        return true;
    }
    else
    {
        return false;
    }
}

bool SavingsBankAcc::deposit(double amount)
{
    if (amount >= 100)
    {
        balance += amount;
        return true;
    }
}

Client::Client()
{
    name = "unknown";
    address = "unknown";
    phone = "unknown";
}

void Client::setName(string n)
{
    name = n;
}

void Client::setAddress(string a)
{
    address = a;
}

void Client::setPhone(string p)
{
    phone = p;
}

void Client::setBankAccount(BankAcc &b)
{
    bankAccount = &b;
}

string Client::getName()
{
    return name;
}

string Client::getAddress()
{
    return address;
}

string Client::getPhone()
{
    return phone;
}

BankAcc *Client::getBankAccount()
{
    return bankAccount;
}

int BankAcc::accountCount = 0;

bool BankApp::addClient()
{
    string name;
    string address;
    string phone;
    int accType;
    double balance;
    Client *c = new Client();
    BankAcc *b = new BankAcc();
    SavingsBankAcc *s = new SavingsBankAcc();

    BankAcc::accountCount++;
    string accountID = "FCAI-" + to_string(BankAcc::accountCount);

    cout << "Enter client name: ";
    cin.ignore();
    getline(cin, name);
    c->setName(name);

    cout << "Enter client address: ";
    // cin.ignore();
    getline(cin, address);
    c->setAddress(address);

    cout << "Enter client phone: ";
    // cin.ignore();
    getline(cin, phone);
    c->setPhone(phone);

    cout << "What Type of Account Do You Like? (1) Basic (2) Saving => Type 1 or 2 : ";
    cin >> accType;

    if (accType == 1)
    {
        b->setType("Basic");
        b->setAccountID(accountID);
        cout << "Please Enter the Starting Balance : ";
        cin >> balance;
        while (b->setBalance(balance) == false)
        {
            cout << "you can't enter negative balance, please enter again : ";
            cin >> balance;
        }
        c->setBankAccount(*b);
        vecAccounts.push_back(b);
        vecClients.push_back(c);
    }
    else if (accType == 2)
    {
        s->setType("Saving");
        s->setAccountID(accountID);
        cout << "Please Enter the Starting Balance : ";
        cin >> balance;
        while (s->setBalance(balance) == false)
        {
            cout << "Your starting balance must be greater than the minimum balance" << endl;
            cout << "The minimum balance is " << s->getMinimumBalance() << endl;
            cout << "Please Enter the Starting Balance : ";
            cin >> balance;
        }
        c->setBankAccount(*s);
        vecAccounts.push_back(s);
        vecClients.push_back(c);
    }
    else
    {
        cout << "Invalid Type" << endl;
        return false;
    }
    cout << "An account was created with ID " << vecAccounts[BankAcc::accountCount - 1]->getAccountID();
    cout << " and Starting Balance " << vecAccounts[BankAcc::accountCount - 1]->getBalance() << endl;
    return true;
}

void BankApp::listClients()
{
    cout << endl
         << "List of Clients and Accounts" << endl;
    for (int i = 0; i < vecClients.size(); i++)
    {
        cout << endl
             << "Client No. " << i + 1 << endl;
        cout << "       Client Name: " << vecClients[i]->getName() << endl;
        cout << "       Client Address: " << vecClients[i]->getAddress() << endl;
        cout << "       Client Phone: " << vecClients[i]->getPhone() << endl;
        cout << "       Account ID: " << vecClients[i]->getBankAccount()->getAccountID() << endl;
        cout << "       Account Type: " << vecClients[i]->getBankAccount()->getType() << endl;
        cout << "       Account Balance: " << vecClients[i]->getBankAccount()->getBalance() << endl;
    }
}

void BankApp::withdraw()
{
    string accID;
    double amount;
    cout << "Enter Account ID: ";
    cin >> accID;
    for (int i = 0; i < vecAccounts.size(); i++)
    {
        if (vecAccounts[i]->getAccountID() == accID)
        {
            cout << endl
                 << "Account ID: " << vecAccounts[i]->getAccountID() << endl;
            cout << "Account Type: " << vecAccounts[i]->getType() << endl;
            cout << "Account Balance: " << vecAccounts[i]->getBalance() << endl;
            cout << "Enter Amount to Withdraw: ";
            cin >> amount;
            while (vecAccounts[i]->withdraw(amount) == false)
            {
                cout << "Sorry. This is more than you can withdraw" << endl;
                cout << "Account Balance: " << vecAccounts[i]->getBalance() << endl;
                cout << "Please enter a valid amount: ";
                cin >> amount;
            }
            cout << "Thank you. Your new balance is " << vecAccounts[i]->getBalance() << endl;
        }
    }
}

void BankApp::deposit()
{
    string accID;
    double amount;
    cout << "Enter Account ID: ";
    cin >> accID;
    for (int i = 0; i < vecAccounts.size(); i++)
    {
        if (vecAccounts[i]->getAccountID() == accID)
        {
            cout << endl
                 << "Account ID: " << vecAccounts[i]->getAccountID() << endl;
            cout << "Account Type: " << vecAccounts[i]->getType() << endl;
            cout << "Account Balance: " << vecAccounts[i]->getBalance() << endl;
            cout << "Enter Amount to Deposit: ";
            cin >> amount;
            while (vecAccounts[i]->deposit(amount) == false)
            {
                cout << "Sorry. This is less than what you can deposit" << endl;
                cout << "Minimum Deposit Amount is 100, Please enter a valid amount : ";
                cin >> amount;
            }
            cout << "Thank you. Your new balance is " << vecAccounts[i]->getBalance() << endl;
        }
    }
}

void BankApp::run()
{
    int choice;
    do
    {
        cout << endl
             << "Welcome to FCAI Banking Application" << endl;
        cout << "1. Create a New Account" << endl;
        cout << "2. List Clients and Accounts" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Deposit Money" << endl;
        cout << "5. Exit" << endl;
        cout << "Please Enter Choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addClient();
            break;
        case 2:
            listClients();
            break;
        case 3:
            withdraw();
            break;
        case 4:
            deposit();
            break;
        case 5:
            cout << "Thank you for using FCAI Banking Application" << endl;
            break;
        default:
            cout << "Invalid Choice" << endl;
            break;
        }
    } while (choice == 1 || choice == 2 || choice == 3 || choice == 4);
}