#include <iostream>
#include "lab1_polynomial.hpp"
#include <random>
#include <fstream>
#define ASSERT(condition) if(!(condition)) return false

using namespace std;


// random number generation from https://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
random_device rd;     // only used once to initialise (seed) engine
mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
uniform_int_distribution<int> uni(-1000, 1000); // guaranteed unbiased
uniform_int_distribution<int> uni2(0, 1000); // guaranteed unbiased



Polynomial::Polynomial(int A[], int size) {
	// push back the provided integer array after resizing the vector to fit the integers
	data.resize(size);
	for (int i = 0; i < size; i++) {
		data[i] = A[i];
	}
}

Polynomial::Polynomial() {
	//uni2 is a random number generator [0, 1000]
	int polynomialDegree = uni2(rng);
	//uni is a random number generator [-1000, 1000]
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
		int size = stoi(line);
		data.resize(size);
		for (int i = 0; i < size; i++) {
			getline(polyFile, line);
			if (!line.empty()) {
				data[i] = stoi(line);
			}
		}
	}
	remove_trailing_zeros(*this);
}

bool Polynomial::operator==(const Polynomial& target) {
	// compare the vectors to see if they are the same
	return data == target.data;
}

void Polynomial::print() {
	bool first = true;
	for (int i = data.size() - 1; i > -1; i--) {
		if (data[i] != 0 && !first) {
			cout << "+ ";
		}
		if (data[i] != 0) {
			cout << data[i] << "x^" << i << " ";
			first = false;
		}
	}
	cout << endl;
}

Polynomial Polynomial::operator+(const Polynomial& target) {
	bool targetHigherDegree = target.data.size() >= data.size();
	int* emptyArray = NULL;
	Polynomial newPolynomial(emptyArray, 0);
	for (int i = 0; i < (targetHigherDegree ? target.data.size() : data.size()); i++) {
		newPolynomial.data.push_back(targetHigherDegree ? target.data[i] : data[i]);
	}
	for (int i = 0; i < (targetHigherDegree ? data.size() : target.data.size()); i++) {
		newPolynomial.data[i] += (targetHigherDegree ? data[i] : target.data[i]);
	}
	remove_trailing_zeros(newPolynomial);
	return newPolynomial;
}
 

Polynomial Polynomial::operator-(const Polynomial& target) {
	// create a new polynomial object and copy over *this.data to the new polynomial data
	int* emptyArray = NULL;
	Polynomial newPolynomial(emptyArray, 0);
	bool targetHigherDegree = target.data.size() >= data.size();
	newPolynomial.data = data;

	// if the target polynomial is of higher degree resize the new polynomial data to that size
	if (targetHigherDegree) newPolynomial.data.resize(target.data.size(), 0);
	for (int i = 0; i < target.data.size(); i++) {
		newPolynomial.data[i] = newPolynomial.data[i] - target.data[i];
	}
	remove_trailing_zeros(newPolynomial);
	return newPolynomial;
}


void Polynomial::remove_trailing_zeros(Polynomial& target) {
	int i = target.data.size() - 1;
	bool trailing_zero = true;
	while (i > -1 && trailing_zero) {
		if (target.data[i] == 0) {
			target.data.pop_back();
			i--;
		}
		else trailing_zero = false;
	}
}

Polynomial Polynomial::operator*(const Polynomial& target) {
	vector<int> emptyArray(data.size() + target.data.size() - 1);
	Polynomial newPolynomial(&emptyArray[0], data.size() + target.data.size() - 1);
	for (int i = 0; i < data.size(); i++) {
		for (int l = 0; l < target.data.size(); l++) {
			newPolynomial.data[i + l] += (data[i] * target.data[l]);
		}
	}
	remove_trailing_zeros(newPolynomial);
	return newPolynomial;
}

Polynomial Polynomial::derivative() {
	int* emptyArray = NULL;
	Polynomial newPolynomial(emptyArray, 0);
	if (data.size() == 0) {
		return newPolynomial;
	}
	newPolynomial.data.resize(data.size() - 1, 0);
	for (int i = 1; i < data.size(); i++) {
		newPolynomial.data[i - 1] = data[i] * i;
	}
	return newPolynomial;
}




