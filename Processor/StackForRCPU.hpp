#ifndef STACK_HPP
#define STACK_HPP

#define ASSERT_OK()                                     \
    if (!Ok ()) {                                       \
        printf ("ERROR DETECTED!\n");                   \
        printf ("FILE: %s, ", __FILE__);                \
        printf ("FUNCTION: %s, ", __PRETTY_FUNCTION__); \
        printf ("LINE: %d\n\n", __LINE__);              \
        Dump ();                                        \
        exit (EXIT_FAILURE);                            \
}

class Stack
{

private:
    int* data;
    size_t counter; // shows the number of the first free cell
    size_t capacity;

public:
    Stack (size_t size);
    ~Stack();
    void Push (int value);
    int Pop ();
    void Clear ();
    bool Ok () const;
    void Dump () const;

};

#endif
