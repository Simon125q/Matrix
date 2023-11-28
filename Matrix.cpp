#include <iostream>
#include "Matrix.h"

using namespace std;

#define ERROR 1

Matrix::Matrix(int cols_num, int rows_num)
    : columns{cols_num}, rows{rows_num}
{
    elements = new int*[rows];
    for (int index = 0; index<rows; index++)
    {
        elements[index] = new int[columns];
    }
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < columns; col++)
        {
            elements[row][col] = 0;
        }
    }
}

Matrix::Matrix(double element)
    : columns{1}, rows{1}
{
    elements = new int *[rows];
    for (int index = 0; index < rows; index++)
    {
        elements[index] = new int[columns];
    }
    elements[0][0] = element;
}

Matrix::Matrix(const Matrix &other)
{
    for (int index = 0; index < rows; index++)
    {
        delete[] elements[index];
    }
    delete[] elements;
    
    Matrix(other.columns, other.rows);
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < columns; col++)
        {
            elements[row][col] = other.elements[row][col];
        }
    }
}

Matrix::~Matrix()
{
    for (int index = 0; index < rows; index++)
    {
        delete[] elements[index];
    }
    delete[] elements;
}

Matrix Matrix::operator+(const Matrix &other) const
{
    if (columns == other.columns && rows == other.rows)
    {
        Matrix result(other);
        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < columns; col++)
            {
                result.elements[row][col] += other.elements[row][col];
            }
        }
        return result;
    }
    else
    {
        // raise an exception
        return Matrix(other);
    }
}

Matrix Matrix::operator-(const Matrix &other) const
{
    if (columns == other.columns && rows == other.rows)
    {
        Matrix result(columns, rows);
        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < columns; col++)
            {
                result.elements[row][col] -= other.elements[row][col];
            }
        }
        return result;
    }
    else
    {
        // raise an exception
        return Matrix(other);
    }
}

Matrix Matrix::operator*(const Matrix &other) const
{
    if (columns == other.rows)
    {
        Matrix result(other.columns, rows);
        
        return result;
    }
    else
    {
        // raise an exception
        return Matrix(other);
    }
}

Matrix &Matrix::operator+=(const Matrix &other)
{
    if (columns == other.columns && rows == other.rows)
    {
        for (int col = 0; col < columns; col++)
        {
            for (int row = 0; row < rows; row++)
            {
                elements[col][row] += other.elements[col][row];
            }
        }
        return *this;
    }
    else
    {
        // raise an exception
        return *this;
    }
}

Matrix &Matrix::operator-=(const Matrix &other)
{
    if (columns == other.columns && rows == other.rows)
    {
        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < columns; col++)
            {
                elements[row][col] -= other.elements[row][col];
            }
        }
        return *this;
    }
    else
    {
        // raise an exception
        return *this;
    }
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
    if (columns == other.columns && rows == other.rows)
    {
        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < columns; col++)
            {
                if (elements[row][col] != other.elements[row][col])
                    return false;
            }
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool Matrix::operator!=(const Matrix &other) const
{
    if (columns == other.columns && rows == other.rows)
    {
        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < columns; col++)
            {
                if (elements[row][col] != other.elements[row][col])
                    return true;
            }
        }
    }
    else
    {
        return true;
    }
    return false;
}

ostream &operator<<(ostream &os, const Matrix &other)
{
    for (int row = 0; row < other.rows; row++)
    {
        for (int col = 0; col < other.columns; col++)
        {
            os << other.elements[row][col] << " ";
        }
        os << endl;
    }
    return os;
}

