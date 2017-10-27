#include <stdio.h>
#include "list.h"

int main ()
{
    List* my_list = Constructor();

    PushFront (my_list, 10);
    PushFront (my_list, 20);
    PushFront (my_list, 30);
    PushBack (my_list, -234);
    PopFront (my_list);
    PopBack (my_list);
    PushFront (my_list, 70);
    PushFront (my_list, 80);
    PushFront (my_list, 90);
    ListDump (my_list);
    
    printf ("3: %d\n", PopNumElem (my_list, 3));
    ListDump (my_list);
    
    Destructor (my_list);
    
    return 0;
}
