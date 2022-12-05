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