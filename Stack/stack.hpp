#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <cstdio>

#define ASSERT_OK()                            \
    if (!Ok ()) {                              \
        printf("ERROR DETECTED!\nFILE: %s, "   \
               "FUNCTION: %s, LINE: %d\n\n",   \
               __FILE__, __func__,  __LINE__); \
        Dump();                                \
        exit(EXIT_FAILURE);                    \
}

const int POISON = -99;

template <typename data_T>
class Stack
{
private:
    data_T* data;
    size_t counter;
    /* counter shows the number of the first free cell */
    size_t capacity;

public:
    Stack      (size_t size);
    ~Stack     ();
    void Push  (data_T value);
    data_T Pop ();
    void Clear ();
    bool Ok    () const;
    void Dump  ();
};

template <typename data_T>
Stack<data_T>::Stack(size_t size):
    counter  (0),
    capacity (size)
{
    data = new data_T[capacity];
    if (!data) {
        printf("Cannot allocate memory!\n");
        exit(EXIT_FAILURE);
    }
    
    for (size_t i = 0; i < capacity; i++)
        data[i] = (data_T)POISON;
}

template <typename data_T>
Stack<data_T>::~Stack()
{
    delete [] data;
}

template <typename data_T>
void Stack<data_T>::Push(data_T value)
{
    ASSERT_OK();
    data[counter++] = value;
    ASSERT_OK();
}

template <typename data_T>
data_T Stack<data_T>::Pop()
{
    ASSERT_OK();
    data_T value = data[--counter];
    data[counter] = POISON;
    ASSERT_OK(); 
    return value; 
}

template <typename data_T>
void Stack<data_T>::Clear()
{
    ASSERT_OK();
    for (size_t i = 0; i < capacity; i++)
        data[i] = (data_T)POISON;
    counter = 0;
    ASSERT_OK();
}

template <typename data_T>
bool Stack<data_T>::Ok() const
{
    return this && data && counter < capacity;
}

template <typename data_T>
void Stack<data_T>::Dump()
{
    printf("Stack [%p] %s \n{\n"
           "    Capacity: %zu\n" 
           "    Counter:  %zu\n"
           "    Data [%zu] [%p] = {\n", 
        this, (Ok ())? "ok": "ERROR", capacity, counter, capacity, data);
    
    for (size_t i = 0; i < capacity; i++) {
        std::cout << "\t[" << i << "] = " << data[i];
        printf("%s\n", (data[i] == POISON)? " (POISON)" : "");
    }
    printf("    }\n}\n");
}

#endif
