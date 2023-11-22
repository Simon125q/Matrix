#pragma once

class Matrix
{
public:
    int **elements;
    int rows;
    int columns;
    Matrix();
    Matrix(int cols_num, int rows_num);
    Matrix(const Matrix &other);
    ~Matrix();
    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    Matrix &operator+=(const Matrix &other);
    Matrix &operator-=(const Matrix &other);
    Matrix &operator*=(const Matrix &other);
    Matrix &operator=(const Matrix &other);
    bool operator==(const Matrix &other) const;
    bool operator!=(const Matrix &other) const;
};

std::ostream &operator<<(std::ostream &os, const Matrix &other);
Matrix operator+(double num, const Matrix &obj);
Matrix operator-(double num, const Matrix &obj);
Matrix operator*(double num, const Matrix &obj);
bool operator==(double num, const Matrix &obj);
bool operator!=(double num, const Matrix &obj);