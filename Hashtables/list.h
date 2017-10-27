#ifndef LIST_H
#define LIST_H

#define FULL_DUMP

typedef struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct List {
    size_t size;
    Node* head;
    Node* tail;
} List;

List* Constructor ();
void  Destructor  (List* list);
void  PushFront   (List* list, int data);
int   PopFront    (List* list);
void  PushBack    (List* list, int data);
int   PopBack     (List* list);
Node* GetNumElem  (List* list, size_t num); 
void  PushNumElem (List* list, size_t num, int value);
int   PopNumElem  (List* list, size_t num);
void  ListDump    (List* list);
void  NodeDump    (Node* node, FILE* file, size_t list_size);

#endif
