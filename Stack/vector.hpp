#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

template <typename data_T>
class Vector
{
private:
    data_T* buffer_   = nullptr;
    size_t  size_     = 0;
    size_t  capacity_ = 0;

public:
    Vector(size_t capacity_);
    ~Vector();
    
    data_T& operator[](int position)
    {
        if (position < 0 || position >= capacity_) {
            printf("Memory error\n");
            exit(EXIT_FAILURE);
        }
        return buffer_[position];
    }
};

template <typename data_T>
Vector<data_T>::Vector(size_t capacity):
    buffer_  (new data_T[capacity] {}),
    size_    (0),
    capacity_(capacity)
    {}

template <typename data_T>
Vector<data_T>::~Vector()
{
    delete [] buffer_;
    buffer_ = nullptr;
}

#endif
