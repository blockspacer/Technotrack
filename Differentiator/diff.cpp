#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include "diff.hpp"

Diff::Diff (Node* tree):
    tree_  (tree),
    buffer (NULL)
    {}


Diff::~Diff ()
{
    delete [] buffer;
}


Node* Diff::d_add (Node* curNode, Node* parent)
{
    Node* plus   = new Node  (parent, O_add, T_operation);
    plus->left_  = deriviate (curNode-> left_, plus);
    plus->right_ = deriviate (curNode->right_, plus);
    return plus;
}


Node* Diff::d_sub (Node* curNode, Node* parent)
{
    Node* minus   = new Node  (parent, O_sub, T_operation);
    minus->left_  = deriviate (curNode-> left_, minus);
    minus->right_ = deriviate (curNode->right_, minus);
    return minus;
}


Node* Diff::d_mul (Node* curNode, Node* parent)
{
    Node* plus   = new Node (parent, O_add, T_operation);
    plus->left_  = new Node (plus,   O_mul, T_operation);
    plus->right_ = new Node (plus,   O_mul, T_operation);

    plus->left_->left_  =
        deriviate (curNode-> left_, plus->left_);
    plus->left_->right_ = copyNode (curNode->right_, plus->left_);
    plus->right_->left_ = copyNode (curNode->left_, plus->right_);
    plus->right_->right_=
        deriviate (curNode->right_, plus->right_);

    return plus;
}


Node* Diff::d_div (Node* curNode, Node* parent)
{
    Node* div         = new Node (parent,     O_div, T_operation);
    div->left_        = new Node (div,        O_sub, T_operation);
    div->right_       = new Node (div,        O_mul, T_operation);
    div->left_->left_ = new Node (div->left_, O_mul, T_operation);
    div->left_->right_ = new Node(div->left_, O_mul, T_operation);

    div->left_->left_->left_   =
        deriviate (curNode->left_, div->left_->left_);
    div->left_->left_->right_  =
        copyNode (curNode->right_, div->left_->left_);

    div->left_->right_->left_  =
        copyNode (curNode->left_, div->left_->right_);
    div->left_->right_->right_ =
        deriviate (curNode->right_, div->left_->right_);

    div->right_->left_  = copyNode (curNode->right_, div->right_);
    div->right_->right_ = copyNode (curNode->right_, div->right_);

    return div;
}


Node* Diff::d_Ln (Node* curNode, Node* parent)
{
    Node* mul  = new Node  (parent, O_mul, T_operation);
    mul->left_ = new Node  (mul,    O_div, T_operation);

    mul->left_->left_  = new Node (mul->left_, 1, T_constant);
    mul->left_->right_ = copyNode (curNode->left_, mul->left_);

    mul->right_ = deriviate (curNode->left_, mul);

    return mul;
}


Node* Diff::copyNode (Node* curNode, Node* parent)
{
    if (!curNode) return NULL;

    Node* cpNode =
        new Node (parent, curNode->data_, curNode->type_);

    cpNode->left_  = copyNode (curNode->left_ , cpNode);
    cpNode->right_ = copyNode (curNode->right_, cpNode);

    return cpNode;
}


Node* Diff::deriviate (Node* curNode, Node* parent)
{
    assert (curNode);

    switch (curNode->type_)
    {
        case T_constant:
        {
            Node* constant = new Node (parent, 0, T_constant);
            return constant; break;
        }


        case T_value:
        {
            Node* value = new Node (parent, 1, T_constant);
            return value; break;
        }

        case T_operation:
        {
            switch ((int) curNode->data_)
            {
                case O_add:
                    { return d_add (curNode, parent); break; }

                case O_sub:
                    { return d_sub (curNode, parent); break; }

                case O_mul:
                    { return d_mul (curNode, parent); break; }

                case O_div:
                    { return d_div (curNode, parent); break; }

                case O_Ln:
                    { return d_Ln  (curNode, parent); break; }

                default: printf ("Error! Unknown operation.\n");
                    printf ("curNode->data_ = %d \n",
                    (int) curNode->data_);
            }

        }break;

        default: printf ("Error! Unknown type.\n");
    }
    assert (0);
    return NULL;
}
