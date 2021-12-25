#include "matrix.h"

void Matrix::init(std::size_t r, std::size_t c) {
    _rows = r;
    _cols = c;
    int *temp = new int[r * c];
    _data = new int *[r];
    for (std::size_t i = 0; i < r; i++)
        _data[i] = &temp[i * c];
}

void Matrix::delete_data() {
    if(_data == nullptr)
        return;
    delete[] _data[0];
    delete[] _data;
    _data = nullptr;
}

Matrix::Matrix(std::size_t r, std::size_t c) {
    init(r, c);
    std::fill(_data[0], _data[0] + _rows * _cols, 0);
}

Matrix::Matrix(const Matrix &m) : Matrix(m._rows, m._cols) {
    memcpy(_data[0], m._data[0], sizeof(int) * _rows * _cols);
}

Matrix& Matrix::operator=(const Matrix &m) {
    if(this == &m)
        return *this;
    delete_data();
    init(m._rows, m._cols);
    for (std::size_t i = 0; i < _rows; i++)
        for (std::size_t j = 0; j < _cols; j++)
            _data[i][j] = m.get(i, j);
    return *this;
}

Matrix::~Matrix() {
    delete_data();
}

std::size_t Matrix::get_rows() const {
    return _rows;
}

std::size_t Matrix::get_cols() const {
    return _cols;
}

void Matrix::set(std::size_t i, std::size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
    return _data[i][j];
}

void Matrix::print(FILE *f) {
    for (std::size_t i = 0; i < _rows; i++) {
        for (std::size_t j = 0; j < _cols; j++)
            fprintf(f, "%d ", _data[i][j]);
        fprintf(f, "%c", '\n');
    }
}

bool Matrix::operator==(const Matrix &m) const {
    std::size_t rows = _rows, cols = _cols;
    if (rows != m.get_rows() || cols != m.get_cols())
        return false;
    for (std::size_t i = 0; i < rows; i++)
        for (std::size_t j = 0; j < cols; j++)
            if (_data[i][j] != m.get(i, j))
                return false;
    return true;
}

bool Matrix::operator!=(const Matrix &m) const {
    return !(*this == m);
}

Matrix &Matrix::operator+=(const Matrix &m) {
    std::size_t rows = _rows, cols = _cols;

    for (std::size_t i = 0; i < rows; i++)
        for (std::size_t j = 0; j < cols; j++)
            _data[i][j] = _data[i][j] + m.get(i, j);
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &m) {
    std::size_t rows = _rows, cols = _cols;

    for (std::size_t i = 0; i < rows; i++)
        for (std::size_t j = 0; j < cols; j++)
            _data[i][j] = _data[i][j] - m.get(i, j);
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &m) {
    (*this) = (*this) * m;
    return *this;
}

Matrix Matrix::operator+(const Matrix &m) const {
    Matrix res(*this);
    res += m;
    return res;
}

Matrix Matrix::operator-(const Matrix &m) const {
    Matrix res(*this);
    res -= m;
    return res;
}

Matrix Matrix::operator*(const Matrix &m) const {
    std::size_t rows = _rows, cols = m.get_cols();
    std::size_t len = _cols;

    Matrix res(rows, cols);
    for (std::size_t i = 0; i < rows; i++)
        for (std::size_t j = 0; j < cols; j++)
            for (std::size_t k = 0; k < len; k++)
                res.set(i, j, res.get(i, j) + _data[i][k] * m.get(k, j));
    return res;
}
