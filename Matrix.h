#pragma once

class Matrix
{
    int columns;
    int rows;
    int **elements;
public:
    
    Matrix(double element);
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

    friend std::ostream &operator<<(std::ostream &os, const Matrix &other);
    friend Matrix operator+(double num, const Matrix &obj);
    friend Matrix operator-(double num, const Matrix &obj);
    friend Matrix operator*(double num, const Matrix &obj);
    friend bool operator==(double num, const Matrix &obj);
    friend bool operator!=(double num, const Matrix &obj);
};

