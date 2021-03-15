#include <iostream>
#include <NTL/ZZ.h>
#include <stdlib.h> 
#include <time.h>
#include <assert.h>
#include <algorithm>
#include <iomanip>
#include <cassert>

using namespace std;
using namespace NTL;
ZZ mulmod(ZZ a, ZZ b, ZZ m) {
	ZZ x, y;
	x = 0;
	y = a % m;
	while (b > 0) {
		if (b % 2 == 1) {
			x = (x + y) % m;
		}
		y = (y * 2) % m;
		b /= 2;
	}
	return x % m;
}
ZZ modulo(ZZ base, ZZ e, ZZ m) {
	ZZ x;
	x = 1;
	ZZ y = base;
	while (e > 0) {
		if (e % 2 == 1)
			x = (x * y) % m;
		y = (y * y) % m;
		e = e / 2;
	}
	return x % m;
}
bool Miller(ZZ p, int iteration) {
	if (p < 2) {
		return false;
	}
	if (p != 2 && p % 2 == 0) {
		return false;
	}
	ZZ s = p - 1;
	while (s % 2 == 0) {
		s /= 2;
	}
	for (int i = 0; i < iteration; i++) {
		ZZ a = RandomBnd(p - 1) + 1, temp = s;
		ZZ mod = modulo(a, temp, p);
		while (temp != p - 1 && mod != 1 && mod != p - 1) {
			mod = mulmod(mod, mod, p);
			temp *= 2;
		}
		if (mod != p - 1 && temp % 2 == 0) {
			return false;
		}
	}
	return true;
}
int isPrime(ZZ n) {
	ZZ i;
	int isPrime = 1;

	if (n == 0 || n == 1) {
		isPrime = 0;
	}
	else {
		for (i = 2; i <= n / 2; i++) {
			if (n % i == 0) {
				isPrime = 0;
				break;
			}
		}
	}
	return isPrime;
}
ZZ nextPrime(ZZ max) {
	ZZ p;
	do {
		p = RandomBnd(max + 1);
	} while (Miller(p, 2) == 0);
	return p;
}
int jacobiSymbol(ZZ n, ZZ k) {
	int t = 1;

	assert(k > n > 0 && k % 2 == 1);
	n %= k;
	while (n != 0) {
		while (n % 2 == 0) {
			n /= 2;
			int r = k % 8;
			if (r == 3 || r == 5)
				t = -t;
		}
		swap(n, k);
		if (n % 4 == 3 && k % 4 == 3)
			t = -t;
		n %= k;
	}

	if (k == 1)
		return t;
	else
		return 0;
}
int main() {
	ZZ jacobi, seed, x0, x1, i, j, p, q, x, n, max, min, test;
	ZZ bit;
	ZZ test1, test2;
	int n0 = 0, n1 = 0;
	max = 1, min = 1, bit = 0;
	test1 = 1236; test2 = 20003;

	for (int i = 0; i < 512; i++)
		max = max * 2;

	do {
		p = nextPrime(max);
		q = nextPrime(max);
	} while (p == q);

	cout << "Our P is:" << endl;
	cout << p << "\n";
	cout << "Our Q is:" << endl;
	cout << q << "\n";
	cout << "Our N is:" << endl;
	n = p * q;
	cout << n << endl;

	seed = RandomBnd(n);
	cout << "SEED:" << endl;
	cout << seed << endl;

	cout << "Please input the i: ";
	cin >> i;

	for (j = 0; j < i; j++) {
		jacobi = jacobiSymbol(seed + j + 1, n);
		bit = (jacobi + 1) / 2;

		if (bit == 1)
			n1++;
		else
			n0++;

		cout << bit;
	}
	cout << endl;
	cout << "Number of 0's: " << n0 << endl;
	cout << "Number of 1's: " << n1 << endl;

	cout << Miller(p, 2) << endl;
	cout << Miller(q, 2) << endl;
	cout << jacobiSymbol(test1, test2);

	return 0;
}