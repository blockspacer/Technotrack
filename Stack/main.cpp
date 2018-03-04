#include <cstdio>
#include "stack.h"
#include "stack.cpp"

int main ()
{
	Stack <int> stack_t(16);
    
    for (int i = 0; i < 10; i++)
        stack_t.Push(2*i);
    stack_t.Push(115);
    stack_t.Push(123);
 	stack_t.Pop();
	stack_t.Dump();

	return 0;
}
