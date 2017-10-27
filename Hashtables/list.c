#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "list.h"

List* Constructor ()
{
    List* tmp = (List*) calloc (1, sizeof (List));
    tmp->size = 0;
    tmp->head = NULL;
    tmp->tail = NULL;

    return tmp;
}

void Destructor (List* list)
{
    Node* tmp = list->head;
    Node* next = NULL;

    while (tmp) 
    {
        next = tmp->next;
        free (tmp);
        tmp = next;
    }

    free (list);
    list = NULL;
}

void PushFront (List* list, int data)
{
    assert (list);

    Node* new_elem = (Node*) calloc (1, sizeof (Node));
    assert (new_elem);
   
    new_elem->value = data;
    /* new_elem is new head */
    new_elem->next = list->head;
    /* new_elem is the first */
    new_elem->prev = NULL;
  
    /* "old" head is 2nd element now */
    if  (list->head) {
        list->head->prev = new_elem;
    }
    
    list->head = new_elem;
   
    /* if list is empty */
    if (!list->tail) {
        list->tail = new_elem;
    }
    list->size++;
}

int PopFront (List* list)
{
    assert (list);
    assert (list->head);
    
    Node* del_elem = list->head;
    /* change head pointer */
    list->head = list->head->next;

    if (list->head) {
        list->head->prev = NULL;
    } 

    /* if list contains only 1 element */
    if (del_elem == list->tail) {
        list->tail = NULL;
    }

    int val = del_elem->value;
    free (del_elem);
   
    list->size--;
    return val;
}

void PushBack (List* list, int data)
{
    assert (list);

    Node* new_elem = (Node*) calloc (1, sizeof (Node));
    assert (new_elem);
   
    new_elem->value = data;
    /* new_elem is the last */
    new_elem->next = NULL;
    /* new_elem is new tail */
    new_elem->prev = list->tail;
  
    /* "old" tail is penultimate element now */
    if  (list->tail) {
        list->tail->next = new_elem;
    }

    list->tail = new_elem;
    
    /* if list is empty */
    if (list->head == NULL) {
        list->head = new_elem;
    }
    list->size++;
}


int PopBack (List* list)
{
    assert (list);
    assert (list->tail);
    
    Node* del_elem = list->tail;
    /* change tail pointer */
    list->tail = list->tail->prev;

    if (list->tail) {
        list->tail->next = NULL;
    } 

    /* if list contains only 1 element */
    if (del_elem == list->head) {
        list->head = NULL;
    }

    int val = del_elem->value;
    free (del_elem);
   
    list->size--;
    return val;
}

Node* GetNumElem (List* list, size_t num) 
{
    assert (list);
    assert (num < list->size);
    
    Node* cur_elem = list->head;
    
    for (size_t cnt = 0; cnt < num; cnt++) {
        cur_elem = cur_elem->next;
    }

    return cur_elem;
}

/* new element is pushed AFTER num's element */
void PushNumElem (List* list, size_t num, int value)
{
    assert (list);

    Node* cur_elem = GetNumElem (list, num);
    assert (cur_elem);

    Node* new_elem = (Node*) calloc (1, sizeof (Node));
    new_elem->value = value;
    new_elem->prev = cur_elem;
    new_elem->next = cur_elem->next;
    
    if (cur_elem->next) {
        cur_elem->next->prev = new_elem;
    }
    cur_elem->next = new_elem;

    if (!cur_elem->prev) {
        list->head = cur_elem;
    }
    if (!cur_elem->next) {
        list->tail = cur_elem;
    }
    list->size++;
}

/* element AFTER num's element is removed */
int PopNumElem (List* list, size_t num)
{
    assert (list);
   
    Node* del_elem = GetNumElem (list, num);
    assert (del_elem);

    if (del_elem->prev) {
        del_elem->prev->next = del_elem->next;
    }
    if (del_elem->next) {
        del_elem->next->prev = del_elem-> prev;
    }
    
    int val = del_elem->value;

    if (!del_elem->prev) {
        list->head = del_elem->next;
    }
    if (!del_elem->next) {
        list->tail = del_elem->prev;
    }

    free (del_elem);
    list->size--;
    return val;
}

void ListDump (List* list)
{
    assert (list);

    FILE* file_ptr = fopen ("./Dump/list_dump.gv", "w");
    assert (file_ptr);

    fprintf (file_ptr, "digraph graf {\n");
    NodeDump (list->head, file_ptr, list->size);
    fprintf (file_ptr, "}");

    fclose (file_ptr);

    system ("dot ./Dump/list_dump.gv -Tpng -o ./Dump/list_dump.png");
    system ("xdot ./Dump/list_dump.gv");
}

void NodeDump (Node* node, FILE* file, size_t list_size)
{
    assert (node);
    assert (file);
   
    fprintf (file, "Node_%p [label=\"", node);
   
    if (!node->prev) { 
        fprintf (file, "• HEAD •\n");
    }
    if (!node->next) {
        fprintf (file, "• TAIL •\n");
    }

#ifdef FULL_DUMP
    fprintf (file, "Node: [%p]\\l"
                   "Prev: [%p]\\l"
                   "Next: [%p]\\l"
                   "Size: %zu \\l",
                    node, node->prev, node->next, list_size);
#endif
    
    fprintf (file, "Data: %d\\l \"]\n", node->value);

    if (node->prev) {
        fprintf (file, "Node_%p->Node_%p\n", node, node->prev);
    }
    
    if (node->next) {
        fprintf (file, "Node_%p->Node_%p\n", node, node->next);
        NodeDump (node->next, file, list_size);
    }
}
