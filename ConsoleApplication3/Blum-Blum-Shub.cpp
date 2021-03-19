#include <iostream>
#include <NTL/ZZ.h>
#include <stdlib.h> 
#include <time.h>
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
void BBS(int z) {
	ZZ n1, n2, s, x0, x1, i, p, q, x, n, max, min;
	max = 1;

	for (int i = 0; i < 512; i++)
		max = max * 2;

    do {
		do{
		do {
			p = RandomBnd(max + 1);
		} while (p % 4 != 3);
	    } while (Miller(p, 10) == 0);

	do {
		do {
			q = RandomBnd(max + 1);
		} while (q % 4 != 3);
	} while (Miller(q, 10) == 0);

	} while (p == q);

	cout << "Our P is:" << endl;
	cout << p << "\n";
	cout << "Our Q is:" << endl;
	cout << q << "\n";

	n = p * q;
	cout << "Our N is:" << endl;
	cout << n << "\n";

	srand(time(NULL));
	s = RandomBnd(n);
	x0 = (s * s) % n;

	for (int j = 0; j < z; j++)
	{
		x1 = (x0 * x0) % n;
		x0 = x1;

		if (IsOdd(x1))
		{
			cout << "1 ";
			n1++;
		}
		else
		{
			cout << "0 ";
			n2++;
		}
	}

	cout << endl;
	cout << "Number of 1's: " << n1;
	cout << endl;
	cout << "Number of 0's: " << n2 << endl;

	cout << Miller(p, 10) << endl;
	cout << Miller(q, 10) << endl;
}
int main()
{
	int i;
	cout << "Please input the i: ";
	cin >> i;
	BBS(i);

	return 0;
}