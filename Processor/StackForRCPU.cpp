#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cstring>
 
#include "superHeader.hpp"
#include "StackForRCPU.hpp"

Stack::Stack (size_t size):
    counter (0),
    capacity (size)
{
    data = new int [capacity];
    if (!data) exit (EXIT_FAILURE);
    
    for (size_t i = 0; i < capacity; i++)
    {
        data[i] = POISON;
    }
}

Stack::~Stack ()
{
    delete [] data;
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
    ASSERT_OK();
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
        capacity > 0 && 
	    counter < capacity;
}

void Stack::Dump () const
{
    printf ("Stack [%p] ", this);
    printf ("%s \n", (Ok ())? "ok": "ERROR");
    printf ("{\n");
    printf ("    Capacity: %zu \n", capacity);
    printf ("    Counter: %zu \n", counter);
    printf ("    Data [%zu] [%p] = {\n", capacity, data);
    for (size_t i = 0; i < capacity; i++)
    {
        printf ("\t[%zu] = %d %s\n", i,
        data[i], ((data[i] == POISON)? "<=> POISON" : " "));
    }
    printf ("    }\n}\n");
}
