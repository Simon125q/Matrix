#include <iostream>
#include "Matrix.h"

using namespace std;

#define ERROR 1

Matrix::Matrix(int cols_num, int rows_num)
    : columns{cols_num}, rows{rows_num}
{
    int **elements = new int *[columns];
    for (int index = 0; index < rows; index++)
    {
        elements[index] = new int[columns];
    }
    for(int col = 0; col < columns; col++)
    {
        for(int row = 0; row < rows; row++)
        {
            elements[row][col] = 0;
        }
    }
}

Matrix::Matrix(double element)
    : columns{1}, rows{1}
{
    int **elements = new int *[columns];
    for (int index = 0; index < columns; index++)
    {
        elements[index] = new int[rows];
    }
    elements[0][0] = element;
}

Matrix::Matrix(const Matrix &other)
{
    Matrix(other.columns, other.rows);
    for (int col = 0; col < columns; col++)
    {
        for (int row = 0; row < rows; row++)
        {
            elements[col][row] = other.elements[col][row];
        }
    }
}

Matrix::~Matrix()
{
    for (int index = 0; index < columns; index++)
    {
        delete[] elements[index];
    }
    delete[] elements;
}

Matrix Matrix::operator+(const Matrix &other) const
{
    if (columns == other.columns && rows == other.rows)
    {
        Matrix result(columns, rows);
        for (int col = 0; col < columns; col++)
        {
            for (int row = 0; row < rows; row++)
            {
                result.elements[col][row] += other.elements[col][row];
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
        for (int col = 0; col < columns; col++)
        {
            for (int row = 0; row < rows; row++)
            {
                result.elements[col][row] -= other.elements[col][row];
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
        for (int m = 0; m < rows; m++)
        {
            for (int r = 0; r < other.columns; r++)
            {
                result.elements[r][m] = 0;
                for (int k = 0; k < other.rows; k++)
                {
                    result.elements[r][m] += elements[k][m] * other.elements[r][k];
                }
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
        for (int col = 0; col < columns; col++)
        {
            for (int row = 0; row < rows; row++)
            {
                elements[col][row] -= other.elements[col][row];
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
        for (int col = 0; col < columns; col++)
        {
            for (int row = 0; row < rows; row++)
            {
                if (elements[col][row] != other.elements[col][row])
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
        for (int col = 0; col < columns; col++)
        {
            for (int row = 0; row < rows; row++)
            {
                if (elements[col][row] != other.elements[col][row])
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
    for (int col = 0; col < other.columns; col++)
    {
        for (int row = 0; row < other.rows; row++)
        {
            os << other.elements[col][row] << " ";
        }
        os << endl;
    }
    return os;
}

Matrix operator+(double num, const Matrix &obj)
{
    if (obj.columns == 1 && obj.rows == 1)
    {
        Matrix result(1, 1);
        result.elements[0][0] = obj.elements[0][0] + num;
        return result;
    }
    else
        return Matrix(obj);
    // raise exception
}

Matrix operator-(double num, const Matrix &obj)
{
    if (obj.columns == 1 && obj.rows == 1)
    {
        Matrix result(1, 1);
        result.elements[0][0] = num - obj.elements[0][0];
        return result;
    }
    else
        return Matrix(obj);
    // raise exception
}

Matrix operator*(double num, const Matrix &obj)
{
    Matrix result(obj);
    for (int col = 0; col < result.columns; col++)
    {
        for (int row = 0; row < result.rows; row++)
        {
            result.elements[col][row] += num;
        }
    }
    return result;
}

bool operator==(double num, const Matrix &obj)
{
    if (obj.columns != 1 || obj.rows != 1)
        return false;
    else if (obj.elements[0][0] != num)
        return false;
    return true;
}

bool operator!=(double num, const Matrix &obj)
{
    if (obj.columns != 1 || obj.rows != 1)
        return true;
    else if (obj.elements[0][0] != num)
        return true;
    return false;
}
