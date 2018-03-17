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
    size_t GetSize           ();
    void Dump                ();
    void DumpElem            (size_t cnt) const;
};

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
size_t Vector<data_T>::GetSize()
{
    size_ = 0;
    for (size_t i = 0; i < capacity_; i++) {
        if (buffer_[i] != (data_T)0)
            size_++;
    }
    return size_;
}

template <typename data_T>
void Vector<data_T>::Dump()
{
    printf("Vector [this: %p; capacity: %zu; size: %zu; data: %p]\n",
            this, capacity_, GetSize(), buffer_);
    
    printf("{\n");
    
    for (size_t i = 0; i < capacity_; i++)
        DumpElem(i);
    
    printf("}\n");
}

template <typename data_T>
void Vector<data_T>::DumpElem(size_t cnt) const
{
    printf("\tUnknown type\n");
}

/*________ Partial specialization _______*/
template <>
void Vector<int>::DumpElem(size_t cnt) const
{ 
    printf("\t[%zu] = %i (int)\n", cnt, buffer_[cnt]);
}
 
template <>
void Vector<unsigned>::DumpElem(size_t cnt) const
{ 
    printf("\t[%zu] = %u (unsigned)\n", cnt, buffer_[cnt]);
}

template <>
void Vector<size_t>::DumpElem(size_t cnt) const
{ 
    printf("\t[%zu] = %zu (size_t)\n", cnt, buffer_[cnt]);
}

template <>
void Vector<long>::DumpElem(size_t cnt) const
{ 
    printf("\t[%zu] = %ld (long)\n", cnt, buffer_[cnt]);
}

template <>
void Vector<double>::DumpElem(size_t cnt) const
{ 
    printf("\t[%zu] = %lg (double)\n", cnt, buffer_[cnt]);
}

template <>
void Vector<char>::DumpElem(size_t cnt) const
{ 
    printf("\t[%zu] = %c (char)\n", cnt, buffer_[cnt]);
}
/*_______________________________________*/

#endif
