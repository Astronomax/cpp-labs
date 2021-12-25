#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <iostream>
#include <cstddef>

namespace containers {
    template<typename T>
    class my_vector {
    public:
        my_vector();
        explicit my_vector(std::size_t n);
        my_vector(const my_vector &other);
        my_vector& operator=(my_vector other);
        ~my_vector();

        std::size_t size() const;
        std::size_t capacity() const;
        bool empty();

        void resize(std::size_t n);
        void reserve(std::size_t n);

        T& operator[](std::size_t index) const;

        void push_back(T t);
        void pop_back();
        void clear();
    private:
        void init(std::size_t init_sz, std::size_t init_cp);
        void delete_array_();
    private:
        size_t capacity_;
        size_t size_;
        T* array_;
    };
}

#include "my_vector_impl.h"

#endif  // MY_VECTOR_H_
