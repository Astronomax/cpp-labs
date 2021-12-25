#include "matrix.h"

MatrixException::MatrixException(std::string what) : what_(what) {

}

const char *MatrixException::what() const noexcept {
    return what_.c_str();
}

Matrix::~Matrix() {
    if (_data == nullptr)
        return;
    delete[] _data[0];
    delete[] _data;
}

Matrix::Matrix() : _rows(0), _cols(0), _data(nullptr) {

}

Matrix::Matrix(int r, int c) {
    if(r == 0 || c == 0) {
        _rows = _cols = 0;
        _data = nullptr;
    }
    else {
        try {
            _rows = r;
            _cols = c;
            int *temp = new int[r * c];
            std::fill(temp, temp + r * c, 0);
            _data = new int *[r];
            for (int i = 0; i < r; i++)
                _data[i] = &temp[i * c];
        }
        catch (...) {
            delete[] _data[0];
            delete[] _data;
            throw MatrixException("Unable to allocate memory.");
        }
    }
}

Matrix::Matrix(const Matrix &another) : Matrix(another._rows, another._cols) {
    memcpy(_data[0], another._data[0], sizeof(int) * _rows * _cols);
}

Matrix &Matrix::operator=(Matrix another) noexcept {
    if (this == &another)
        return *this;
    std::swap(_data, another._data);
    std::swap(_rows, another._rows);
    std::swap(_cols, another._cols);
    return *this;
}

int Matrix::get_rows() const noexcept {
    return _rows;
}

int Matrix::get_cols() const noexcept {
    return _cols;
}

int *Matrix::operator[](int index) const {
    return _data[index];
}

int &Matrix::get(int row, int col) const {
    if (row < 0 || row >= _rows || col < 0 || col >= _cols)
        throw MatrixException("ACCESS: bad index.");
    return _data[row][col];
}

Matrix operator*(const Matrix &a, const Matrix &b) {
    if (a.get_cols() != b.get_rows())
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    int na = a.get_rows(), len = a.get_cols();
    int mb = b.get_cols();
    Matrix res(na, mb);
    for (int i = 0; i < na; i++)
        for (int j = 0; j < mb; j++)
            for (int k = 0; k < len; k++)
                res[i][j] += a[i][k] * b[k][j];
    return res;
}

Matrix operator+(const Matrix &a, const Matrix &b) {
    if (a.get_rows() != b.get_rows() || a.get_cols() != b.get_cols())
        throw MatrixException("ADD: dimensions do not match.");
    int na = a.get_rows(), ma = a.get_cols();
    Matrix res(na, ma);
    for (int i = 0; i < na; i++)
        for (int j = 0; j < ma; j++)
            res[i][j] = a[i][j] + b[i][j];
    return res;
}

Matrix &Matrix::operator*=(const Matrix &m) {
    return (*this) = (*this) * m;
}

Matrix &Matrix::operator+=(const Matrix &m) {
    return (*this) = (*this) + m;
}

Matrix load(std::ifstream &in) {
    int rows, cols;
    in >> rows >> cols;
    Matrix m(rows, cols);
    for (int i = 0; i < m.get_rows(); i++)
        for (int j = 0; j < m.get_cols(); j++)
            in >> m[i][j];
    return m;
}

std::ostream &operator<<(std::ostream &out, const Matrix &mat) {
    for (int i = 0; i < mat.get_rows(); i++) {
        for (int j = 0; j < mat.get_cols(); j++)
            out << mat[i][j] << " ";
        out << std::endl;
    }
    return out;
}
