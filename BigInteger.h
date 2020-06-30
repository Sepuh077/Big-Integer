#pragma once
#include <iostream>


class BigInteger
{
	char* a;
	int n;
	bool plus = true;
	friend std::istream& operator>>(std::istream& in, BigInteger& num);
	friend std::ostream& operator<<(std::ostream& out,const BigInteger& num);
	friend void delete_0(BigInteger& num);
	friend void push(BigInteger& num, int k);
public:
	BigInteger(int b = 0);
	BigInteger(int* b, bool plus, int n);
	BigInteger(const BigInteger& num);
	BigInteger& operator=(const BigInteger& num);
	bool operator==(const BigInteger& num) const;
	bool operator!=(const BigInteger& num) const;
	bool operator>(const BigInteger& num) const;
	bool operator>=(const BigInteger& num) const;
	bool operator<(const BigInteger& num) const;
	bool operator<=(const BigInteger& num) const;
	BigInteger& operator+=(const BigInteger& num);
	BigInteger& operator-=(const BigInteger& num);
	BigInteger operator+(const BigInteger& num) const;
	BigInteger operator-(const BigInteger& num) const;
	BigInteger& operator*=(const BigInteger& num);
	BigInteger operator*(const BigInteger& num) const;
	BigInteger& operator/=(const BigInteger& num);
	BigInteger operator/(const BigInteger& num) const;
	BigInteger& operator%=(const BigInteger& num);
	BigInteger operator%(const BigInteger& num) const;
	BigInteger& operator^(const int k);
	operator int() {
		int x = 0;
		for (int i = n - 1; i >= 0; i--) {
			x *= 10;
			x += (a[i] - '0');
		}
		return x;
	}
	BigInteger& operator++() {
		BigInteger b(1);
		return (*this += b);
	}
	BigInteger operator++(int) {
		BigInteger b(1), c(*this);
		*this += b;
		return c;
	}
	BigInteger& operator--() {
		BigInteger b(1);
		return (*this -= b);
	}
	BigInteger operator--(int) {
		BigInteger b(1), c(*this);
		*this -= b;
		return c;
	}
	~BigInteger() {
		delete[] a;
	}
};