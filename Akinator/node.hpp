#ifndef NODE_HPP
#define NODE_HPP

class Node
{
public:
   
    char* data_;
    Node* left;
    Node* right;
    Node* parent;
 
    Node  (Node* par, char* data_);
    ~Node ();

    void recDestructor ();
    void printTree     (FILE* output);
    bool isLeftNode    (Node* tree);
};

Node* buildTreeRec (char* Buffer, Node* node);

#endif
