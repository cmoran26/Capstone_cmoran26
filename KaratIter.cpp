#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <windows.h>
#include <chrono>

using namespace std;
using namespace chrono;
constexpr auto BASE = 10;

struct stackFrame {
	long long X, Y, Xh, Xl, Yh, Yl, mult, M, z0, z1, z2, state, R;
};

int getLength(long long num) {
	int length = 0;
	while (num != 0) {
		length++;
		num /= 10;
	}
	return length;
}

long long Karat(long A, long B) {
	long long X, Y, Xh, Xl, Yh, Yl, mult, z0, z1, z2, R, state;
	int xLen, yLen;
	double M;
	vector<stackFrame> stack;
	stackFrame lastImage;
	//Initial conditions
	lastImage.X = A;
	lastImage.Y = B;
	//Initial conditions
	lastImage.state = 1; //giving state base case
	stack.push_back(lastImage);
	while (stack.size() > 0) {
		lastImage = stack.back();
		stack.pop_back();
		xLen = getLength(lastImage.X);
		yLen = getLength(lastImage.Y);
		M = fmin(xLen, yLen);
		M = (int)(ceil(M / 2));
		mult = pow(BASE, M);
		Xh = lastImage.X / mult;
		Xl = lastImage.X % mult;
		Yh = lastImage.Y / mult;
		Yl = lastImage.Y % mult;
		switch (lastImage.state) {
			case 1:
				if (lastImage.X < 10 || lastImage.Y < 10) {
					R = lastImage.X * lastImage.Y;
					break;
				}
				lastImage.state = 2;
				lastImage.M = M;
				stack.push_back(lastImage);
				lastImage.X = Xl;
				lastImage.Y = Yl;
				lastImage.state = 1;
				stack.push_back(lastImage);
				break;
			case 2:
				lastImage.z0 = R;
				lastImage.M = M;
				lastImage.state = 3;
				stack.push_back(lastImage);
				lastImage.X = Xh;
				lastImage.Y = Yh;
				lastImage.state = 1;
				stack.push_back(lastImage);
				break;
			case 3:
				lastImage.z2 = R;
				lastImage.M = M;
				lastImage.state = 4;
				stack.push_back(lastImage);
				lastImage.X = Xh + Xl;
				lastImage.Y = Yh + Yl;
				lastImage.state = 1;
				stack.push_back(lastImage);
				break;
			case 4:
				lastImage.z1 = R - lastImage.z2 - lastImage.z0;
				R = lastImage.z2*pow(BASE, lastImage.M * 2) + lastImage.z1*pow(BASE, lastImage.M) + lastImage.z0;
				break;
		}
	}
	return R;
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