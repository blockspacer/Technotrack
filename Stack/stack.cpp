#include <cstdlib>
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

template <typename data_t>
Stack<data_t>::~Stack()
{
    delete [] data;
}

template <typename data_t>
void Stack<data_t>::Push(data_t value)
{
    ASSERT_OK();
    data[counter++] = value;
    ASSERT_OK();
}

template <typename data_t>
data_t Stack<data_t>::Pop()
{
    ASSERT_OK();
    counter--;
    ASSERT_OK();
    data_t value = data[counter];
    data[counter] = POISON;
    ASSERT_OK(); 
    return value; 
}

template <typename data_t>
void Stack<data_t>::Clear ()
{
    ASSERT_OK();
    counter = 0;
    ASSERT_OK();
}

template <typename data_t>
bool Stack<data_t>::Ok() const
{
    return this && data &&
        capacity > 0 && 
	    counter < capacity;
}

template <typename data_t>
void Stack<data_t>::Dump ()
{
    printf("Stack [%p] ", this);
    printf("%s \n", (Ok ())? "ok": "ERROR");
    printf("{\n");
    printf("    Capacity: %zu \n", capacity);
    printf("    Counter: %zu \n", counter);
    printf("    Data [%zu] [%p] = {\n", capacity, data);
    for (size_t i = 0; i < capacity; i++)
    {
        printf("\t[%zu] = %d %s\n", i,
        data[i], ((data[i] == POISON)? "<=> POISON" : " "));
    }
    printf("    }\n");
    printf("}\n");
}
