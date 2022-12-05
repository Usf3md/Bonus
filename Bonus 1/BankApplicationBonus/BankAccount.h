#pragma once
using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
class Client;
class BankAccount
{
protected:
    static int globalId;
    int id;
    double balance;
    Client *client = nullptr;

public:
    BankAccount();
    BankAccount(double balance);
    BankAccount(int id, double balance);
    void setClient(Client &client);
    int getId();
    double getBalance();
    virtual int getType();
    virtual double getMinimumBalance();
    virtual bool withdraw(double amount);
    virtual bool deposit(double amount);
};