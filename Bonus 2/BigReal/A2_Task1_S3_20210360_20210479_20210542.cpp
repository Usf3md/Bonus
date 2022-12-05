// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "BigReal.h"

int main()
{
    BigReal number{"1.2"};
    BigReal number2{"1.12"};
    BigReal number3{"000000000000.000123456"};
    BigReal number4{123456};
    BigReal number5{0.000000123456};
    BigReal number6;
    BigReal number7{BigDecimalInt("123456")};
    BigReal number8;
    cout << "Please enter Real Number: ";
    cin >> number8;
    cout << "Number 1: " << number << endl;
    cout << "Number 2: " << number2 << endl;
    cout << "number1 > number2: " << (number > number2) << endl;
    cout << "Number 3: " << number3 << endl;
    cout << "Number 4: " << number4 << endl;
    cout << "Number 5: " << number5 << endl;
    cout << "Number 6: " << number6 << endl;
    cout << "Number 7: " << number7 << endl;
    cout << "Number 8: " << number8 << endl;
}
