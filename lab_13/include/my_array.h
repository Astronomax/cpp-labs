#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstdint>
#include <cassert>

namespace lab_13 {
    template<typename T, std::size_t N>
    class my_array {
    public:
        my_array() {

        }

        my_array(const my_array &a) {
            for(std::size_t i = 0; i < N; i++)
                _data[i] = T(a[i]);
        }

        const T& at(std::size_t index) const {
            assert(index < N && "index is out of range");
            return _data[index];
        }

        T& at(std::size_t index)  {
            assert(index < N && "index is out of range");
            return _data[index];
        }

        const T& operator[](std::size_t index) const {
            return _data[index];
        }

        T& operator[](std::size_t index) {
            return _data[index];
        }

        bool empty() const {
            return !N;
        }

        std::size_t size() const {
            return N;
        }

        void fill(T val) {
            for(std::size_t i = 0; i < N; i++)
                _data[i] = T(val);
        }

    private:
        T _data[N]{};
    };
    
    template<std::size_t N>
    class my_array<bool, N> {
    private:
        class proxy {
        public:
            proxy(const uint8_t &_data, int _bit) : _bit(_bit), _data(const_cast<uint8_t &>(_data)) {
            }

            proxy& operator=(const proxy& a) {
                *this = bool(a);
                return *this;
            }

            operator bool() const {
                return _data & (1 << _bit);
            }

            proxy& operator=(bool val) {
                if((bool)(*this) != val)
                    _data ^= (1 << _bit);
                return *this;
            }

            bool operator==(const proxy& a) const {
                return (bool)(*this) == (bool)(a);
            }
        private:
            int _bit;
            uint8_t &_data;
        };
    public:
        my_array() {
            fill(0);
        }

        my_array(const my_array &a) {
            for(std::size_t i = 0; i < N; i++)
                _data[i] = a[i];
        }

        proxy at(std::size_t index)  {
            assert(index < N && "index is out of range");
            return proxy(_data[index / 8], index % 8);
        }

        proxy operator[](std::size_t index) {
            return proxy(_data[index / 8], index % 8);
        }

        const proxy at(std::size_t index) const {
            assert(index < N && "index is out of range");
            return proxy(_data[index / 8], index % 8);
        }

        const proxy operator[](std::size_t index) const {
            return proxy(_data[index / 8], index % 8);
        }

        bool empty() const {
            return !N;
        }

        std::size_t size() const {
            return N;
        }

        void fill(bool val) {
            uint8_t mask = ((val) ? 255 : 0);
            for(std::size_t i = 0; i < REAL_SIZE; i++)
                _data[i] = mask;
        }

    private:
        static const std::size_t REAL_SIZE = (N + 7) / 8;
        uint8_t _data[REAL_SIZE]{};
    };
}
#endif
