#include "Matrix.h"
#include <iostream>
#include <fstream>

using namespace std;

void display(const Matrix &m1, const Matrix &m2, const Matrix &m3);
void test();
void testAddition(const Matrix &m1, const Matrix &m2, const Matrix &m3);
void testSubtraction(const Matrix &m1, const Matrix &m2, const Matrix &m3);
void testMultiplication(const Matrix &m1, const Matrix &m2, const Matrix &m3);
void testBooleanExpressions(const Matrix &m1, const Matrix &m2, const Matrix &m3);
void testSingleElementAccess(const Matrix &m1, const Matrix &m2, const Matrix &m3);
void testExceptions();

int main(int argc, char const *argv[])
{

	test();

	return 0;
}

void display(const Matrix &m1, const Matrix &m2, const Matrix &m3)
{
	cout << "m1: " << endl
		 << m1 << endl;
	cout << "m2: " << endl
		 << m2 << endl;
	cout << "m3: " << endl
		 << m3 << endl;
}

void test()
{
	cout << "creating matrices" << endl;
	Matrix m1(3, 4);
	Matrix m2(5, 6);
	Matrix m3(6, 4);
	Matrix m4(3, 4);
	Matrix m5(2, 2);
	Matrix m6(2, 2);

	ifstream filem1("m1.txt");
	filem1 >> m1;
	ifstream filem2("m2.txt");
	filem2 >> m2;
	ifstream filem3("m3.txt");
	filem3 >> m3;
	ifstream filem4("m4.txt");
	filem4 >> m4;
	ifstream filem5("m5.txt");
	filem5 >> m5;
	m6(0, 0) = 2;
	m6(0, 1) = 6;
	m6(1, 0) = 1;
	m6(1, 1) = 9;
	display(m1, m2, m3);
	display(m4, m5, m6);
	testAddition(m1, m4, m6);
	testSubtraction(m1, m4, m6);
	testMultiplication(m2, m3, m5);
	testBooleanExpressions(m1, m4, m3);
	testSingleElementAccess(m1, m4, m6);
	filem1.close();
	filem2.close();
	filem3.close();
	filem4.close();
	filem5.close();
	testExceptions();
}

void testAddition(const Matrix &m1, const Matrix &m2, const Matrix &m3)
{
	cout << "Testing addition" << endl;
	display(m1, m2, m3);
	Matrix res = m1 + m2;
	cout << "Sum of matrices m1 and m2: " << endl
		 << res << endl;
	Matrix m4(m3);
	cout << "m4: " << endl
		 << m4 << endl;
	m4 += m3;
	cout << "Matrix m4 after adding m3: " << endl
		 << m4 << endl;
}

void testSubtraction(const Matrix &m1, const Matrix &m2, const Matrix &m3)
{
	cout << "Testing subtraction" << endl;
	display(m1, m2, m3);
	Matrix res = m1 - m2;
	cout << "Difference of matrices m1 and m2: " << endl
		 << res << endl;
	cout << "Difference of matrices m1 and m1: " << endl
		 << m1 - m1 << endl;
	Matrix m4(m3);
	cout << "m4: " << endl
		 << m4 << endl;
	m4 -= m3;
	cout << "Matrix m4 after subtracting m3: " << endl
		 << m4 << endl;
}

void testMultiplication(const Matrix &m1, const Matrix &m2, const Matrix &m3)
{
	cout << "Testing multiplication" << endl;
	display(m1, m2, m3);
	Matrix res = m1 * m2;
	cout << "Product of matrices m1 and m2: " << endl
		 << res << endl;
	cout << "Product of matrices m3 and m3: " << endl
		 << m3 * m3 << endl;
	Matrix m4(m3);
	cout << "m4: " << endl
		 << m4 << endl;
	m4 *= m3;
	cout << "Matrix m4 after multiplaying by m3: " << endl
		 << m4 << endl;
}

void testBooleanExpressions(const Matrix &m1, const Matrix &m2, const Matrix &m3)
{
	cout << "Testing Boolean Expressions" << endl;
	display(m1, m2, m3);
	cout << boolalpha << "m1 == m2: " << (m1 == m2) << endl;
	cout << "m1 != m2: " << (m1 != m2) << endl;
	cout << "m2 == m3: " << (m2 == m3) << endl;
	cout << "m2 != m3: " << (m2 != m3) << endl;
	Matrix m4 = m2;
	cout << "Matrix m4: " << endl
		 << m4 << endl;
	cout << "m2 == m4: " << (m2 == m4) << endl;
	cout << "m2 != m4: " << (m2 != m4) << endl;
}

void testSingleElementAccess(const Matrix &m1, const Matrix &m2, const Matrix &m3)
{
	cout << "Testing single element access" << endl;
	display(m1, m2, m3);
	cout << "m1[2][3] = " << m1(2, 3) << endl;
	cout << "m2[1][2] = " << m1(1, 2) << endl;
	cout << "m3[0][1] = " << m1(0, 1) << endl;
	Matrix m4(m1), m5(m3);
	cout << "Before modification:" << endl;
	cout << "m4: " << endl
		 << m4 << endl;
	cout << "m5: " << endl
		 << m5 << endl;
	m4(2, 2) = 23;
	m4(0, 1) = 0;
	m5(0, 0) = 10;
	m5(1, 1) = 99;
	cout << "After modification:" << endl;
	cout << "m4: " << endl
		 << m4 << endl;
	cout << "m5: " << endl
		 << m5 << endl;
}

void testExceptions()
{
	cout << "Testing exceptions" << endl;

	cout << "Adding matrices with differente dimensions" << endl;

	try
	{
		Matrix m1(2, 4), m2(5, 7);
		Matrix res = m1 + m2;
		cout << "Test failed" << endl;
	}
	catch (Matrix::UnevenMatrixDimensionsException &umde)
	{
		cerr << umde.what() << endl;
		cout << "Test succeded" << endl;
	}

	cout << "Multiplying matrices with differente dimensions" << endl;

	try
	{
		Matrix m1(2, 4), m2(5, 7);
		Matrix res = m1 * m2;
		cout << "Test failed" << endl;
	}
	catch (Matrix::UnevenMatrixDimensionsException &umde)
	{
		cerr << umde.what() << endl;
		cout << "Test succeded" << endl;
	}

	cout << "Accessing elements out of range" << endl;
	
	try
	{
		Matrix m1(2, 4);
		m1(3, 5) = 8;
		cout << "Test failed" << endl;
	}
	catch (Matrix::MatrixIndexOutOfRangeException &miore)
	{
		cerr << miore.what() << endl;
		cout << "Test succeded" << endl;
	}
}