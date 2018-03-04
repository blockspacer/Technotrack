#ifndef STACK_HPP
#define STACK_HPP

#define ASSERT_OK()                            \
    if (!Ok ()) {                              \
        printf("ERROR DETECTED!\nFILE: %s, "   \
               "FUNCTION: %s, LINE: %d\n\n",   \
               __FILE__, __func__,  __LINE__); \
        Dump();                                \
        exit(EXIT_FAILURE);                    \
}

const int POISON = -666;
/*
enum
{
    POISON = -666
};
*/

template <typename data_T>
class Stack
{
private:
    data_T* data;
    size_t counter;
    /* counter shows the number of the first free cell */
    size_t capacity;

public:
    Stack      (size_t size);
    ~Stack     ();
    void Push  (data_T value);
    data_T Pop      ();
    void Clear ();
    bool Ok    () const;
    void Dump  ();
};

#endif
