// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "BankApplication.h"
bool isNumber(string num)
{
    for (char el : num)
    {
        if (!isdigit(el))
        {
            return false;
        }
    }
    return num.length();
}

BankApplication::BankApplication()
{
    string name, address, phoneNumber, id, balance, minimumBalance, type;
    Client *tempClient;
    BankAccount *tempAccount = nullptr;
    database.open("db.txt");
    string tempStr;
    getline(database, tempStr);
    while (!database.eof())
    {
        getline(database, name, '|');
        getline(database, address, '|');
        getline(database, phoneNumber, '|');
        getline(database, id, '|');
        getline(database, balance, '|');
        getline(database, minimumBalance, '|');
        getline(database, type);
        tempClient = new Client(name, address, phoneNumber);
        if (type == "1")
        {
            tempAccount = new BankAccount(stoi(id), stoi(balance));
        }
        else
        {
            tempAccount = new SavingsBankAccount(stoi(id), stoi(balance), stoi(minimumBalance));
        }
        tempClient->setAccount(*tempAccount);
        tempAccount->setClient(*tempClient);
        clients.push_back(*tempClient);
        if (database.eof())
        {
            break;
        }
    }
    database.close();
}
void BankApplication::saveData()
{
    database.open("db.txt");
    database << "NAME|ADDRESS|PHONENUMBER|ID|BALANCE|MINIMUMBALANCE|TYPE";
    for (auto client : clients)
    {
        database << endl;
        database << client.getName() << "|";
        database << client.getAddress() << "|";
        database << client.getPhoneNumber() << "|";
        database << client.getAccount()->getId() << "|";
        database << client.getAccount()->getBalance() << "|";
        database << client.getAccount()->getMinimumBalance() << "|";
        database << client.getAccount()->getType();
    }
    database.close();
}
bool BankApplication::addClient(string name, string address, string phoneNumber, double balance, double minimumBalance, int accountType)
{
    for (auto client : clients)
    {
        if (client.getPhoneNumber() == phoneNumber)
        {
            return false;
        }
    }
    BankAccount *tempAccount = nullptr;
    Client *tempClient = new Client(name, address, phoneNumber);
    if (accountType == 1)
    {
        tempAccount = new BankAccount(balance);
    }
    else
    {
        tempAccount = new SavingsBankAccount(balance, minimumBalance);
    }
    tempClient->setAccount(*tempAccount);
    tempAccount->setClient(*tempClient);
    clients.push_back(*tempClient);
    saveData();
    return true;
}
int BankApplication::checkClient(int id)
{
    for (int i = 0; i < clients.size(); i++)
    {
        if (clients[i].getAccount()->getId() == id)
        {
            return i;
        }
    }
    return -1;
}
string BankApplication::getPrefixedId(Client client, string prefix)
{
    string s = prefix + '-';
    for (int i = 0; i < (3 - to_string(client.getAccount()->getId()).length()); i++)
    {
        s += '0';
    }
    s += to_string(client.getAccount()->getId());
    return s;
}
string BankApplication::getPrefixedId(int id, string prefix)
{
    string s = prefix + '-';
    for (int i = 0; i < (3 - to_string(id).length()); i++)
    {
        s += '0';
    }
    s += to_string(id);
    return s;
}
void BankApplication::run()
{
    char answer;
    string name, address, phoneNumber;
    int accountType;
    double balance, minimumBalance{-1};

    while (true)
    {
        cout << "1. Create a New Account" << endl;
        cout << "2. List Clients and Accounts" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Deposit Money" << endl;
        cout << "Please Enter Choice: ";
        cin >> answer;
        cin.ignore();
        if (answer == '1')
        {
            cout << "Please Enter Client Name: ";
            getline(cin, name);
            cout << "Please Enter Client Address: ";
            getline(cin, address);
            while (!isNumber(phoneNumber))
            {
                cout << "Please Enter Client Phone: ";
                getline(cin, phoneNumber);
            }
            while (true)
            {
                cout << "What Type of Account Do You Like? (1) Basic (2) Saving Type 1 or 2: ";
                cin >> accountType;
                if (accountType == 1 || accountType == 2)
                {
                    break;
                }
            }
            cout << "Please Enter the Starting Balance: ";
            cin >> balance;
            if (accountType == 2)
            {
                cout << "Please Enter the Minimum Balance: ";
                cin >> minimumBalance;
            }
            addClient(name, address, phoneNumber, balance, minimumBalance, accountType);
        }
        else if (answer == '2')
        {
            int dotsAmount = 80;
            for (auto client : clients)
            {
                if (client.getName().length() > dotsAmount)
                {
                    dotsAmount = (client.getName().length() * 1.5);
                }
                for (int i = 0; i < (dotsAmount - client.getName().length()) / 2; i++)
                {
                    cout << '-';
                }
                cout << client.getName();
                for (int i = 0; i < (dotsAmount - client.getName().length()) / 2; i++)
                {
                    cout << '-';
                }
                cout << endl;
                cout << "Address: " << client.getAddress() << endl;
                cout << "Phone Number: " << client.getPhoneNumber() << endl;
                cout << "Account ID: " << getPrefixedId(client, "FCAI") << endl;
                cout << "Balance: " << client.getAccount()->getBalance() << endl;
                cout << "Account Type : " << ((client.getAccount()->getType() == 1) ? "Basic" : "Savings") << endl;
            }
            for (int i = 0; i < dotsAmount; i++)
            {
                cout << "_";
            }
            cout << endl;
        }
        else if (answer == '3')
        {
            int accountId;
            cout << "Please Enter Account ID: ";
            cin >> accountId;
            int clientIndex = checkClient(accountId);
            if ((clientIndex != -1)) //-V547
            {
                double amount;
                cout << "Account ID: " << getPrefixedId(clients[clientIndex], "FCAI") << endl;
                cout << "Account Type : " << ((clients[clientIndex].getAccount()->getType() == 1) ? "Basic" : "Savings") << endl;
                cout << "Balance : " << clients[clientIndex].getAccount()->getBalance() << endl;
                while (true)
                {
                    cout << "Please Enter The Amount To withdraw: ";
                    cin >> amount;
                    if (clients[clientIndex].getAccount()->withdraw(amount))
                    {
                        break;
                    }
                    cout << "Sorry. This is more than what you can withdraw." << endl;
                }
                cout << "Thank you." << endl;
                cout << "Account ID: " << getPrefixedId(clients[clientIndex], "FCAI") << endl;
                cout << "New Balance : " << clients[clientIndex].getAccount()->getBalance() << endl;
                saveData();
            }
        }
        else if (answer == '4')
        {
            int accountId;
            cout << "Please Enter Account ID: ";
            cin >> accountId;
            int clientIndex = checkClient(accountId);
            if (clientIndex != -1) //-V547
            {
                double amount;
                cout << "Account ID: " << getPrefixedId(clients[clientIndex], "FCAI") << endl;
                cout << "Account Type : " << ((clients[clientIndex].getAccount()->getType() == 1) ? "Basic" : "Savings") << endl;
                cout << "Balance : " << clients[clientIndex].getAccount()->getBalance() << endl;
                while (true)
                {
                    cout << "Please Enter The Amount To deposit: ";
                    cin >> amount;
                    if (clients[clientIndex].getAccount()->deposit(amount))
                    {
                        break;
                    }
                    cout << "Sorry. This is less than what you can deposit." << endl;
                }
                cout << "Thank you." << endl;
                cout << "Account ID: " << getPrefixedId(clients[clientIndex], "FCAI") << endl;
                cout << "New Balance : " << clients[clientIndex].getAccount()->getBalance() << endl;
                saveData();
            }
        }
    }
}
