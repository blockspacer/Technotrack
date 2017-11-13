#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include "node.hpp"

Node::Node (Node* parent, double data, Types type):
    data_   (data),
    type_   (type),
    left_   (NULL),
    right_  (NULL),
    parent_ (parent)
{}

Node::~Node () { left_ = right_ = parent_ = NULL; }

bool Node::isLeftNode (Node* curNode)
{
    assert (curNode->parent_);
    return (curNode == curNode->parent_->left_);
}

void Node::recDestructor ()
{
    if (left_)   left_->recDestructor ();
    if (right_) right_->recDestructor ();

    if (this) delete this;
}

bool Node::nodeCmp (Node* node, Types type, double data)
{
    if (!node) return false;
    return (node->type_ == type &&
         (int) node->data_ == (int) data)? true: false;
}

bool Node::nodeCmp (Node* node, Types type)
{
    if (!node) return false;
    return (node->type_ == type)? true: false;
}

Priority Node::getPriority (Node* node)
{
    if (node->nodeCmp(node, T_operation, O_add)) return P_add_sub;
    if (node->nodeCmp(node, T_operation, O_sub)) return P_add_sub;
    if (node->nodeCmp(node, T_operation, O_mul)) return P_mul_div;
    if (node->nodeCmp(node, T_operation, O_div)) return P_mul_div;
    if (node->nodeCmp(node, T_operation, O_Ln )) return P_Ln;
    return P_low;
}
