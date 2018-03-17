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
    size_t counter_  = 0;
    /* counter_ shows the number of the first free cell */
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
    void Dump      () const;
    void DumpElem  (size_t cnt) const;
};

template <typename data_T>
Stack<data_T>::Stack(size_t capacity):
    counter_  (0),
    capacity_ (capacity),
    data_     (capacity_) 
{
    HERE();
}

template <typename data_T>
Stack<data_T>::Stack(const Stack& that):
    counter_  (that.counter_),
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
    counter_++;
    if (!Ok()) {
        counter_--;
        printf("Unable to push (full stack)\n");
        return S_ERR_FULL;
    }
    data_[counter_-1] = value;
    ASSERT_OK();
    return S_ERR_OK;
}

template <typename data_T>
int Stack<data_T>::Pop(data_T* value)
{
    ASSERT_OK();
    *value = data_[--counter_];
    data_[counter_] = 0;
    ASSERT_OK(); 
    return S_ERR_OK;
}

template <typename data_T>
int Stack<data_T>::Clear()
{
    ASSERT_OK();
    for (size_t i = 0; i < capacity_; i++)
        data_[i] = (data_T)0;
    counter_ = 0;
    ASSERT_OK();
    return S_ERR_OK;
}

template <typename data_T>
bool Stack<data_T>::Ok() const
{
    return counter_ >= 0 && counter_ <= capacity_ && capacity_ > 0;
}

template <typename data_T>
void Stack<data_T>::DumpElem(size_t cnt) const
{
    printf("\tUnknown type\n");
}

/*________ Partial specialization _______*/
template <>
void Stack<int>::DumpElem(size_t cnt) const
{ 
    printf("\t[%zu] = %i (int)\n", cnt, data_[cnt]);
}
 
template <>
void Stack<unsigned>::DumpElem(size_t cnt) const
{ 
    printf("\t[%zu] = %u (unsigned)\n", cnt, data_[cnt]);
}

template <>
void Stack<size_t>::DumpElem(size_t cnt) const
{ 
    printf("\t[%zu] = %zu (size_t)\n", cnt, data_[cnt]);
}

template <>
void Stack<long>::DumpElem(size_t cnt) const
{ 
    printf("\t[%zu] = %ld (long)\n", cnt, data_[cnt]);
}

template <>
void Stack<double>::DumpElem(size_t cnt) const
{ 
    printf("\t[%zu] = %lg (double)\n", cnt, data_[cnt]);
}

template <>
void Stack<char>::DumpElem(size_t cnt) const
{ 
    printf("\t[%zu] = %c (char)\n", cnt, data_[cnt]);
}
/*_______________________________________*/

template <typename data_T>
void Stack<data_T>::Dump() const
{
    printf("Stack [%p] %s \n{\n    Capacity: %zu\n" 
       "    Counter:  %zu\n    Data [%zu] [%p] = {\n", 
        this, (Ok())? "ok": "ERROR", capacity_, counter_, capacity_, data_);
    
    for (size_t i = 0; i < capacity_; i++)
        DumpElem(i);
    
    printf("    }\n}\n");
}

#endif
