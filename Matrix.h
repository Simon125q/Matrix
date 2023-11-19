#pragma once

class Matrix
{
public:
    Matrix();
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