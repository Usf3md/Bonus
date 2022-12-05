#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "BankAccount.h"
using namespace std;

class Client
{
private:
    string name;
    string address;
    string phoneNumber;
    BankAccount *account = nullptr;

public:
    Client(string name, string address, string phoneNumber);
    string getName();
    string getAddress();
    string getPhoneNumber();
    BankAccount *getAccount();
    void setAccount(BankAccount &account);
};
