#include <iostream>
#include "lab1_polynomial.hpp"
#include <random>
#include <fstream>

using namespace std;


// random number generation from https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
random_device rd;     // only used once to initialise (seed) engine
mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
uniform_int_distribution<int> uni(-1000, 1000); // guaranteed unbiased



Polynomial::Polynomial(int A[], int size) {
	// push back the provided integer array after resizing the vector to fit the integers
	data.resize(size);
	for (int i = 0; i < size; i++) {
		data.push_back(A[i]);
	}
}

Polynomial::Polynomial() {
	int polynomialDegree = rand() % 1001;
	for (int i = 0; i < polynomialDegree; i++) {
		data.push_back(uni(rng));
	}
}

Polynomial::Polynomial(string fileName) {
	string line;
	ifstream polyFile(fileName);
	if (polyFile.is_open()) {
		// first resize the vector taking in the polynomial size as the first line
		getline(polyFile, line);
		data.resize(stoi(line));
		while (getline(polyFile, line)) {
			data.push_back(stoi(line));
		}
	}
}

bool Polynomial::operator==(const Polynomial& target) {
	// compare the vectors to see if they are the same
	return data == target.data;
}

Polynomial Polynomial::operator+(const Polynomial& target) {
	bool targetHigherDegree = target.data.size() >= data.size();
	int emptyArray[10] = {};
	Polynomial newPolynomial(emptyArray, 1);
	for (int i = 0; i < (targetHigherDegree ? target.data.size() : data.size()); i++) {
		newPolynomial.data.push_back(targetHigherDegree ? target.data[i] : data[i]);
	}
	for (int i = 0; i < (targetHigherDegree ? data.size() : target.data.size()); i++) {
		newPolynomial.data[i] += (targetHigherDegree ? data[i] : target.data[i]);
	}

	return newPolynomial;
}
 

Polynomial Polynomial::operator-(const Polynomial& target) {
	// create a new polynomial object and copy over *this.data to the new polynomial data
	int emptyArray[10] = {};
	Polynomial newPolynomial(emptyArray, 1);
	bool targetHigherDegree = target.data.size() >= data.size();
	newPolynomial.data = data;

	// if the target polynomial is of higher degree resize the new polynomial data to that size
	if (targetHigherDegree) newPolynomial.data.resize(target.data.size(), 0);
	for (int i = 0; i < target.data.size(); i++) {
		newPolynomial.data[i] = newPolynomial.data[i] - target.data[i];
	}

	// TODO should remove 0s at end?

	return newPolynomial;
}

Polynomial Polynomial::derivative() {
	int emptyArray[10] = {};
	Polynomial newPolynomial(emptyArray, 1);
	newPolynomial.data.resize(data.size() - 1, 0);
	for (int i = 1; i < data.size(); i++) {
		newPolynomial.data[i - 1] = data[i] * i;
	}
	return newPolynomial;
}

int main() {

}