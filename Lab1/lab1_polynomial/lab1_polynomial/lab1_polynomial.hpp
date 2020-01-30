#pragma once
#ifndef POLYNOMIAL_H

#include <vector>
#include <string>
using namespace std;

class Polynomial {
public:
	vector<int> data;
	void remove_trailing_zeros(Polynomial& target);
	Polynomial(int A[], int size);
	Polynomial();
	Polynomial(string fileName);
	bool operator==(const Polynomial& target);
	void print();
	Polynomial operator+(const Polynomial& target);
	Polynomial operator-(const Polynomial& target);
	Polynomial operator*(const Polynomial& target);
	Polynomial derivative();
	class PolynomialTest friend;
};


class PolynomialTest {
public:
	bool testConstructors();
	bool testComparison();
	bool testAddition();
	bool testSubtraction();
	bool testMultiplication();
	bool testDerivation();

	void runTests();
};

#endif // !POLYNOMIAL_H
