#include <iostream>
#include "Matrix.h"

using namespace std;

#define ERROR 1

Matrix::Matrix(int cols_num, int rows_num)
    :columns{cols_num}, rows{rows_num} 
{
    int **elements = new int*[columns];
    for (int index = 0; index<columns; index++)
    {
        elements[index] = new int[rows];
    }
}

Matrix::Matrix()
{
    
}

Matrix::Matrix(const Matrix &other)
{
    Matrix(other.columns, other.rows);
    for(int col = 0; col < columns; col++)
    {
        for (int row = 0; row < rows; row++)
        {
            elements[col][row] = other.elements[col][row];
        }
    }
}

Matrix::~Matrix()
{
    for (int index = 0; index<columns; index++)
    {
        delete [] elements[index];
    }
    delete [] elements;
}

Matrix Matrix::operator+(const Matrix &other) const
{
    if(columns == other.columns && rows == other.rows)
    {
        Matrix result(columns, rows);
        for(int col = 0; col < columns; col++)
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
        //raise an exception
        return;
    }
}

Matrix Matrix::operator-(const Matrix &other) const
{
    if(columns == other.columns && rows == other.rows)
    {
        Matrix result(columns, rows);
        for(int col = 0; col < columns; col++)
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
        //raise an exception
        return;
    }
}

Matrix Matrix::operator*(const Matrix &other) const
{
    Matrix result;

    return result;
}

Matrix &Matrix::operator+=(const Matrix &other)
{
    if(columns == other.columns && rows == other.rows)
    {
        for(int col = 0; col < columns; col++)
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
        //raise an exception
        return;
    }
}

Matrix &Matrix::operator-=(const Matrix &other)
{
    if(columns == other.columns && rows == other.rows)
    {
        for(int col = 0; col < columns; col++)
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
        //raise an exception
        return;
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
    if(columns == other.columns && rows == other.rows)
    {
        for(int col = 0; col < columns; col++)
        {
            for (int row = 0; row < rows; row++)
            {
                if(elements[col][row] != other.elements[col][row])
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
    if(columns == other.columns && rows == other.rows)
    {
        for(int col = 0; col < columns; col++)
        {
            for (int row = 0; row < rows; row++)
            {
                if(elements[col][row] != other.elements[col][row])
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
    for(int col = 0; col < other.columns; col++)
        {
            for (int row = 0; row < other.rows; row++)
            {
                os << other.elements[col][row] << "";
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
    }
    else
        return;
        // raise exception
}

Matrix operator-(double num, const Matrix &obj)
{
    if (obj.columns == 1 && obj.rows == 1)
    {
        Matrix result(1, 1);
        result.elements[0][0] = num - obj.elements[0][0];
    }
    else
        return;
        // raise exception
}

Matrix operator*(double num, const Matrix &obj)
{
    return;
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
