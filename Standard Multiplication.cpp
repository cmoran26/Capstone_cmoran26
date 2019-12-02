#include <iostream>
#include <stdio.h>
#include <chrono>

using namespace std;
using namespace chrono;

int main() {
	long long X = 123456789;
	long long Y = 123456789;
	auto start = high_resolution_clock::now();
	cout << X << " * " << Y << " = " << X * Y << endl;
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(end - start);
	double time = duration.count();
	cout << "Execution Time: " << time / 1000000 << "ms" << endl;
	system("pause");
	return 0;
}