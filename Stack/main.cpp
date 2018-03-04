#include <cstdio>
#include "stack.h"
#include "stack.cpp"

int main ()
{
	Stack <long> stack_t(16);
    
    for (int i = 0; i < 11; i++)
        stack_t.Push(9*i);
    stack_t.Push(34);
    stack_t.Push(12);
 	stack_t.Pop();
	stack_t.Dump();

	return 0;
}
