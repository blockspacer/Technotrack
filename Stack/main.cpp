#include "stack.hpp"
#include "vector.hpp"

void test_1()
{
    Stack <unsigned> stack_l(16);
    Stack <int>  stack_i(16);

    for (int i = 1; i < 17; i++)
        stack_l.Push(9*i);
    
    stack_l.Dump();

    unsigned val = 0;
    for (int i = 0; i < 9; i++) {
        stack_l.Pop(&val);
        stack_i.Push((int)val);
    }
   
    stack_i.Dump();
    stack_i.Clear();
    stack_i.Dump(); 
}

void copy_test()
{   
    Stack <int> st(8);
    for (int i = 1; i < 5; i++) 
        st.Push(i);
    st.Dump();

    Stack <int> copy(st);
    copy.Dump();
}

void vector_test()
{
    Vector<int> v(10);
    v[5] = 3;
    v.Dump();
}

int main(void)
{
    //vector_test();
    //test_1();
    copy_test();
    return 0;
}
