#include "SavingsBankAccount.h"

SavingsBankAccount::SavingsBankAccount(double balance, double minimumBalance) : BankAccount(balance)
{
    this->minimumBalance = minimumBalance;
}
SavingsBankAccount::SavingsBankAccount(int id, double balance, double minimumBalance) : BankAccount(id, balance)
{
    this->minimumBalance = minimumBalance;
}
int SavingsBankAccount::getType()
{
    return 2;
}
double SavingsBankAccount::getMinimumBalance()
{
    return minimumBalance;
}
bool SavingsBankAccount::withdraw(double amount)
{
    if ((balance - amount) >= minimumBalance)
    {
        balance -= amount;
        return true;
    }
    return false;
}
bool SavingsBankAccount::deposit(double amount)
{
    if (amount >= 100)
    {
        balance += amount;
        return true;
    }
    return false;
}
