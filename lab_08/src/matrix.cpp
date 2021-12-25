#include "matrix.hpp"
#include <cstring>

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
    for (std::size_t i = 0; i < _rows; i++)
        for (std::size_t j = 0; j < _cols; j++)
            _data[i][j] = 0;
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
