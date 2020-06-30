#include "BigInteger.h"
#include <iostream>

std::istream& operator>>(std::istream& in, BigInteger& num) {
	in >> num.n;
	char* b = new char[num.n + 1];
	num.a = new char[num.n];
	in >> b;
	if (b[0] == '-' || b[0] == '+') {
		if (b[0] == '-') {
			num.plus = 0;
		}
		if (b[0] == '+') {
			num.plus = 1;
		}
		for (int i = 1; i <= num.n; i++) {
			num.a[i - 1] = b[num.n + 1 - i];
		}
	}
	else {
		for (int i = 0; i < num.n; i++)
			num.a[i] = b[num.n - i - 1];
	}
	delete_0(num);
	return in;
}
std::ostream& operator<<(std::ostream& out, const BigInteger& num) {
	if (num.plus == 0)
		out << "-";
	for (int i = num.n - 1; i >= 0; i--)
		out << num.a[i];
	out << " ";
	return out;
}
BigInteger::BigInteger(int b) {
	if (b != 0) {
		if (b < 0)
			plus = 0;
		else
			plus = 1;
		int i = 0;
		int x = b;
		while (b) {
			i++;
			b /= 10;
		}
		n = i;
		a = new char[n];
		i = 0;
		while (x) {
			a[i] = x % 10 + '0';
			x /= 10;
			++i;
		}
	}
	else {
		n = 1;
		a = new char[1];
		a[0] = '0';
	}
	delete_0(*this);
}

