#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "tools.hpp"

template <typename data_T>
class Vector
{
private:
    data_T* buffer_   = nullptr;
    size_t  size_     = 0;
    size_t  capacity_ = 0;

public:
    explicit Vector          (size_t capacity);
    ~Vector                  ();
    data_T& operator[]       (size_t position);
    const data_T& operator[] (size_t position) const;
 //   void Dump                () const;
};

template <typename data_T>
data_T& Vector<data_T>::operator[](size_t position)
{
    if (position < 0 || position >= capacity_) {
        printf("Memory error\n");
        exit(EXIT_FAILURE);
    }
    return buffer_[position];
}

template <typename data_T>
const data_T& Vector<data_T>::operator[](size_t position) const
{
    if (position < 0 || position >= capacity_) {
        printf("Memory error\n");
        exit(EXIT_FAILURE);
    }
    return buffer_[position];
}

template <typename data_T>
Vector<data_T>::Vector(size_t capacity):
    buffer_  (new data_T[capacity] {}),
    size_    (0),
    capacity_(capacity)
{ 
    HERE(); 
}

template <typename data_T>
Vector<data_T>::~Vector()
{
    HERE();
    delete [] buffer_;
    buffer_ = nullptr;
}

#endif
