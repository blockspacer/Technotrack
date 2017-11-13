#ifndef DIFF_HPP
#define DIFF_HPP

#include "node.hpp"

class Diff
{

public:

    Node* tree_;
    char* buffer;
    FILE* input_;

    Diff             (Node* tree);
    ~Diff            ();
    void reading     ();

    Node* deriviate  (Node* curNode, Node* parent);
    Node* d_add      (Node* curNode, Node* parent);
    Node* d_sub      (Node* curNode, Node* parent);
    Node* d_mul      (Node* curNode, Node* parent);
    Node* d_div      (Node* curNode, Node* parent);
    Node* d_Ln       (Node* curNode, Node* parent);
    Node* copyNode   (Node* curNode, Node* parent);
    bool simplify    (Node* curNode);
    void changeTree  (Node* node, Types type, double data);
};

    void treeDump    (Node* tree);
    void nodeDump    (Node* tree, FILE* ptrFile);
    void texDump     (Node* oldTree, Node* newTree);
    void texNodeDump (Node* tree, FILE* ptrFile);

#endif
