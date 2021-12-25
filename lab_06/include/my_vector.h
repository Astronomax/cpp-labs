#ifndef _MY_VECTOR_H_INCLUDED
#define _MY_VECTOR_H_INCLUDED

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <algorithm>

class MyVector {
public: // methods
  MyVector(std::size_t init_capacity = default_cp);
  MyVector(const MyVector&);
  MyVector& operator=(const MyVector &mv);
  ~MyVector();

  void set(std::size_t index, int value);
  int get(std::size_t index);

  std::size_t size();
  std::size_t capacity();

  void reserve(std::size_t new_capacity);
  void resize(std::size_t new_size);
  
  void push_back(int value);
  void insert(std::size_t index, int value);
  void erase(std::size_t index);
private: // fields
  void init(std::size_t init_sz, std::size_t init_cp); 
  void cp_init(const MyVector &mv);
  void delete_data();
  std::size_t _sz, _cp;
  static const std::size_t default_cp = 2;
  int *_data;
};

#endif
