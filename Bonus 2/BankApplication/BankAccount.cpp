// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "BankAccount.h"

BankAccount::BankAccount()
{
    id = BankAccount::globalId++;
    balance = 0;
};
BankAccount::BankAccount(double balance)
{
    this->id = BankAccount::globalId++;
    this->balance = balance;
}
BankAccount::BankAccount(int idd, double balance)
{
    this->id = idd;
    BankAccount::globalId = max(idd, BankAccount::globalId) + 1;
    this->balance = balance;
}
void BankAccount::setClient(Client& client)
{
    this->client = &client;
}
int BankAccount::getId()
{
    return id;
}
double BankAccount::getBalance()
{
    return balance;
}
int BankAccount::getType()
{
    return 1;
}
double BankAccount::getMinimumBalance()
{
    return -1;
}

bool BankAccount::withdraw(double amount)
{
    if (balance > amount)
    {
        balance -= amount;
        return true;
    }
    return false;
}
bool BankAccount::deposit(double amount)
{
    balance += amount;
    return true;
}
int BankAccount::BankAccount::globalId = 0;