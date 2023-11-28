#include <iostream>
#include "Matrix.h"

using namespace std;

void testAssigment();
void testAddition();
void testSubtraction();
void testMultiplication();

int main()
{
    testAssigment();
    testAddition();
    testSubtraction();
    testMultiplication();

    return 0;
}

void testAssigment()
{
    return;
}

void testAddition()
{
    Matrix m1(7, 7);
    Matrix m2(2, 5);
    Matrix m3(7, 7);

    cout << "Matrix m1:" << endl;
    cout << m1 << endl;
    cout << "Matrix m2:" << endl;
    cout << m2 << endl;
    cout << "Matrix m3:" << endl;
    cout << m3 + m1 << endl;

}

void testSubtraction()
{
    return;
}

void testMultiplication()
{
    return;
}