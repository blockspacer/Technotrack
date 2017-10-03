#include <cstdio>

#include "stack.hpp"
//#include "stack.cpp"

int main ()
{
	Stack stack_t (16);

	for (int i = 0; i < 8; i++)
    {
        stack_t.Push (i);
    }
    //stack_t.Push (15);
    //stack_t.Push (-23);
	stack_t.Pop ();
	stack_t.Dump ();

	return 0;
}

