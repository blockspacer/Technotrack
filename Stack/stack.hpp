#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "vector.hpp"

#define ASSERT_OK()                            \
    if (!Ok()) {                               \
        printf("ERROR DETECTED!\nFILE: %s, "   \
               "FUNCTION: %s, LINE: %d\n\n",   \
               __FILE__, __func__,  __LINE__); \
        Dump();                                \
        exit(EXIT_FAILURE);                    \
}

template <typename data_T>
class Stack
{
private:
    int counter_     = 0;
    /* counter_ shows the number of the first free cell */
    size_t capacity_ = 0;
    Vector <data_T> data_;
  
public:
    Stack      (size_t size);
    ~Stack     ();
    void Push  (data_T value);
    data_T Pop ();
    void Clear ();
    bool Ok    () const;
    void Dump  ();
    void DumpElem (size_t cnt);
};

template <typename data_T>
Stack<data_T>::Stack(size_t size):
    counter_  (0),
    capacity_ (size),
    data_     (capacity_) {}

template <typename data_T>
Stack<data_T>::~Stack() {}

template <typename data_T>
void Stack<data_T>::Push(data_T value)
{
    ASSERT_OK();
    counter_++;
    if (!Ok()) {
        counter_--;
        printf("Unable to push (full stack)\n");
        return;
    }
    data_[counter_-1] = value;
    ASSERT_OK();
}

template <typename data_T>
data_T Stack<data_T>::Pop()
{
    ASSERT_OK();
    counter_--;
    ASSERT_OK();
    data_T value = data_[counter_];
    data_[counter_] = 0;
    ASSERT_OK(); 
    return value; 
}

template <typename data_T>
void Stack<data_T>::Clear()
{
    ASSERT_OK();
    for (size_t i = 0; i < capacity_; i++)
        data_[i] = (data_T)0;
    counter_ = 0;
    ASSERT_OK();
}

template <typename data_T>
bool Stack<data_T>::Ok() const
{
    return counter_ >= 0 && counter_ <= capacity_;
}

template <typename data_T>
void Stack<data_T>::DumpElem(size_t cnt)
{
    printf("\tUnknown type\n");
}

/*________ Partial specialization _______*/
template <>
void Stack<int>::DumpElem(size_t cnt)
{ 
    printf("\t[%zu] = %i (int)\n", cnt, data_[cnt]);
}
 
template <>
void Stack<unsigned>::DumpElem(size_t cnt)
{ 
    printf("\t[%zu] = %u (unsigned)\n", cnt, data_[cnt]);
}

template <>
void Stack<size_t>::DumpElem(size_t cnt)
{ 
    printf("\t[%zu] = %zu (size_t)\n", cnt, data_[cnt]);
}

template <>
void Stack<long>::DumpElem(size_t cnt)
{ 
    printf("\t[%zu] = %ld (long)\n", cnt, data_[cnt]);
}

template <>
void Stack<double>::DumpElem(size_t cnt)
{ 
    printf("\t[%zu] = %lg (double)\n", cnt, data_[cnt]);
}

template <>
void Stack<char>::DumpElem(size_t cnt)
{ 
    printf("\t[%zu] = %c (char)\n", cnt, data_[cnt]);
}
/*_______________________________________*/

template <typename data_T>
void Stack<data_T>::Dump()
{
    printf("Stack [%p] %s \n{\n    Capacity: %zu\n" 
       "    Counter:  %d \n    Data [%zu] [%p] = {\n", 
        this, (Ok())? "ok": "ERROR", capacity_, counter_, capacity_, data_);
    
    for (size_t i = 0; i < capacity_; i++)
        DumpElem(i);
    
    printf("    }\n}\n");
}

#endif
