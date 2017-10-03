#include <cstdlib>
#include <cstdio>
#include <cassert>

#include "stack.hpp"

Stack::Stack (size_t size):
    counter (0),
    capacity (size)
{
    data = new int [capacity];
    assert (data);
    
    for (size_t i = 0; i <= capacity; i++)
    {
        data[i] = POISON;
    }
    ASSERT_OK();
}

Stack::~Stack ()
{
    delete[] data;
}

void Stack::Push (int value)
{
    ASSERT_OK();
    data [counter] = value;
    counter++;
    ASSERT_OK();
}

int Stack::Pop ()
{
    ASSERT_OK();
    counter --;
    int value = data [counter];
    data [counter] = POISON;
    ASSERT_OK(); 
    return value; 
}

void Stack::Clear ()
{
    ASSERT_OK();
    counter = 0;
    ASSERT_OK();
}

bool Stack::Ok () const
{
    return this && 
	    data && 
        //capacity >= 0 && 
	    //counter >=0  &&
	    counter <= capacity + 1;
}

void Stack::Dump ()
{
    PRINT("Stack [%p] ", this);
    PRINT("%s \n", (Ok ())? "ok": "ERROR");
    PRINT("Capacity: %zu \n", capacity);
    PRINT("Counter: %zu \n", counter);
    PRINT("Data [%p] \n", data);
    for (size_t i = 0; i <= capacity; i++)
    {
        PRINT("\t*[%zu] = %d %s\n", i,
        data[i], ((data[i] == POISON)? "<=> POISON" : " "));
    }
}