BigInteger::BigInteger(int* b, bool plus, int n) {
	this->n = n;
	a = new char[n];
	this->plus = plus;
	for (int i = 0; i < n; i++) {
		a[i] = b[i] + '0';
	}
	delete_0(*this);
}
BigInteger::BigInteger(const BigInteger& num) {
	n = num.n;
	plus = num.plus;
	a = new char[n];
	for (int i = 0; i < n; i++)
		a[i] = num.a[i];
	delete_0(*this);
}
BigInteger& BigInteger::operator=(const BigInteger& num) {
	if (*this == num)
		return *this;
	delete[] a;
	n = num.n;
	plus = num.plus;
	a = new char[n];
	for (int i = 0; i < n; i++)
		a[i] = num.a[i];
	return *this;
}
bool BigInteger::operator==(const BigInteger& num) const {
	if (n != num.n || plus!=num.plus)
		return 0;
	for (int i = 0; i < n; i++)
		if (a[i] != num.a[i])
			return 0;
	return 1;
}
bool BigInteger::operator!=(const BigInteger& num) const {
	if ((*this) == num)
		return 0;
	return 1;
}
bool BigInteger::operator > (const BigInteger& num) const {
	if (n > num.n || plus > num.plus) {
		return 1;
	}
	if (n < num.n || plus < num.plus) {
		return 0;
	}
	for (int i = n - 1; i >= 0; i--) {
		if (a[i] > num.a[i])
			return 1;
		if (a[i] < num.a[i])
			return 0;
	}
	return 0;
}
bool BigInteger::operator>=(const BigInteger& num) const {
	if (*this == num || *this > num)
		return 1;
	return 0;
}
bool BigInteger::operator<(const BigInteger& num) const {
	if (*this >= num)
		return 0;
	return 1;
}
bool BigInteger::operator<=(const BigInteger& num) const {
	if (*this > num)
		return 0;
	return 1;
}
BigInteger& BigInteger::operator+=(const BigInteger& num) {
	if (plus != num.plus) {
		BigInteger b(num);
		b.plus = plus;
		(*this) -= b;
		return *this;
	}
	if (n < num.n) {
		char* b = new char[n];
		for (int i = 0; i < n; i++)
			b[i] = a[i];
		delete[] a;
		a = new char[num.n];
		for (int i = 0; i < num.n; i++) {
			if (i < n)
				a[i] = b[i];
			else
				a[i] = '0';
		}
		delete[] b;
		n = num.n;
	}
	int x = 0;
	for (int i = 0; i < n; i++) {
		int k;
		if (i < num.n)
			k = a[i] + num.a[i] - 2 * '0' + x;
		else
			k = a[i] - '0' + x;
		a[i] = k % 10 + '0';
		x = k / 10;
	}
	if (x > 0) {
		char* b = new char[n];
		for (int i = 0; i < n; i++)
			b[i] = a[i];
		delete[] a;
		a = new char[n + 1];
		for (int i = 0; i < n; i++)
			a[i] = b[i];
		delete[] b;
		a[n] = x + '0';
		n++;
	}
	return *this;

}
BigInteger& BigInteger::operator-=(const BigInteger& num) {
	if (plus != num.plus) {
		BigInteger b(num);
		b.plus = plus;
		*this += b;
		return *this;
	}
	if (num > * this) {
		plus = !plus;
		if (num.n != n) {
			char* b = new char[n];
			for (int i = 0; i < n; i++) {
				b[i] = a[i];
			}
			delete[] a;
			a = new char[num.n];
			for (int i = 0; i < num.n; i++) {
				if (i < n)
					a[i] = b[i];
				else
					a[i] = '0';
			}
			delete[] b;
			n = num.n;
		}
		int x = 0;
		for (int i = 0; i < num.n; i++) {
			int k = num.a[i] - a[i] - x;
			if (k < 0)
			{
				x = 1;
				k += 10;
			}
			else
				x = 0;
			a[i] = k + '0';
		}
	}
	else {
		int x = 0;
		for (int i = 0; i < n; i++) {
			int k;
			if (i < num.n) {
				k = a[i] - num.a[i] - x;
			}
			else {
				k = a[i] - x - '0';
			}
			if (k < 0) {
				k += 10;
				x = 1;
			}
			else
				x = 0;
			a[i] = k + '0';
		}
	}
	delete_0(*this);
	return *this;
}
BigInteger BigInteger::operator+(const BigInteger& num) const {
	BigInteger b(*this);
	return (b += num);
}
BigInteger BigInteger::operator-(const BigInteger& num) const {
	BigInteger b(*this);
	return (b -= num);
}
BigInteger& BigInteger::operator*=(const BigInteger& num) {
	if (plus != num.plus)
		plus = 0;
	else
		plus = 1;
	BigInteger b(0);
	for (int i = 0; i < num.n; i++) {
		BigInteger c(*this);
		push(c, i);
		for (int j = 0; j < num.a[i] - '0'; j++) {
			c.plus = b.plus;
			b += c;
		}
	}
	*this = b;
	return *this;
}
BigInteger BigInteger::operator*(const BigInteger& num) const {
	BigInteger b(*this);
	return (b *= num);
}
BigInteger& BigInteger::operator/=(const BigInteger& num) {
	if (plus != num.plus)
		plus = 0;
	else
		plus = 1;
	BigInteger b(*this), c(num);
	b.plus = 1;
	c.plus = 1;
	if (b < c) {
		n = 1;
		delete[] a;
		a = new char[1];
		a[0] = '0';
	}
	else {
		BigInteger ans(0);
		while (b >= c) {
			int z = b.a[b.n - 1] - '0';
			BigInteger d(z);
			int x = b.n - 2;
			while (d < c) {
				push(d, 1);
				int v = b.a[x] - '0';
				BigInteger h(v);
				d += h;
				x--;
			}
			for (int i = 1; i < 10; i++) {
				BigInteger ind(i);
				ind *= c;
				if (ind > d) {
					push(ans, 1);
					BigInteger gum(i - 1);
					ans += gum;
					gum *= c;
					b -= gum;
					break;
				}
			}
		}
		*this = ans;
	}
	delete_0(*this);
	return *this;
}
BigInteger BigInteger::operator/(const BigInteger& num) const {
	BigInteger b(*this);
	return (b /= num);
}
BigInteger& BigInteger::operator%=(const BigInteger& num) {
	BigInteger b;
	b = (*this / num);
	b *= num;
	return (*this -= b);
}
BigInteger BigInteger::operator%(const BigInteger& num) const {
	BigInteger b(*this);
	return (b %= num);
}
BigInteger& BigInteger::operator^(const int k) {
	BigInteger b(1);
	for (int i = 0; i < k; i++) {
		b *= (*this);
	}
	*this = b;
	return *this;
}
void delete_0(BigInteger& num) {
	int i = num.n - 1;
	while (num.a[i] == '0' && i > 0) {
		i--;
	}
	if (i != num.n - 1) {
		char* b = new char[i + 1];
		for (int j = 0; j <= i; j++)
			b[j] = num.a[j];
		delete[] num.a;
		num.a = new char[i + 1];
		num.n = i + 1;
		for (int j = 0; j <= i; j++) {
			num.a[j] = b[j];
		}
		delete[] b;
		if (num.n == 1 && num.a[0] == '0')
			num.plus = 1;
	}
}
void push(BigInteger& num, int k) {
	char* b = new char[num.n];
	for (int i = 0; i < num.n; i++) {
		b[i] = num.a[i];
	}
	delete[] num.a;
	num.a = new char[k + num.n];
	for (int i = k; i < num.n + k; i++) {
		num.a[i] = b[i - k];
	}
	for (int i = 0; i < k; i++)
		num.a[i] = '0';
	num.n += k;
}