// Test Cases
bool PolynomialTest::testConstructors() {
	vector<int> newPolynomial{ 1, 2, 3, 4 };
	//Demonstrates polynomial takes two input parameters
	Polynomial p(&newPolynomial[0], newPolynomial.size());
	ASSERT(p.data.size() == newPolynomial.size());
	ASSERT(p.data == newPolynomial);

	//Demonstrates no parameters generates a random polynomial
	Polynomial randomPolynomial = Polynomial();
	ASSERT(randomPolynomial.data.size() >= 0 && randomPolynomial.data.size() <= 1000);
	for (int i : randomPolynomial.data) {
		ASSERT(i <= 1000 && i >= -1000);
	}
	//Demonstrates a consecutive call generates a different random polynomial
	
	Polynomial otherRandomPolynomial = Polynomial();
	ASSERT(randomPolynomial.data != otherRandomPolynomial.data);

	//Creates file "testvec.txt" to test filename parameter
	ofstream testFile;
	testFile.open("testvec.txt");
	testFile << "3\n1\n2\n3";
	testFile.close();
	vector<int> filevec{ 1, 2, 3 };
	Polynomial pFile(&filevec[0], filevec.size());
	Polynomial getPFile("testvec.txt");
	//Demonstrates that inputting a filename creates the expected polynomial
	ASSERT(pFile.data == getPFile.data);

	//Creates file "testvec2.txt" to test filename parameter
	ofstream testFile2;
	testFile2.open("testvec2.txt");
	testFile2 << "4\n1\n2\n\n4\n";
	testFile2.close();
	vector<int> filevec2{ 1, 2, 0, 4 };
	Polynomial pFile2(&filevec2[0], filevec2.size());
	Polynomial getPFile2("testvec2.txt");
	//Demonstrates that inputting a filename creates the expected polynomial
	ASSERT(pFile2.data == getPFile2.data);


	return true;
}
bool PolynomialTest::testPrint() {
	//Test normal case
	cout << "### output of testPrint() function, please visually inspect ###" << endl;
	vector<int> nums1{ 1, 2, 3, 4, 5 };
	Polynomial p1(&nums1[0], nums1.size());

	cout << "The following line should read '5x^4 + 4x^3 + 3x^2 + 2x^1 + 1x^0'" << endl;
	p1.print();

	//Test that negatives work
	vector<int> nums2{ -1, 2, -3, 4, -5 };
	Polynomial p2(&nums2[0], nums2.size());

	cout << "The following line should read '-5x^4 + 4x^3 + -3x^2 + 2x^1 + -1x^0'" << endl;
	p2.print();

	//Test that an empty polynomial works
	Polynomial p3(nullptr, 0);

	cout << "The following line should be blank" << endl;
	p3.print();

	//Test that it ignores the 0 coefficient
	vector<int> nums4{ 1, 2, 3, 4, 0 };
	Polynomial p4(&nums4[0], nums4.size());

	cout << "The following line should read '4x^3 + 3x^2 + 2x^1 + 1x^0'" << endl;
	p4.print();

	cout << "### end of output for testPrint()\n\n" << endl;
	return true;
}

bool PolynomialTest::testComparison() {
	//Test a normal case
	vector<int> nums{ 1, 2, 3, 4, 5 };
	Polynomial p1(&nums[0], nums.size());
	Polynomial p2(&nums[0], nums.size());
	ASSERT(p1 == p2);

	//Test a negative comparison
	vector<int> nums2{ 1, 2, 3, 4, 5, 6, 7 };
	Polynomial p3(&nums2[0], nums2.size());
	ASSERT(!(p1 == p3));

	//Test an empty comparison
	Polynomial p4(nullptr, 0);
	Polynomial p5(nullptr, 0);
	ASSERT(p4 == p5);

	//Test an empty and non empty comparison
	ASSERT(!(p4 == p3));

	return true;
}

bool PolynomialTest::testAddition() {
	//Test a normal case
	vector<int> nums1{ 1, 1, 1, 1, 1 };
	vector<int> nums2{ 2, 2, 2, 2, 2 };
	vector<int> nums3{ 3, 3, 3, 3, 3 };
	Polynomial p1(&nums1[0], nums1.size());
	Polynomial p2(&nums2[0], nums2.size());
	Polynomial p3(&nums3[0], nums3.size());
	ASSERT(p1 + p2 == p3);

	//test a negative case
	vector<int> nums4{ 2, 3, 4, 5, 6 };
	vector<int> nums5{ -1, -1, -1, -1, -1 };
	vector<int> nums6{ 1, 2, 3, 4, 5 };
	Polynomial p4(&nums4[0], nums4.size());
	Polynomial p5(&nums5[0], nums5.size());
	Polynomial p6(&nums6[0], nums6.size());
	ASSERT(p4 + p5 == p6);

	//Test an empty case
	Polynomial p7(nullptr, 0);
	ASSERT(p1 + p7 == p1);

	//Test a case with a zero and consecutive additions
	vector<int> nums8{ -2, -1, -0, 1, 2 };
	Polynomial p8(&nums8[0], nums8.size());
	ASSERT(p7 + p8 + p3 == p6);	

	return true;
}

