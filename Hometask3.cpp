#include "rationalNum.h"

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

//  Functions that will cut short on repeated mathematical operations

//  Absulote Value
int abs(int x) {
    if (x >= 0) {
        return x;
    }
    else {
        return -x;
    }
}


//  Finding the factors of some number
void getFactors(int num, vector<int>& factorSet) {
    if (num != 1) {
        factorSet.push_back(num);
    }
    for (int i = 2; i <= sqrt(static_cast<double>(num)); i++) {
        if (num % i == 0) {
            factorSet.push_back(i);
            factorSet.push_back(num / i);
        }
    }
}


//  The function that will simplify the fractions
void simplifyFun(int& a, int& b) {
    int Numer = a;
    int Denom = b;
    int small, temp;
    vector<int> factorSet;
    if (Numer == Denom) {
        a = 1;
        b = 1;
        return;
    }
    else if (Numer == -Denom) {
        a = -1;
        b = 1;
        return;
    }
    else if (Numer == 0) {
        b = 1;
        return;
    }


    if (abs(Numer) < abs(Denom)) {
        small = abs(Numer);
    }
    else {
        small = abs(Denom);
    }

    getFactors(small, factorSet);
    for (int i = 0; i < factorSet.size(); i++) {
        temp = factorSet[i];
        while (Numer % temp == 0 && Denom % temp == 0) {
            Numer /= temp;
            Denom /= temp;
        }
    }
    a = Numer;
    b = Denom;
}


int numerator;
int denominator;
void simplify();



//  Constructor

rationalNum::rationalNum() {
    setNumerator(0);
    setDenominator(1);
}

rationalNum::rationalNum(int _numerator, int _denominator)
{
    setNumerator(_numerator);
    setDenominator(_denominator);
    simplify();
}

//  Setters

void rationalNum::setNumerator(int _numerator)
{
    numerator = _numerator;
}

void rationalNum::setDenominator(int _denominator)
{
    if (_denominator == 0)
    {
        cout << "Invalid input, Denominator can't be 0" << endl;
    }
    else
    {
        denominator = _denominator;
    }
}


//  Getters
int rationalNum::getNumerator() const
{
    return numerator;
}

int rationalNum::getDenominator() const
{
    return denominator;
}

//  Simplifying method

void rationalNum::simplify()
{
    int N = numerator;
    int D = denominator;

    simplifyFun(N, D);
    setNumerator(N);
    setDenominator(D);
}


//  Input and Output operators
ostream& operator<<(ostream& out, const rationalNum& rn)
{
    out << rn.numerator;
    if (rn.numerator != 0 && rn.denominator != 1)
    {
        out << "/" << rn.denominator;
    }
    return out;
}

istream& operator>>(istream& in, rationalNum& rn)
{
    string rationalStr;
    int num = 0;
    int sign = 1;
    bool slash = false;
    bool validInput = true;

    cin >> rationalStr;

    for (int i = 0; i < rationalStr.size(); i++)
    {
        char temp = rationalStr[i];
        if (temp == '/')
        {
            if (slash == false && i != 0)
            {
                slash = true;
                rn.setNumerator(sign * num);
                num = 0;
                sign = 1;
            }
            else
            {
                validInput = false;
                break;
            }
        }
        else if (temp == '-')
        {
            if (i == 0)
            {
                sign = -sign;
            }
            else if (rationalStr[i - 1] == '/')
            {
                sign = -sign;
            }
            else
            {
                validInput = false;
                break;
            }
        }
        else if (temp <= '9' && temp >= '0')
        {
            if (num > INT_MAX / 10) {
                cout << "this number is too long to handle.";
                validInput = false;
                break;
            }
            num *= 10;
            num += rationalStr[i] - '0';
        }
        else {
            validInput = false;
            break;
        }


    }
    if (validInput == false)
    {
        rn.setNumerator(0);
        rn.setDenominator(1);
        cout << "Input is invalid!" << endl;
    }
    else
    {
        if (slash == true)
        {
            rn.setDenominator(sign * num);
        }
        else
        {
            rn.setNumerator(sign * num);
            rn.setDenominator(1);
        }
    }

    rn.simplify();

    return in;

}


//  Compound Arithmetic Operators

rationalNum& rationalNum::operator+=(const rationalNum& rn)
{
    *this = *this + rn;
    return *this;
}


