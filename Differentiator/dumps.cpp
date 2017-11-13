#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <unistd.h>
#include "diff.hpp"


void treeDump (Node* tree)
{
    assert (tree);
    static int fileNum = 0;

    char fileName [64] = {};
    sprintf (fileName, "./DotDumpPro/dumpfile%03d.gv", fileNum);

    FILE* ptrFile = fopen (fileName, "w");
    assert (ptrFile);

    fprintf (ptrFile, "digraph graf {\n");
    nodeDump (tree, ptrFile);
    fprintf (ptrFile, "}");
    fclose (ptrFile);

    char str [128] = {};
    sprintf (str, "dot ./DotDumpPro/dumpfile%03d.gv -Tpng -o "
        "./DotDumpPro/dumpfile%03d.png", fileNum, fileNum);
    system (str);

    char str2 [64] = {};
    sprintf (str2, "xdot ./DotDumpPro/dumpfile%03d.gv", fileNum);
    system (str2);

    fileNum++;
}

void nodeDump (Node* tree, FILE* ptrFile)
{
    assert (tree);
    assert (ptrFile);

    const int SIZE_OF_FUNC   = 8;
    char data [SIZE_OF_FUNC] = {};

    if (tree->type_ == T_value) { strcpy (data, "x"); }

    else if (tree->type_ == T_operation)
    {
        switch ((int) tree->data_)
        {
            case O_brL: { strcpy (data, "(") ; break; }
            case O_brR: { strcpy (data, ")") ; break; }
            case O_add: { strcpy (data, "+") ; break; }
            case O_sub: { strcpy (data, "-") ; break; }
            case O_mul: { strcpy (data, "*") ; break; }
            case O_div: { strcpy (data, "/") ; break; }
            case O_Ln:  { strcpy (data, "Ln"); break; }
            default : printf ("Unknown operation.\n");
                printf ("tree->data_ = %d \n", (int) tree->data_);
        }
    }

    fprintf (ptrFile, "treeNode_%p [label=\"", tree);
//===============================================================
//    fprintf (ptrFile, "[%p]\\l"
//                      "parent [%p]\\l"
//                      "left   [%p]\\l"
//                      "right  [%p]\\l",
//    tree, tree->parent_, tree->left_, tree->right_);
//===============================================================

    if (tree->type_ == T_constant)
        { fprintf (ptrFile, "%lg\\l\"]\n", tree->data_); }

    else { fprintf (ptrFile, "%s\\l\"]\n", data); }

    if (tree->left_)
    {
        fprintf  (ptrFile, "treeNode_%p->treeNode_%p\n",
                  tree,    tree->left_);
        nodeDump (tree->left_, ptrFile);
    }

    if (tree->right_)
    {
        fprintf  (ptrFile, "treeNode_%p->treeNode_%p\n",
                  tree,    tree->right_);
        nodeDump (tree->right_, ptrFile);
    }
}

void texDump (Node* oldTree, Node* newTree)
{
    assert (oldTree);
    assert (newTree);

    FILE* stream = fopen ("./TexDump/diff.tex", "w");
    assert (stream);

    fprintf (stream,
        "\\documentclass{article}\n"
        "\\usepackage[a4paper, margin=6mm]{geometry}\n"
        "\\usepackage{amsmath}\n"
        "\\title{Differentiator}\n"
        "\\begin{document}\n"
        "\\maketitle\n"

        "\\begin{eqnarray}\n"
        "\\left( ");

    texNodeDump (oldTree, stream);
    fprintf (stream, "\\right) ' = \n");
    texNodeDump (newTree, stream);

    fprintf (stream,
        "\\end{eqnarray}\n"
        "\\end{document}\n");
    fclose (stream);

    chdir  ("./TexDump");
    system ("pdflatex diff.tex");
    system ("evince diff.pdf");
    system ("mv diff.pdf ./../");
}

void texNodeDump (Node* node, FILE* stream)
{
    assert (stream);
    if (!node) return;

    if (node->nodeCmp (node, T_constant))
    {
        fprintf (stream, "{%lg}", node->data_);
    }

    else if (node->nodeCmp (node, T_value))
    {
        fprintf (stream, "{x}");
    }

    else if (node->nodeCmp (node, T_operation, O_add))
    {
        fprintf (stream, "{(");
        texNodeDump (node->left_ , stream);
        fprintf (stream, "}+{");
        texNodeDump (node->right_, stream);
        fprintf (stream, ")}");
    }

    else if (node->nodeCmp (node, T_operation, O_sub))
    {
        fprintf (stream, "{(");
        texNodeDump (node->left_ , stream);
        fprintf (stream, "}-{");
        texNodeDump (node->right_, stream);
        fprintf (stream, ")}");
    }

    else if (node->nodeCmp (node, T_operation, O_mul))
    {
        fprintf (stream, "{");
        texNodeDump (node->left_ , stream);
        fprintf (stream, "}*{");
        texNodeDump (node->right_, stream);
        fprintf (stream, "}");
    }

    else if (node->nodeCmp (node, T_operation, O_div))
    {
        fprintf (stream, "\\frac{");
        texNodeDump (node->left_, stream);
        fprintf (stream, "}{");
        texNodeDump (node->right_, stream);
        fprintf (stream, "}");
    }

    else if (node->nodeCmp (node, T_operation, O_Ln))
    {
        fprintf (stream, "Ln");
        fprintf (stream, "\\left(");
        texNodeDump (node->left_, stream);
        texNodeDump (node->right_, stream);
        fprintf (stream, "\\right)");
    }
}