bool PolynomialTest::testSubtraction() {
	//Test a normal case
	vector<int> nums1{ 1, 1, 1, 1, 1 };
	vector<int> nums2{ 2, 2, 2, 2, 2 };
	vector<int> nums3{ 3, 3, 3, 3, 3 };
	Polynomial p1(&nums1[0], nums1.size());
	Polynomial p2(&nums2[0], nums2.size());
	Polynomial p3(&nums3[0], nums3.size());
	ASSERT(p3 - p2 == p1);

	//Test a negative case
	vector<int> nums4{ -1, -1, -1, -1, -1 };
	Polynomial p4(&nums4[0], nums4.size());
	ASSERT(p1 - p2 == p4);

	//Test consecutive subtractions
	ASSERT(p3 - p1 - p1 - p2 == p4);

	//Test empty subtraction
	Polynomial p5(nullptr, 0);
	ASSERT(p3 - p5 == p3);

	return true;
}

bool PolynomialTest::testMultiplication() {
	//Test a normal case
	vector<int> nums1{ 2, 1 }; //x + 2
	vector<int> nums2{ 3, 1 }; //x + 3
	//(x + 2)(x + 3) = x^2 + 5x + 6
	vector<int> ans{ 6, 5, 1 };
	Polynomial p1(&nums1[0], nums1.size());
	Polynomial p2(&nums2[0], nums2.size());
	Polynomial pAns(&ans[0], ans.size());
	ASSERT(p1 * p2 == pAns);
	ASSERT(p1 * Polynomial(NULL, 0) == Polynomial(NULL, 0));

	//Test an empty case
	Polynomial p3(nullptr, 0);
	ASSERT(p1 * p3 == p3);

	//Test a case with negatives
	vector<int> nums4{ -1 }; //-1
	Polynomial p4(&nums4[0], nums4.size());
	vector<int> p1p4ans{ -2, -1 };
	Polynomial polynomialp1p4ans(&p1p4ans[0], p1p4ans.size());
	ASSERT(p4 * p1 == polynomialp1p4ans);

	return true;
}

bool PolynomialTest::testDerivation() {
	//Test a normal case
	vector<int> nums1{ 1, 2, 3 }; // 3x^2 + 2x + 1
	// d/dx(3x^2 + 2x + 1) = 6x + 2
	vector<int> ans1{ 2, 6 };
	Polynomial p1(&nums1[0], nums1.size());
	Polynomial p1Ans(&ans1[0], ans1.size());
	ASSERT(p1.derivative() == p1Ans);

	//Test an empty case
	ASSERT(Polynomial(nullptr, 0).derivative() == Polynomial(nullptr, 0));

	//Test a negative case
	vector<int> nums2{ -4, -5, -6};
	vector<int> ans2{ -5, -12};
	Polynomial p2(&nums2[0], nums2.size());
	Polynomial p2ans(&ans2[0], ans2.size());
	ASSERT(p2.derivative() == p2ans);

	//Test a consecutive derivatives case
	ASSERT(p1Ans.derivative().derivative() == Polynomial(NULL, 0));
	return true;
}

void PolynomialTest::runTests() {
	int failCount = 0;
	if (!testConstructors()) {
		cout << "testConstructors failed" << endl;
		failCount++;
	}
	if (!testPrint()) {
		cout << "testPrint failed" << endl;
		failCount++;
	}
	if (!testComparison()) {
		cout << "testComparison failed" << endl;
		failCount++;
	}
	if (!testAddition()) {
		cout << "testAddition failed" << endl;
		failCount++;
	}
	if (!testSubtraction()) {
		cout << "testSubtraction failed" << endl;
		failCount++;
	}
	if (!testMultiplication()) {
		cout << "testMultiplication failed" << endl;
		failCount++;
	}
	if (!testDerivation()) {
		cout << "testDerivation failed" << endl;
		failCount++;
	}
	if (failCount > 0) {
		cout << "Finished running tests. Failures: " << failCount << endl;
	}
	else {
		cout << "Finished running test. All tests passed." << endl;
	}
}

int main(int argc, char* argsv[]) {
	PolynomialTest tester;
	tester.runTests();
	getchar(); // Pause before exiting to view results
}
