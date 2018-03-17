#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "tools.hpp"
#include "vector.hpp"

enum STACK_ERRORS {
    S_ERR_OK = 0,
    S_ERR_FULL
};

template <typename data_T>
class Stack
{
private:
    size_t size_ = 0;
    /* size_ shows the number of the first free cell */
    size_t capacity_ = 0;
    Vector <data_T> data_;
  
public:
    explicit Stack (size_t capacity);
    Stack          (const Stack& that);
    ~Stack         ();
    int Push       (data_T value);
    int Pop        (data_T* value);
    int  Clear     ();
    bool Ok        () const;
    void Dump      ();
};

template <typename data_T>
Stack<data_T>::Stack(size_t capacity):
    size_     (0),
    capacity_ (capacity),
    data_     (capacity_) 
{
    HERE();
}

template <typename data_T>
Stack<data_T>::Stack(const Stack& that):
    size_     (that.size_),
    capacity_ (that.capacity_),
    data_     (capacity_)
{
    for (size_t i = 0; i < capacity_; i++)
        data_[i] = that.data_[i];
    
    HERE();
}

template <typename data_T>
Stack<data_T>::~Stack() 
{
    HERE();
}

template <typename data_T>
int Stack<data_T>::Push(data_T value)
{
    ASSERT_OK();
    size_++;
    if (!Ok()) {
        size_--;
        printf("Unable to push (full stack)\n");
        return S_ERR_FULL;
    }
    data_[size_-1] = value;
    ASSERT_OK();
    return S_ERR_OK;
}

template <typename data_T>
int Stack<data_T>::Pop(data_T* value)
{
    ASSERT_OK();
    *value = data_[--size_];
    data_[size_] = 0;
    ASSERT_OK(); 
    return S_ERR_OK;
}

template <typename data_T>
int Stack<data_T>::Clear()
{
    ASSERT_OK();
    for (size_t i = 0; i < capacity_; i++)
        data_[i] = (data_T)0;
    size_ = 0;
    ASSERT_OK();
    return S_ERR_OK;
}

template <typename data_T>
bool Stack<data_T>::Ok() const
{
    return size_ >= 0 && size_ <= capacity_ && capacity_ > 0;
}

template <typename data_T>
void Stack<data_T>::Dump()
{
    printf ("Stack  [this: %p; capacity: %zu; size: %zu; data: %p] %s\n",
            this, capacity_, size_, data_, (Ok())? "ok": "ERROR");
    data_.Dump();
}

#endif
