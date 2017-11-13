#ifndef RECDESC_HPP
#define RECDESC_HPP

#include "diff.hpp"

//#define PRINT(...) printf (__VA_ARGS__)
#define PRINT(...)

class RecDescent
{
public:
    char* str;
    int   ptr;

     RecDescent ();
    ~RecDescent ();

    Node* GetN (Node* parent);
    Node* GetF (Node* parent);
    Node* GetP (Node* parent);
    Node* GetT (Node* parent);
    Node* GetE (Node* parent);
    Node* GetG (Node* parent);
};

#endif
