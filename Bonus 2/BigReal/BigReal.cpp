// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "BigReal.h"

BigReal::BigReal() // Default constructor
{
    string real = "0.0";
    splitNumber(real, integer, decimal);
    decimalPos = real.length() - real.find('.') - 1;
    real.erase(real.find('.'), 1);
    fullNumber = BigDecimalInt(real);
}
BigReal::BigReal(string real) // constructor
{
    decimalPos = 0;
    if (!hasDecimalPoint(real))
    {
        real += ".0";
    }
    real = removeSucceedingZeros(real);
    regex check("[-+]?([0-9]*.[0-9]+|[0-9]+)");
    if (regex_match(real, check))
    {
        splitNumber(real, integer, decimal);
        decimalPos = real.length() - real.find('.') - 1;
        real.erase(real.find('.'), 1);
        fullNumber = BigDecimalInt(real);
    }
    else
    {
        cout << "Invalid Number.\n";
        exit(1);
    }
}
BigReal::BigReal(double num) // double constructor
{
    string real = removeSucceedingZeros(to_string(num));
    if (!hasDecimalPoint(real))
    {
        real += ".0";
    }
    splitNumber(real, integer, decimal);
    decimalPos = real.length() - real.find('.') - 1;
    real.erase(real.find('.'), 1);
    fullNumber = BigDecimalInt(real);
}
BigReal::BigReal(BigDecimalInt BigInteger)
{
    string real = removeSucceedingZeros(getSign(BigInteger) + BigInteger.getNumber() + ".0");
    splitNumber(real, integer, decimal);
    decimalPos = real.length() - real.find('.') - 1;
    real.erase(real.find('.'), 1);
    fullNumber = BigDecimalInt(real);
}
// Copy Constractor
BigReal::BigReal(const BigReal &other)
{
    fullNumber = other.fullNumber;
    integer = other.integer;
    decimal = other.decimal;
    decimalPos = other.decimalPos;
}
// Move constructor
BigReal::BigReal(BigReal &&other)
    : fullNumber(move(other.fullNumber)), integer(move(other.integer)), decimal(move(other.decimal)), decimalPos{move(other.decimalPos)}
{
    cout << "Moved\n";
}
// Assignment assignment
BigReal &BigReal::BigReal::operator=(BigReal &&other)
{
    if (this != &other)
    {


        fullNumber = other.fullNumber;
        integer = other.integer;
        decimal = other.decimal;
        decimalPos = other.decimalPos;
    }
    return *this;
}
// Move operator
BigReal &BigReal::operator=(BigReal &other)
{
    if (this != &other)
    {


        fullNumber = other.fullNumber;
        integer = other.integer;
        decimal = other.decimal;
        decimalPos = other.decimalPos;

        delete &other.fullNumber;
        delete &other.decimalPos;
        delete &other.integer;
        delete &other.decimal;
    }
    return *this;
}
BigReal BigReal::operator+(BigReal &anotherDec)
{
    int furthestDecimalPos = max(decimalPos, anotherDec.decimalPos); // furthest from right
    BigReal *longestDecimal = this;
    BigReal *shortestDecimal = &anotherDec;
    int difference = decimalPos - anotherDec.decimalPos;
    if (decimalPos != furthestDecimalPos)
    {
        longestDecimal = &anotherDec;
        shortestDecimal = this;
        difference *= -1;
    }
    string shortest = addZerosToEnd(getNumberWithoutPoint(shortestDecimal), difference);
    BigDecimalInt sum = longestDecimal->fullNumber + BigDecimalInt(shortest);
    return removePrecceedingZeros(removeSucceedingZeros(addZerosToStart(getNumberWithoutPoint(sum), shortest.length() - getNumberWithoutPoint(sum).length()).insert(addZerosToStart(getNumberWithoutPoint(sum), shortest.length() - getNumberWithoutPoint(sum).length()).length() - furthestDecimalPos, ".")));
}

BigReal BigReal::operator-(BigReal &anotherDec)
{
    BigReal secondNumber = anotherDec;
    secondNumber.fullNumber = flipSign(getNumberWithoutPoint(&secondNumber));
    return *this + secondNumber;
}

