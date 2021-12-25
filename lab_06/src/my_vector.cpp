#include "my_vector.h"

void MyVector::init(std::size_t init_sz, std::size_t init_cp) {
    _sz = init_sz;
    _cp = init_cp;
    _data = (int*)calloc(_cp, sizeof(int));
}

void MyVector::cp_init(const MyVector &mv) {
    init(mv._sz, mv._cp);
    memcpy(_data, mv._data, sizeof(int) * _sz);
}

void MyVector::delete_data() {
    if(_data == nullptr)
        return;
    free(_data);
    _data = nullptr;
}

MyVector::MyVector(std::size_t init_capacity) {
    init(0, init_capacity);
}

MyVector::MyVector(const MyVector &mv) {
    cp_init(mv);
}

MyVector& MyVector::operator=(const MyVector &mv) {
    if(this == &mv)
        return *this;
    delete_data();
    cp_init(mv);
    return *this;
}

MyVector::~MyVector() {
    delete_data();
}

void MyVector::set(std::size_t index, int value) {
    _data[index] = value;
}

int MyVector::get(std::size_t index) {
    return _data[index];
}

std::size_t MyVector::size() {
    return _sz;
}

std::size_t MyVector::capacity() {
    return _cp;
}

void MyVector::reserve(std::size_t new_capacity) {
    if(new_capacity <= _cp)
        return;
    _data = (int*)realloc(_data, sizeof(int) * new_capacity);
    _cp = new_capacity;
}

void MyVector::resize(std::size_t new_size) {
    if(new_size > _cp)
        reserve(std::max(2 * _cp, new_size));
    if(new_size > _sz)
        memset(_data + _sz, 0, sizeof(int) * (new_size - _sz));
    _sz = new_size;
}

void MyVector::push_back(int value) {
    resize(_sz + 1);
    _data[_sz - 1] = value;
}

void MyVector::insert(std::size_t index, int value) {
    resize(_sz + 1);
    for(int i = _sz - 2; i >= (int)index; i--)
        _data[i + 1] = _data[i];
    _data[index] = value;
}

void MyVector::erase(std::size_t index) {
    resize(_sz - 1);
    for(int i = index; i < (int)_sz; i++)
        _data[i] = _data[i + 1];
}
