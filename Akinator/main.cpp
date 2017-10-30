#include <cstdio>
#include "akinator.hpp"
#include "node.hpp"

int main ()
{
    FILE* stream = fopen ("treeFile", "r+");
    if (!stream) {
        printf ("File cannot be opened.\n");
        return 0;
    }

    Akinator genius (stream);
    genius.menu ();

    fclose (stream);
    return 0;
}
