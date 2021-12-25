#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <cstring>
#include <cstddef>

class Matrix {
public:
    Matrix();

    Matrix(int r, int c);

    Matrix(const Matrix &another);

    Matrix &operator=(Matrix another) noexcept;

    ~Matrix();

    int get_rows() const noexcept;

    int get_cols() const noexcept;

    int *operator[](int index) const;

    int &get(int row, int col) const;

    Matrix &operator*=(const Matrix &m);

    Matrix &operator+=(const Matrix &m);

private:
    int _rows, _cols;
    int **_data;
};

Matrix operator*(const Matrix &a, const Matrix &b);

Matrix operator+(const Matrix &a, const Matrix &b);

Matrix load(std::ifstream &in);

std::ostream &operator<<(std::ostream &out, const Matrix &mat);

class MatrixException : std::exception {
public:
    explicit MatrixException(std::string what);

    const char *what() const noexcept override;

private:
    std::string what_;
};

#endif  // MATRIX_H_
