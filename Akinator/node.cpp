#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include "node.hpp"

Node::Node (Node* par, char* data):
    data_  (data),
    left   (NULL),
    right  (NULL),
    parent (par)
{}

Node::~Node ()
{
    left = right = parent = NULL;
    delete [] data_;
}

void Node::recDestructor ()
{
    if (left)   left->recDestructor ();
    if (right) right->recDestructor ();

    delete this;
}

void Node::printTree (FILE* output)
{
    assert (output);

    fprintf (output, "(%s", data_);

    if (left)   left->printTree (output);
    else fprintf (output, "()");

    if (right) right->printTree (output);
    else fprintf (output, "()");

    fprintf (output, ")");
}

bool Node::isLeftNode (Node* curNode)
{
    assert (curNode->parent);
    return (curNode == curNode->parent->left);
}

Node* buildTreeRec (char* Buffer, Node* curParent)
{
    static int counter = 0;

    if (Buffer [counter + 1] == ')')
    {
        counter += 2;
        return NULL;
    }

    int len = -1;
    counter ++;

    sscanf (&Buffer[counter], "%*[^(]%n", &len);
    assert (len != -1); /* if */

    char* data = new char [len + 1];

    strncpy (data, Buffer + counter, (size_t) len);
    data [len] = '\0';

    counter += len;

    Node* newNode  = new Node     (curParent, data);
    newNode->left  = buildTreeRec (Buffer, newNode);
    newNode->right = buildTreeRec (Buffer, newNode);
    counter++;

    return newNode;
}
