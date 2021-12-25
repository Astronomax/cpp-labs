#include <iostream>

#include "my_vector.h"
#include <cassert>
#include <cstring>
#include <random>
#include <chrono>

namespace product {
    class Product {
    public:
        ~Product() {
            delete [] name_;
        }
        Product(const Product &p) {
            name_ = new char[strlen(p.name_) + 1];
            strcpy(name_, p.name_);
            quantity_ = p.quantity_;
            price_ = p.price_;
        }
        Product(const char* name, int quantity, double price) {
            name_ = new char[strlen(name) + 1];
            strcpy(name_, name);
            quantity_ = quantity;
            price_ = price;
        }
        friend std::ostream& operator<< (std::ostream& out, const Product &p);
    private:
        char *name_;
        int quantity_;
        double price_;
    };

    std::ostream& operator<< (std::ostream& out, const Product &p) {
        out << std::string(p.name_) << " " << p.quantity_ << " " << p.price_;
        return out;
    }

    void print(const containers::my_vector<Product>& v) {
        std::cout << v << std::endl;
    }
}

template<typename T>
void test_my_vector(std::initializer_list<T> l) {
    std::cout << "test_my_vector" << std::endl;
    containers::my_vector<T> v;
    assert(v.empty());
    for(auto &i : l)
        v.push_back(i);
    std::size_t n = l.size();
    std::cout << v << std::endl;
    assert(v.size() == n);
    assert(!v.empty());
    T last = T(v[v.size() - 1]);
    v.pop_back();
    std::cout << v << std::endl;
    assert(v.size() == --n);
    v.push_back(last);
    std::cout << v << std::endl;
    assert(v.size() == ++n);
    v.clear();
    std::cout << v << std::endl;
    assert(v.size() == 0);
    assert(v.empty());
    v.reserve(10);
    assert(v.capacity() == 16);
}

template<typename T>
void test_my_vector_default_constructable(std::initializer_list<T> l) {
    std::cout << "test_my_vector_default_constructable" << std::endl;
    containers::my_vector<T> v;
    assert(v.empty());
    for(auto &i : l)
        v.push_back(i);

    std::size_t n = l.size();
    std::cout << v << std::endl;
    assert(v.size() == n);
    assert(!v.empty());
    T last = v[v.size() - 1];
    v.pop_back();
    std::cout << v << std::endl;
    assert(v.size() == --n);
    v.push_back(last);
    std::cout << v << std::endl;
    assert(v.size() == ++n);
    v.resize(200);
    std::cout << v << std::endl;
    assert(v.size() == 200);
    v.clear();
    std::cout << v << std::endl;
    assert(v.size() == 0);
    assert(v.empty());
    v.reserve(10);
    assert(v.capacity() == 256);
}

using namespace product;

int main() {
    test_my_vector<int>({5, 10});
    test_my_vector<Product>({Product("asdf", 4, 12.0), Product("qwe", -1, 7.5)});
    test_my_vector_default_constructable<int>({5, 10});
    return 0;
}

