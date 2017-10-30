#ifndef AKINATOR_HPP
#define AKINATOR_HPP

#include "node.hpp"

class Akinator
{
private:

    FILE* input_;
    Node* tree_;

public:

    char* Buffer;
    Akinator  (FILE* input);
    ~Akinator ();

    void fromFileToArray  ();
    void game             (Node* curNode);
    void addTeacher       (Node* curNode);
    void treeDump         (Node* tree);
    void nodeDump         (Node* tree, FILE* ptrFile);
    void menu             ();

    void description      ();
    Node* findTeacher     (Node* curNode, char* requiredTeacher);
    void printDescription (Node* node);
};

#endif
