// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Client.h"

Client::Client(string name, string address, string phoneNumber)
{
    this->name = name;
    this->address = address;
    this->phoneNumber = phoneNumber;
}

string Client::getName()
{
    return name;
}
string Client::getAddress()
{
    return address;
}
string Client::getPhoneNumber()
{
    return phoneNumber;
}
BankAccount* Client::getAccount()
{
    return account;
}

void Client::setAccount(BankAccount& account)
{
    this->account = &account;
}