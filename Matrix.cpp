#include <iostream>
#include "Matrix.h"

using namespace std;

#define ERROR 1

// Matrix definitions

Matrix::Matrix(unsigned int rows_num, unsigned int cols_num)
{
    cout << "Matrix created" << endl;
    rcdata *new_data = new rcdata(rows_num, cols_num);
    data = new_data;
}

Matrix::Matrix(const Matrix &other)
{
    cout << "matrix created pointing to other matrix data" << endl;
    data = other.data;
    data->rccounter++;
}

Matrix::~Matrix()
{

    data->rccounter--;
    cout<< "rccounter: "<<data->rccounter<<endl;
    if (data->rccounter == 0)
    {
        cout << "Matrix destroyed" << endl;
        
        delete data;
    }
    else
    {
        cout << "Matrix nulled" << endl;
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
        throw UnevenMatrixDimensionsException();
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
        throw UnevenMatrixDimensionsException();
    }
}

Matrix Matrix::operator*(const Matrix &other) const
{
    return Matrix(0, 0);
}

Matrix &Matrix::operator+=(const Matrix &other)
{
    if (this->getRowsNum() == other.getRowsNum() && this->getColsNum() == other.getColsNum())
    {
        data = data->detach();
        for (unsigned int row = 0; row < this->getRowsNum(); row++)
        {
            for (unsigned int col = 0; col < this->getColsNum(); col++)
            {
                data->elements[row][col] += other.data->elements[row][col];
            }
        }
    }
    else
        throw Matrix::UnevenMatrixDimensionsException();

    return *this;
}

Matrix &Matrix::operator-=(const Matrix &other)
{
    cout << "subtraction (-=)" << endl;

    if (this->getRowsNum() == other.getRowsNum() && this->getColsNum() == other.getColsNum())
    {
        data = data->detach();
        for (unsigned int row = 0; row < this->getRowsNum(); row++)
        {
            for (unsigned int col = 0; col < this->getColsNum(); col++)
            {
                data->elements[row][col] -= other.data->elements[row][col];
            }
        }
    }
    else
        throw Matrix::UnevenMatrixDimensionsException();

    return *this;
}

Matrix &Matrix::operator*=(const Matrix &other)
{
    return *this;
}

bool Matrix::operator==(const Matrix &other) const
{
    if (this->getRowsNum() == other.getRowsNum() && this->getColsNum() == other.getColsNum())
    {
        for (unsigned int row = 0; row < this->getRowsNum(); row++)
        {
            for (unsigned int col = 0; col < this->getColsNum(); col++)
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
        for (unsigned int row = 0; row < this->getRowsNum(); row++)
        {
            for (unsigned int col = 0; col < this->getColsNum(); col++)
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

unsigned int Matrix::getRowsNum() const
{
    return data->rows;
}

unsigned int Matrix::getColsNum() const
{
    return data->cols;
}

double Matrix::operator()(unsigned int r, unsigned int c) const
{
    if (r > this->getRowsNum() || c > this->getColsNum())
    {
        throw Matrix::MatrixIndexOutOfRangeException();
    }
    return data->elements[r][c];
}

Matrix::Mref Matrix::operator()(unsigned int r, unsigned int c)
{
    if (r > this->getRowsNum() || c > this->getColsNum())
    {
        throw Matrix::MatrixIndexOutOfRangeException();
    }
    return Mref(*this, r, c);
}

ostream &operator<<(std::ostream &os, const Matrix &obj)
{
    for (unsigned int row = 0; row < obj.getRowsNum(); row++)
    {
        for (unsigned int col = 0; col < obj.getColsNum(); col++)
        {
            os << obj.data->elements[row][col] << " ";
        }
        os << endl;
    }
    return os;
}

istream &operator>>(std::istream &is, Matrix &obj)
{
    for (unsigned int row = 0; row < obj.getRowsNum(); row++)
    {
        for (unsigned int col = 0; col < obj.getColsNum(); col++)
        {
            if (!(is >> obj.data->elements[row][col]))
                throw Matrix::WrongDataTypeException();
        }
    }
    return is;
}

// rcdata definitions

Matrix::rcdata::rcdata(unsigned int rows_no, unsigned int cols_no)
{
    cout << "rcdata created" << endl;
    rows = rows_no;
    cols = cols_no;
    rccounter = 1;

    elements = new double *[rows] {};
    for (unsigned int row = 0; row < rows; row++)
    {
        elements[row] = new double[cols]{};
    }
}

Matrix::rcdata::rcdata(const rcdata &other) // ------->
{
    cout << "rcdata created based on other" << endl;
    rows = other.rows;
    cols = other.cols;
    rccounter = 1;

    elements = new double *[rows] {};
    for (unsigned int row = 0; row < rows; row++)
    {
        elements[row] = new double[cols]{};
    }

    for (unsigned int row = 0; row < rows; row++)
    {
        for (unsigned int col = 0; col < cols; col++)
        {
            elements[row][col] = other.elements[row][col];
        }
    }
}

Matrix::rcdata::~rcdata()
{
    cout << "rcdata destroyed" << endl;
    for (unsigned int row = 0; row < rows; row++)
    {
        delete[] elements[row];
    }
    delete[] elements;
}

Matrix::rcdata &Matrix::rcdata::operator=(const Matrix::rcdata &other) //----->
{
    if (rccounter == 1)
    {
        for (unsigned int row = 0; row < rows; row++)
        {
            delete[] elements[row];
        }
        delete[] elements;
    }
    else
        rccounter--;

    rows = other.rows;
    cols = other.cols;

    elements = new double *[rows] {};
    for (unsigned int row = 0; row < rows; row++)
    {
        elements[row] = new double[cols]{};
    }

    for (unsigned int row = 0; row < rows; row++)
    {
        for (unsigned int col = 0; col < cols; col++)
        {
            elements[row][col] = other.elements[row][col];
        }
    }

    return *this;
}

Matrix::rcdata *Matrix::rcdata::detach()
{
    if (rccounter == 1)
    {
        return this;
    }

    rccounter--;
    
    rcdata *new_data = new rcdata(rows, cols);

    for (unsigned int row = 0; row < rows; row++)
    {
        for (unsigned int col = 0; col < cols; col++)
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
    return *this;
}

// Matrix::Mref &Matrix::Mref::operator=(const Mref &ref) {}