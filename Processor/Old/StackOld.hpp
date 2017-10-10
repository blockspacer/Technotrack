#ifndef STACK_HPP
#define STACK_HPP

class Stack
{

private:
    int* data;
    size_t counter;
    size_t capacity;

public:
    Stack (size_t capacity);
    ~Stack();
    void Push (int value);
    int Pop ();
    void Clear ();
    bool Ok () const;
    void Dump ();

};

#endif