bool BigReal::operator<(BigReal anotherDec)
{
    if (integer < anotherDec.integer)
    {
        return true;
    }
    else if (integer == anotherDec.integer)
    {
        BigDecimalInt *smallest = &decimal;
        int difference = decimal.getNumber().length() - anotherDec.decimal.getNumber().length();
        if (anotherDec.decimal.getNumber().length() < decimal.getNumber().length())
        {
            smallest = &anotherDec.decimal;
        }
        difference = ((difference < 0) ? difference * -1 : difference);
        smallest->setNumber(getSign(*smallest) + addZerosToEnd(smallest->getNumber(), difference));
        return decimal < anotherDec.decimal;
    }
    return false;
}
bool BigReal::operator>(BigReal anotherDec)
{
    if (integer > anotherDec.integer)
    {
        return true;
    }
    else if (integer == anotherDec.integer)
    {
        BigDecimalInt *smallest = &decimal;
        int difference = decimal.getNumber().length() - anotherDec.decimal.getNumber().length();
        if (anotherDec.decimal.getNumber().length() < decimal.getNumber().length())
        {
            smallest = &anotherDec.decimal;
        }
        difference = ((difference < 0) ? difference * -1 : difference);
        smallest->setNumber(getSign(*smallest) + addZerosToEnd(smallest->getNumber(), difference));
        return decimal > anotherDec.decimal;
    }
    return false;
}

bool BigReal::operator==(BigReal anotherDec)
{
    if (integer == anotherDec.integer)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int BigReal::size()
{
    return fullNumber.size();
}
int BigReal::sign()
{
    if (fullNumber.sign() == 1)
        // positive
        return 1;
    else
        // negative
        return 0;
}
ostream &operator<<(ostream &out, BigReal Real)
{
    out << Real.getNumber();
    return out;
}

istream &operator>>(istream &in, BigReal &num)
{
    string real;
    in >> real;
    num = BigReal(real);
    return in;
}
string BigReal::getNumber()
{
    return getNumberWithoutPoint(this).insert(getNumberWithoutPoint(this).length() - decimalPos, ".");
}

bool BigReal::hasDecimalPoint(string real)
{
    return real.find('.') != -1;
}
string BigReal::getNumberWithoutPoint(BigDecimalInt n)
{
    return getSign(n) + n.getNumber();
}
string BigReal::getNumberWithoutPoint(BigReal *n)
{
    return getSign(*n) + n->fullNumber.getNumber();
}
string BigReal::addZerosToEnd(string s, int amount)
{
    for (int i = 0; i < amount; i++)
    {
        s += "0";
    }
    return s;
}
string BigReal::addZerosToStart(string s, int amount)
{
    string sign = ((s[0] == '-') ? "-" : "+");
    if (!isdigit(s[0]))
    {
        s.erase(0, 1);
    }
    for (int i = 0; i < amount; i++)
    {
        s = "0" + s;
    }
    return sign + s;
}
string BigReal::removeSucceedingZeros(string s)
{
    int pos = s.find('.');
    while (((s.length() - 2) != pos) && (s[s.length() - 1] == '0'))
    {
        s = s.erase(s.length() - 1, 1);
    }
    return s;
}
string BigReal::removePrecceedingZeros(string s)
{
    string sign = ((s[0] == '-') ? "-" : "+");
    if (!isdigit(s[0]))
    {
        s.erase(0, 1);
    }
    while ((s[1] != '.') && (s[0] == '0'))
    {
        s = s.erase(0, 1);
    }
    return sign + s;
}
string BigReal::getSign(BigDecimalInt n)
{
    return ((n.sign() == 1) ? "+" : "-");
}
string BigReal::getSign(BigReal n)
{
    return ((n.fullNumber.sign() == 1) ? "+" : "-");
}
string BigReal::flipSign(string s)
{
    s[0] = ((s[0] == '-') ? '+' : '-');
    return s;
}
void BigReal::splitNumber(string real, BigDecimalInt &integer, BigDecimalInt &decimal)
{
    string integerString, decimalString;
    string *ptr = &integerString;
    string sign = (((isdigit(real[0]) || real[0] == '+') ? "+" : "-"));
    for (int i = 0; i < real.length(); i++)
    {
        if (!isdigit(real[i]))
        {
            if (real[i] == '.')
            {
                ptr = &decimalString;
            }
        }
        else
        {
            *ptr += real[i];
        }
    }
    integer = BigDecimalInt(sign + integerString);
    decimal = BigDecimalInt(sign + decimalString);
}
