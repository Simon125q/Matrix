#include <iostream>
#include "Matrix.h"

using namespace std;

#define ERROR 1

// Matrix definitions

Matrix::Matrix()
{
    data = new rcdata(0, 0);
}

Matrix::Matrix(unsigned int rows_num, unsigned int cols_num)
{
    data = new rcdata(rows_num, cols_num);
}

Matrix::Matrix(const Matrix &other)
{
    data->rccounter++;
    data = other.data;
}

Matrix::~Matrix()
{
    data->rccounter--;
    if (data->rccounter == 0)
    {
        delete data;
    }
    else
    {
        data = nullptr;
    }
}

Matrix &Matrix::operator=(const Matrix &other)
{
    data->rccounter--;
    if (data->rccounter == 0)
    {
        delete data;
    }
    data = other.data;
    data->rccounter++;

    return *this;
}

Matrix Matrix::operator+(const Matrix &other) const
{
    if (this->getRowsNum() == other.getRowsNum() && this->getColsNum() == other.getColsNum())
    {
        return (Matrix(*this) += other);
    }
    else
    {
        throw UnevenMatrixDimensions();
    }
}
Matrix Matrix::operator-(const Matrix &other) const
{
    if (this->getRowsNum() == other.getRowsNum() && this->getColsNum() == other.getColsNum())
    {
        return (Matrix(*this) -= other);
    }
    else
    {
        throw UnevenMatrixDimensions();
    }
}
Matrix Matrix::operator*(const Matrix &other) const {}

Matrix &Matrix::operator+=(const Matrix &other)
{
    if (this->getRowsNum() == other.getRowsNum() && this->getColsNum() == other.getColsNum())
    {
        data = data->detach();
        for (int row = 0; row < this->getRowsNum(); row++)
        {
            for (int col = 0; col < this->getColsNum(); col++)
            {
                data->elements[row][col] += other.data->elements[row][col];
            }
        }
    }
    else
        throw Matrix::UnevenMatrixDimensions();

    return *this;
}

Matrix &Matrix::operator-=(const Matrix &other)
{
    if (this->getRowsNum() == other.getRowsNum() && this->getColsNum() == other.getColsNum())
    {
        data = data->detach();
        for (int row = 0; row < this->getRowsNum(); row++)
        {
            for (int col = 0; col < this->getColsNum(); col++)
            {
                data->elements[row][col] -= other.data->elements[row][col];
            }
        }
    }
    else
        throw Matrix::UnevenMatrixDimensions();

    return *this;
}

Matrix &Matrix::operator*=(const Matrix &other) {}

bool Matrix::operator==(const Matrix &other) const
{
    if (this->getRowsNum() == other.getRowsNum() && this->getColsNum() == other.getColsNum())
    {
        for (int row = 0; row < this->getRowsNum(); row++)
        {
            for (int col = 0; col < this->getColsNum(); col++)
            {
                if (data->elements[row][col] != other.data->elements[row][col])
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
    if (this->getRowsNum() == other.getRowsNum() && this->getColsNum() == other.getColsNum())
    {
        for (int row = 0; row < this->getRowsNum(); row++)
        {
            for (int col = 0; col < this->getColsNum(); col++)
            {
                if (data->elements[row][col] != other.data->elements[row][col])
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

int Matrix::getRowsNum() const
{
    return data->rows;
}

int Matrix::getColsNum() const
{
    return data->cols;
}

double Matrix::operator()(unsigned int r, unsigned int c) const
{
    if (r > this->getRowsNum() || c > this->getColsNum())
    {
        throw Matrix::MatrixIndexOutOfRange();
    }
    return data->elements[r][c];
}

Matrix::Mref Matrix::operator()(unsigned int r, unsigned int c)
{
    if (r > this->getRowsNum() || c > this->getColsNum())
    {
        throw Matrix::MatrixIndexOutOfRange();
    }
    return Mref(*this, r, c);
}

ostream &operator<<(std::ostream &os, const Matrix &obj)
{
    for (int row = 0; row < obj.getRowsNum(); row++)
    {
        for (int col = 0; col < obj.getColsNum(); col++)
        {
            os << obj.data->elements[row][col] << " ";
        }
        os << endl;
    }
    return os;
}
istream &operator>>(std::istream &is, Matrix &obj) {}

// rcdata definitions

Matrix::rcdata::rcdata(unsigned int rows_no, unsigned int cols_no)
{
    rows = rows_no;
    cols = cols_no;
    rccounter = 1;

    elements = new double *[rows];
    for (int row; row < rows; row++)
    {
        elements[row] = new double[cols];
    }
}

Matrix::rcdata::rcdata(const rcdata & other) {
    if (rccounter == 1)
    {
        for (int row = 0; row < rows; row++)
        {
            delete[] elements[row];
        }
        delete[] elements;   
    }

}

Matrix::rcdata::~rcdata()
{
    for (int row = 0; row < rows; row++)
    {
        delete[] elements[row];
    }
    delete[] elements;
}

Matrix::rcdata &Matrix::rcdata::operator=(const Matrix::rcdata &other) {
    if (rccounter == 1)
    {
        for (int row = 0; row < rows; row++)
        {
            delete[] elements[row];
        }
        delete[] elements;   
    }
    rows = other.rows;

    elements = other.elements;
}

Matrix::rcdata *Matrix::rcdata::detach()
{
    if (rccounter == 1)
    {
        return this;
    }

    rcdata *new_data = new rcdata(rows, cols);

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            new_data->elements[row][col] = elements[row][col];
        }
    }

    return new_data;
}

// Mref definitions

Matrix::Mref::operator double() const
{
    return m.data->elements[r][c];
}

Matrix::Mref &Matrix::Mref::operator=(double elem)
{
    m.data = m.data->detach();
    m.data->elements[r][c] = elem;
}

Matrix::Mref &Matrix::Mref::operator=(const Mref &ref) {}