#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <windows.h>
#include <chrono>

using namespace std;
using namespace chrono;
constexpr auto BASE = 10;

int getLength(long num) {
	int length = 0;
	while (num != 0) {
		length++;
		num /= 10;
	}
	return length;
}

long long Karat(long X, long Y) {
	if (X < 10 || Y < 10) {
		return X * Y;
	}
	long Xh, Xl, Yh, Yl, mult, z0, z1, z2;
	int xLen, yLen;
	double M;
	xLen = getLength(X);
	yLen = getLength(Y);
	M = fmin(xLen, yLen);
	M = (int)(ceil(M / 2));
	mult = pow(BASE, M);
	Xh = X / mult;
	Xl = X % mult;
	Yh = Y / mult;
	Yl = Y % mult;
	z0 = Karat(Xl, Yl);
	z2 = Karat(Xh, Yh);
	z1 = Karat((Xh + Xl), (Yh + Yl)) - z2 - z0;
	return z2 * pow(BASE, M * 2) + z1 * pow(BASE, M) + z0;
}

int main() {
	long X = 123456789;
	long Y = 123456789;
	auto start = high_resolution_clock::now();
	cout << X << " * " << Y << " = " << Karat(X, Y) << endl;
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(end - start);
	double time = duration.count();
	cout << "Execution Time: " << time / 1000000 << "ms" << endl;
	system("pause");
	return 0;
}