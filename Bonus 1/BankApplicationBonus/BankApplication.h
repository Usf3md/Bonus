#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Client.h"
#include "BankAccount.h"
#include "SavingsBankAccount.h"
using namespace std;
class BankApplication
{
    vector<Client> clients;
    fstream database;

public:
    BankApplication();
    void saveData();
    bool addClient(string name, string address, string phoneNumber, double balance, double minimumBalance, int accountType);
    int checkClient(int id);
    string getPrefixedId(Client client, string prefix);
    string getPrefixedId(int id, string prefix);
    void run();
};