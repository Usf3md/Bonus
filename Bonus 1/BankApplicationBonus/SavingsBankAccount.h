#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "BankAccount.h"

class SavingsBankAccount : public BankAccount
{
    int minimumBalance = 1000;

public:
    SavingsBankAccount(double balance, double minimumBalance);
    SavingsBankAccount(int id, double balance, double minimumBalance);
    int getType();
    double getMinimumBalance();
    bool withdraw(double amount);
    bool deposit(double amount);
};