rationalNum& rationalNum::operator=(const rationalNum& rn)
{
    setNumerator(rn.getNumerator());
    setDenominator(rn.getDenominator());

    return *this;
}


rationalNum& rationalNum::operator-=(const rationalNum& rn)
{
    *this = *this - rn;
    return *this;
}

rationalNum& rationalNum::operator*=(const rationalNum& rn)
{
    *this = *this * rn;
    return *this;
}

rationalNum& rationalNum::operator/=(const rationalNum& rn)
{
    *this = *this / rn;
    return *this;
}

rationalNum rationalNum::operator-() const
{
    rationalNum temp;
    temp.setNumerator(-getNumerator());
    temp.setDenominator(getDenominator());

    return temp;
}


//   Bool operators
bool operator==(const rationalNum& first, const rationalNum& second)
{
    int ls = first.getNumerator() * second.getDenominator();
    int rs = first.getDenominator() * second.getNumerator();

    return (ls == rs);
}

bool operator>=(const rationalNum& first, const rationalNum& second)
{
    int ls = first.getNumerator() * second.getDenominator();
    int rs = first.getDenominator() * second.getNumerator();

    return (ls > rs || first == second);
}

bool operator<=(const rationalNum& first, const rationalNum& second)
{
    int ls = first.getNumerator() * second.getDenominator();
    int rs = first.getDenominator() * second.getNumerator();

    return (ls < rs || first == second);
}


//  Operations on two fractions
rationalNum operator+(const rationalNum& first, const rationalNum& second)
{
    rationalNum temp;

    int fDenom = first.getDenominator();
    int sDenom = second.getDenominator();

    simplifyFun(fDenom, sDenom);

    temp.setDenominator(first.getDenominator() * sDenom);
    temp.setNumerator(first.getNumerator() * sDenom + second.getNumerator() * fDenom);

    temp.simplify();

    return temp;
}

rationalNum operator-(const rationalNum& first, const rationalNum& second)
{
    rationalNum temp = first + (-second);
    temp.simplify();
    return temp;
}

rationalNum operator*(const rationalNum& first, const rationalNum& second)
{
    rationalNum temp;

    int a = first.getNumerator();
    int b = second.getNumerator();
    int c = first.getDenominator();
    int d = second.getDenominator();

    temp.setNumerator(a * b);
    temp.setDenominator(c * d);

    temp.simplify();

    return temp;
}

rationalNum operator/(const rationalNum& first, const rationalNum& second)
{
    rationalNum temp(second.getDenominator(), second.getNumerator());

    rationalNum res = first * temp;
    res.simplify();

    return res;
}





int main() {

    rationalNum rn1, rn2;


    cout << "Enter two numbers, if fractions use /:  " << endl;
    cin >> rn1 >> rn2;

    // Using Arithmetic operators
    rationalNum rn3 = rn1 + rn2;

    rationalNum rn4 = rn1 - rn2;

    rationalNum rn5 = rn1 * rn2;

    rationalNum rn6 = rn1 / rn2;

    cout << "The result of addition is ";
    cout << rn3 << endl;

    cout << "The result of subtraction is ";
    cout << rn4 << endl;

    cout << "The result of multiplication is ";
    cout << rn5 << endl;

    cout << "The result of subtraction is ";
    cout << rn6 << endl;

    // Compound assignment operatrors

    rn1 += rn2;
    cout << "The result of addition is ";
    cout << rn1 << endl;

    rn1 -= rn2;
    cout << "The result of subtraction is ";
    cout << rn1 << endl;

    rn1 *= rn2;
    cout << "The result of multiplication is ";
    cout << rn1 << endl;

    rn1 /= rn2;
    cout << "The result of division is ";
    cout << rn1 << endl;

    // Bool operators

    bool bigger = rn1 >= rn2;
    cout << rn1 << " >= " << rn2 << " is: " << ((bigger) ? "True" : "False") << endl;

    //  Using setters and getters

    rationalNum rn7;
    int n, d;
    cout << "Enter a number that represents the numerator: " << endl;
    cin >> n;
    cout << "Enter a number that represents the denominator: " << endl;
    cin >> d;

    rn7.setNumerator(n);
    rn7.setDenominator(d);

    cout << rn7.getNumerator() << "/" << rn7.getDenominator() << endl;

    return 0;
}