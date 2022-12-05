#include "BigDecimalIntClass.h"

class BigReal
{
    BigDecimalInt fullNumber;
    BigDecimalInt integer;
    BigDecimalInt decimal;
    int decimalPos;

public:
    BigReal();            // Default constructor
    BigReal(string real); // string constructor
    BigReal(double num);  // double constructor
    BigReal(BigDecimalInt BigInteger);
    BigReal(const BigReal &other);       // Copy constructor
    BigReal(BigReal &&other);            // Move constructor
    BigReal &operator=(BigReal &&other); // Assignment assignment
    BigReal &operator=(BigReal &other);  // Move operator
    BigReal operator+(BigReal &anotherDec);
    BigReal operator-(BigReal &anotherDec);
    bool operator<(BigReal anotherDec);
    bool operator>(BigReal anotherDec);
    bool operator==(BigReal anotherDec);
    int size();
    int sign();
    friend ostream &operator<<(ostream &out, BigReal Real);
    friend istream &operator>>(istream &in, BigReal &num);
    string getNumber();

private:
    bool hasDecimalPoint(string real);
    string getNumberWithoutPoint(BigDecimalInt n);
    string getNumberWithoutPoint(BigReal *n);
    string addZerosToEnd(string s, int amount);
    string addZerosToStart(string s, int amount);
    string removeSucceedingZeros(string s);
    string removePrecceedingZeros(string s);
    string getSign(BigDecimalInt n);
    string getSign(BigReal n);
    string flipSign(string s);
    void splitNumber(string real, BigDecimalInt &integer, BigDecimalInt &decimal);
};
