#include <cstdlib>
#include <cstdio>
#include <cassert>

#include "superHeader.hpp"
#include "StackForRCPU.hpp"

Stack::Stack (size_t capacity)
{
    this->data = new int[capacity];
    assert(data);
    for (size_t i = 0; i <= capacity; i++)
    {
        this->data[i] = POISON;
    }
    this->counter = 0;
    this->capacity = capacity;
}

Stack::~Stack ()
{
    delete[] this->data;
}

void Stack::Push (int value)
{
    assert (this->counter <= this->capacity);
    this->data [this->counter++] = value;
}

int Stack::Pop ()
{
    if (this->counter <= 0)
    {
        PRINT("Stack counter = %zu\n", counter);
        PRINT("You cannot pop from empty stack!\n");
        exit (0);
    }
    return this->data [--this->counter];
}

void Stack::Clear ()
{
    this->counter = 0;
}

bool Stack::Ok () const
{
    return ((data && capacity && counter < capacity) ||
	(!data && !capacity && !(counter < capacity)));
}

void Stack::Dump ()
{
    PRINT("Capacity: %zu \n", this->capacity);
    if (!this->counter)
    {
        PRINT("Empty stack\n");
    }
    else
    {
        PRINT("Current size: %zu \n", this->counter);
    }
    PRINT("Data address: %p \n", this->data);
    for (size_t i = 0; i <= capacity; i++)
    {
        PRINT("%c [%zu] = %d %s\n", ((i < counter)? '*' : ' '), i,
this->data[i], ((this->data[i] == POISON)? "<=> POISON" : " "));
    }
}
