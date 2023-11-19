#include <iostream>
#include "Matrix.h"

using namespace std;

#define ERROR 1

Matrix::Matrix()
{
}

Matrix::Matrix(const Matrix &other)
{
}

Matrix Matrix::operator+(const Matrix &other) const
{
    Matrix result;

    return result;
}

Matrix Matrix::operator-(const Matrix &other) const
{
    Matrix result;

    return result;
}

Matrix Matrix::operator*(const Matrix &other) const
{
    Matrix result;

    return result;
}

Matrix &Matrix::operator+=(const Matrix &other)
{
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &other)
{
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &other)
{
    return *this;
}

Matrix &Matrix::operator=(const Matrix &other)
{
    return *this;
}

bool Matrix::operator==(const Matrix &other) const
{

    return false;
}

bool Matrix::operator!=(const Matrix &other) const
{
    return false;
}

ostream &operator<<(ostream &os, const Matrix &other)
{

    return os;
}

Matrix operator+(double num, const Matrix &obj)
{
    return;
}

Matrix operator-(double num, const Matrix &obj)
{
    return;
}

Matrix operator*(double num, const Matrix &obj)
{
    return;
}

bool operator==(double num, const Matrix &obj)
{
    return false;
}

bool operator!=(double num, const Matrix &obj)
{
    return false;
}
