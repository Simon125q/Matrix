#include <iostream>
#include "Matrix.h"

using namespace std;

#define ERROR 1
#define TEST 0

// Matrix definitions

Matrix::Matrix(unsigned int rows_num, unsigned int cols_num)
{
    if (TEST)
        cout << "Matrix created" << endl;
    try
    {
        rcdata *new_data = new rcdata(rows_num, cols_num);
        data = new_data
    }
    catch (bad_alloc &bae)
    {
        cerr << "bad_alloc detected: " << bae.what() << endl;
        exit(ERROR);
    }
}

Matrix::Matrix(const Matrix &other)
{
    if (TEST)
        cout << "matrix created pointing to other matrix data" << endl;
    data = other.data;
    data->rccounter++;
}

Matrix::~Matrix()
{

    data->rccounter--;
    if (TEST)
        cout << "rccounter: " << data->rccounter << endl;
    if (data->rccounter == 0)
    {
        if (TEST)
            cout << "Matrix destroyed" << endl;

        delete data;
    }
    else
    {
        if (TEST)
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
    try
    {
        if (this->getRowsNum() == other.getRowsNum() && this->getColsNum() == other.getColsNum())
        {
            return (Matrix(*this) += other);
        }
        else
            throw Matrix::UnevenMatrixDimensionsException();
    }
    catch (Matrix::UnevenMatrixDimensionsException &umde)
    {
        cerr << umde.what() << endl;
        exit(ERROR);
    }
}

Matrix Matrix::operator-(const Matrix &other) const
{
    try
    {
        if (this->getRowsNum() == other.getRowsNum() && this->getColsNum() == other.getColsNum())
        {
            return (Matrix(*this) -= other);
        }
        else
            throw Matrix::UnevenMatrixDimensionsException();
    }
    catch (Matrix::UnevenMatrixDimensionsException &umde)
    {
        cerr << umde.what() << endl;
        exit(ERROR);
    }
}

Matrix Matrix::operator*(const Matrix &other) const
{
    unsigned int r1 = this->getRowsNum();
    unsigned int c1 = this->getColsNum();
    unsigned int r2 = other.getRowsNum();
    unsigned int c2 = other.getColsNum();
    Matrix result(r1, c2);
    try
    {
        if (c1 == r2)
        {
            for (unsigned int row1 = 0; row1 < r1; row1++)
            {
                for (unsigned int col2 = 0; col2 < c2; col2++)
                {
                    result.data->elements[row1][col2] = 0;
                    for (unsigned int row2 = 0; row2 < r2; row2++)
                    {
                        result.data->elements[row1][col2] += data->elements[row1][row2] * other.data->elements[row2][col2];
                    }
                }
            }
        }
        else
            throw Matrix::UnevenMatrixDimensionsException();
    }
    catch (Matrix::UnevenMatrixDimensionsException &umde)
    {
        cerr << umde.what() << endl;
        exit(ERROR);
    }
    return result;
}

Matrix &Matrix::operator+=(const Matrix &other)
{
    try
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
    }
    catch (Matrix::UnevenMatrixDimensionsException &umde)
    {
        cerr << umde.what() << endl;
        exit(ERROR);
    }

    return *this;
}

Matrix &Matrix::operator-=(const Matrix &other)
{
    try
    {
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
    }
    catch (Matrix::UnevenMatrixDimensionsException &umde)
    {
        cerr << umde.what() << endl;
        exit(ERROR);
    }

    return *this;
}

Matrix &Matrix::operator*=(const Matrix &other)
{
    unsigned int r1 = this->getRowsNum();
    unsigned int c1 = this->getColsNum();
    unsigned int r2 = other.getRowsNum();
    unsigned int c2 = other.getColsNum();

    try
    {
        Matrix result(r1, c2);
        if (c1 == r2)
        {
            for (unsigned int row1 = 0; row1 < r1; row1++)
            {
                for (unsigned int col2 = 0; col2 < c2; col2++)
                {
                    result.data->elements[row1][col2] = 0;
                    for (unsigned int row2 = 0; row2 < r2; row2++)
                    {
                        result.data->elements[row1][col2] += data->elements[row1][row2] * other.data->elements[row2][col2];
                    }
                }
            }
        }
        else
            throw Matrix::UnevenMatrixDimensionsException();

        *this = result;
    }
    catch (Matrix::UnevenMatrixDimensionsException &umde)
    {
        cerr << umde.what() << endl;
        exit(ERROR);
    }

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
    try
    {
        if (r > this->getRowsNum() || c > this->getColsNum())
        {
            throw Matrix::MatrixIndexOutOfRangeException();
        }
        return data->elements[r][c];
    }
    catch (Matrix::MatrixIndexOutOfRangeException &miore)
    {
        cerr << miore.what() << endl;
        exit(ERROR);
    }
}

Matrix::Mref Matrix::operator()(unsigned int r, unsigned int c)
{
    try
    {
        if (r > this->getRowsNum() || c > this->getColsNum())
        {
            throw Matrix::MatrixIndexOutOfRangeException();
        }
        return Mref(*this, r, c);
    }
    catch (Matrix::MatrixIndexOutOfRangeException &miore)
    {
        cerr << miore.what() << endl;
        exit(ERROR);
    }
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
    try
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
    catch (Matrix::MatrixIndexOutOfRangeException &wdte)
    {
        cerr << wdte.what() << endl;
        exit(ERROR);
    }
}

// rcdata definitions

Matrix::rcdata::rcdata(unsigned int rows_no, unsigned int cols_no)
{
    if (TEST)
        cout << "rcdata created" << endl;
    rows = rows_no;
    cols = cols_no;
    rccounter = 1;

    try
    {
        elements = new double *[rows] {};
        for (unsigned int row = 0; row < rows; row++)
        {
            elements[row] = new double[cols]{};
        }
    }
    catch (bad_alloc &bae)
    {
        cerr << "bad_alloc detected: " << bae.what() << endl;
        exit(ERROR);
    }
}

Matrix::rcdata::rcdata(const rcdata &other)
{
    if (TEST)
        cout << "rcdata created based on other" << endl;
    rows = other.rows;
    cols = other.cols;
    rccounter = 1;
    try
    {
        elements = new double *[rows] {};
        for (unsigned int row = 0; row < rows; row++)
        {
            elements[row] = new double[cols]{};
        }
    }
    catch (bad_alloc &bae)
    {
        cerr << "bad_alloc detected: " << bae.what() << endl;
        exit(ERROR);
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
    if (TEST)
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
    try
    {
        elements = new double *[rows] {};
        for (unsigned int row = 0; row < rows; row++)
        {
            elements[row] = new double[cols]{};
        }
    }
    catch (bad_alloc &bae)
    {
        cerr << "bad_alloc detected: " << bae.what() << endl;
        exit(ERROR);
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
    try
    {
        rcdata *new_data = new rcdata(rows, cols);
    }
    catch (bad_alloc &bae)
    {
        cerr << "bad_alloc detected: " << bae.what() << endl;
        exit(ERROR);
    }
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
