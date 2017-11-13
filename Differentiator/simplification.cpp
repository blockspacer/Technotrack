#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include "diff.hpp"


void Diff::changeTree (Node* node, Types type, double data)
{
    node->type_  = type;
    node->data_  = data;

    node->left_ ->recDestructor ();
    node->right_->recDestructor ();

    node->left_  = NULL;
    node->right_ = NULL;
}

bool Diff::simplify (Node* curNode)
{
    assert (curNode);
    double tempData = 0;
    double eps  = 0.001;
    Types tempType;

    if (curNode-> left_) { simplify (curNode->left_ ); }
    if (curNode->right_) { simplify (curNode->right_); }

//~~~~оптимизация узлов с константами~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (curNode->left_ && curNode->right_            &&
        tree_->nodeCmp (curNode, T_operation)        &&
        tree_->nodeCmp (curNode->left_ , T_constant) &&
        tree_->nodeCmp (curNode->right_, T_constant)  )
    {
        switch ((int) curNode->data_)
        {

#define LEFT_DATA  (curNode->left_->data_)
#define RIGHT_DATA (curNode->left_->data_)
            case O_add: tempData = LEFT_DATA + RIGHT_DATA; break;

            case O_sub: tempData =
            curNode->left_->data_ - curNode->right_->data_; break;

            case O_mul: tempData =
            curNode->left_->data_ * curNode->right_->data_; break;

            case O_div:
            assert (curNode->right_->data_ >= eps);
            tempData =
            curNode->left_->data_ / curNode->right_->data_; break;

            default: printf ("Unknown operation"); assert (0);
        }

        changeTree (curNode, T_constant, tempData);

        return true;
    }

//~~~~умножение на ноль (справа и слева)~~~~~~~~~~~~~~~~~~~~~~~~
    if ( curNode->left_ && curNode->right_                    &&
         tree_->nodeCmp (curNode,         T_operation, O_mul) &&
        (tree_->nodeCmp (curNode->left_,  T_constant,  0)     ||
         tree_->nodeCmp (curNode->right_, T_constant,  0))     )
    {
        changeTree (curNode, T_constant, 0);

        return true;
    }

//~~~~умножение X на единицу слева~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if ( curNode->left_ && curNode->right_                    &&
         tree_->nodeCmp (curNode,         T_operation, O_mul) &&
         tree_->nodeCmp (curNode->left_,  T_constant,      1) &&
       !(tree_->nodeCmp (curNode->right_, T_operation))        )
    {
        tempData = curNode->right_->data_;
        tempType = curNode->right_->type_;

        changeTree (curNode, tempType, tempData);

        return true;
    }

//~~~~умножение X на единицу справа~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if ( curNode->left_ && curNode->right_                    &&
         tree_->nodeCmp (curNode,         T_operation, O_mul) &&
         tree_->nodeCmp (curNode->right_, T_constant,      1) &&
       !(tree_->nodeCmp (curNode->left_ , T_operation))         )
    {
        tempData = curNode->left_->data_;
        tempType = curNode->left_->type_;

        changeTree (curNode, tempType, tempData);

        return true;
    }

//~~~~сложение операции с нулём (0 справа)~~~~~~~~~~~~~~~~~~~~~~~~
    if ( curNode->left_ && curNode->right_               &&
         tree_->nodeCmp (curNode, T_operation, O_add)    &&
         tree_->nodeCmp (curNode->right_, T_constant, 0) &&
         tree_->nodeCmp (curNode->left_, T_operation)     )
    {
        (tree_->isLeftNode (curNode)) ?
        curNode->parent_->left_  = curNode->left_:
        curNode->parent_->right_ = curNode->left_;

        curNode->left_->parent_ = curNode->parent_;

        delete curNode->right_;
        delete curNode;

        return true;
    }

//~~~~умножение операции на единицу (1 слева)~~~~~~~~~~~~~~~~~~~~~
    if ( curNode->left_ && curNode->right_               &&
         tree_->nodeCmp (curNode, T_operation, O_mul)    &&
         tree_->nodeCmp (curNode->left_, T_constant, 1)  &&
         tree_->nodeCmp (curNode->right_, T_operation)     )
    {
        (tree_->isLeftNode (curNode))?
        curNode->parent_->left_  = curNode->right_:
        curNode->parent_->right_ = curNode->right_;

        curNode->right_->parent_ = curNode->parent_;

        delete curNode->left_;
        delete curNode;

        return true;
    }

//~~~~[ 1 / ( 1 / x ) = x ]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (curNode->left_ && curNode->right_                      &&
        tree_->nodeCmp (curNode, T_operation, O_div)           &&
        tree_->nodeCmp (curNode->left_, T_constant, 1)         &&
        tree_->nodeCmp (curNode->right_, T_operation, O_div)   &&
        tree_->nodeCmp (curNode->right_->left_, T_constant, 1) &&
        tree_->nodeCmp (curNode->right_->right_, T_operation)   )
    {
        (tree_->isLeftNode (curNode))?
        curNode->parent_->left_  = curNode->right_->right_:
        curNode->parent_->right_ = curNode->right_->right_;

        curNode->right_->right_->parent_ = curNode->parent_;

        delete curNode->right_->left_;
        delete curNode->right_;
        delete curNode->left_;
        delete curNode;

        return true;
    }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    return false;
}
