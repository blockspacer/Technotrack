#ifndef NODE_HPP
#define NODE_HPP

enum Types
{
    T_constant,
    T_value,
    T_operation
};

enum Operations
{
    O_add,
    O_sub,
    O_mul,
    O_div,
    O_Ln,
    O_brL,
    O_brR
};

enum Priority
{
    P_low,
    P_add_sub,
    P_mul_div,
    P_Ln
};

class Node
{

public:

    double  data_;
    Types   type_;
    Node*   left_;
    Node*  right_;
    Node* parent_;

    Node                 (Node* parent, double data, Types type);
    ~Node                ();

    void recDestructor   ();
    bool isLeftNode      (Node* tree);
    bool nodeCmp         (Node* node, Types type);
    bool nodeCmp         (Node* node, Types type, double data);
    Priority getPriority (Node* node);
};

#endif
