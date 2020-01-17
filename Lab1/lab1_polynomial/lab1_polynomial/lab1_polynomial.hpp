#pragma once
#ifndef POLYNOMIAL_H

#include <vector>
#include <string>
using namespace std;

class Polynomial {
	vector<int> data;
	Polynomial(int A[], int size);
	Polynomial();
	Polynomial(string fileName);
	bool operator==(const Polynomial& target);
	void print();
	Polynomial operator+(const Polynomial& target);
	Polynomial operator-(const Polynomial& target);
	Polynomial operator*(const Polynomial& target);
	Polynomial derivative();
};

#endif // !POLYNOMIAL_H
