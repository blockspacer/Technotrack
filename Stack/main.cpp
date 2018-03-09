#include "stack.hpp"
#include "vector.hpp"

int main(void)
{
    Stack <long> stack_l(16);
    Stack <int>  stack_i(16);

    for (int i = 1; i < 17; i++)
        stack_l.Push(9*i);
    
    stack_l.Dump();

    for (int i = 0; i < 9; i++)
        stack_i.Push((int)stack_l.Pop());
   
    stack_i.Dump();
    stack_i.Clear();
    stack_i.Dump(); 
      
	return 0;
}
