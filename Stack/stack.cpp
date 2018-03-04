#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include "stack.h"

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
        data[i] = POISON;
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
    counter = 0;
    ASSERT_OK();
}

template <typename data_T>
bool Stack<data_T>::Ok() const
{
    return this && data &&
        capacity > 0 && 
	    counter < capacity;
}

template <typename data_T>
void Stack<data_T>::Dump ()
{
    printf("Stack [%p] ", this);
    printf("%s \n", (Ok ())? "ok": "ERROR");
    printf("{\n");
    printf("    Capacity: %zu \n", capacity);
    printf("    Counter:  %zu \n", counter);
    printf("    Data [%zu] [%p] = {\n", capacity, data);
    for (size_t i = 0; i < capacity; i++) {
        std::cout << "\t[" << i << "] = " << data[i];
        printf("%s\n", (data[i] == POISON)? " <=> POISON" : "");
    }
    printf("    }\n}\n");
}
