#include <cstdio>
#include <cstdlib>
#include "rec_desc.hpp"

int main ()
{
    RecDescent TreeBuilder;
    Node* oldTree = TreeBuilder.GetG (NULL);

    Diff wolfram (oldTree);
    Node* diffTree = wolfram.deriviate (oldTree, NULL);
    
    wolfram.simplify (diffTree);

    treeDump (oldTree);
    treeDump (diffTree);

    texDump (oldTree, diffTree);

    oldTree ->recDestructor ();
    diffTree->recDestructor ();

    return 0;
}
