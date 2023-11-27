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
    Matrix m1(3, 5);
    Matrix m2(3, 5);
    Matrix m3(4, 4);
    cout<<m1;
}

void testSubtraction()
{
    return;
}

void testMultiplication()
{
    return;
}