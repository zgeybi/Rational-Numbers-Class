#pragma once

#include <iostream>
using namespace std;

class rationalNum {

	friend rationalNum operator+(const rationalNum& first, const rationalNum& second);
	friend rationalNum operator-(const rationalNum& first, const rationalNum& second);
	friend rationalNum operator*(const rationalNum& first, const rationalNum& second);
	friend rationalNum operator/(const rationalNum& first, const rationalNum& second);

	friend bool operator==(const rationalNum& first, const rationalNum& second);
	friend bool operator>=(const rationalNum& first, const rationalNum& second);
	friend bool operator<=(const rationalNum& first, const rationalNum& second);

	friend ostream& operator<<(ostream& out, const rationalNum& rn);
	friend istream& operator>>(istream& in, rationalNum& rn);

public:

	rationalNum();
	rationalNum(int _numerator, int _denominator);

	rationalNum& operator=(const rationalNum& rn);
	rationalNum& operator+=(const rationalNum& rn);
	rationalNum& operator-=(const rationalNum& rn);
	rationalNum& operator*=(const rationalNum& rn);
	rationalNum& operator/=(const rationalNum& rn);

	rationalNum operator-() const;


	void setNumerator(int _numerator);
	int getNumerator() const;
	void setDenominator(int _denominator);
	int getDenominator() const;

private:
	int numerator;
	int denominator;
	void simplify();
};



