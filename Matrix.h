#pragma once

class Matrix
{
    struct rcdata;
    class MatrixIndexOutOfRange;
    class UnevenMatrixDimensions;
    rcdata *data;

public:
    class Mref;
    Matrix();
    Matrix(unsigned int rows_num, unsigned int cols_num);
    Matrix(const Matrix &other);
    ~Matrix();
    Matrix &operator=(const Matrix &other);
    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    Matrix &operator+=(const Matrix &other);
    Matrix &operator-=(const Matrix &other);
    Matrix &operator*=(const Matrix &other);

    bool operator==(const Matrix &other) const;
    bool operator!=(const Matrix &other) const;

    int getRowsNum() const;
    int getColsNum() const;

    double read(unsigned int r, unsigned int c) const;
    double write(unsigned int r, unsigned int c, double elem);

    double operator()(unsigned int r, unsigned int c) const;
    Mref operator()(unsigned int r, unsigned int c);

    friend std::ostream &operator<<(std::ostream &os, const Matrix &obj);
    friend std::istream &operator>>(std::istream &is, Matrix &obj);
};

struct Matrix::rcdata
{

public:
    double **elements;
    unsigned int rccounter;
    unsigned int rows;
    unsigned int cols;
    rcdata(unsigned int rows_no, unsigned int cols_no);
    rcdata(const rcdata &);
    ~rcdata();
    rcdata &operator=(const rcdata &);
    rcdata *detach();
};

class Matrix::Mref
{
    friend class Matrix;
    Matrix &m;
    unsigned int r;
    unsigned int c;
    Mref(Matrix &obj, unsigned int r_no, unsigned int c_no)
        : m(obj), r(r_no), c(c_no){};

public:
    operator double() const;
    Matrix::Mref &operator=(double elem);
    Matrix::Mref &operator=(const Mref &ref);
};

class Matrix::MatrixIndexOutOfRange : public exception
{
    const char *what() const throw()
    {
        return "Index is out of matrix range";
    }
};

class Matrix::UnevenMatrixDimensions : public exception
{
    const char *what() const throw()
    {
        return "Operation connot be done, matrices have different dimensions";
    }
};