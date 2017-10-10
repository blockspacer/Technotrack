#include <cstdio>
#include <cassert>
#include "assembler.hpp"

int main ()
{
    FILE* inputFile = fopen ("OriginalFile", "r");
    assert (inputFile);

    FILE* outputFile = fopen ("NewFile", "w");
    assert (outputFile);

    Assembler MYASM;
    MYASM.Assemble (inputFile, outputFile);

    fclose (inputFile);
    fclose (outputFile);

    return 0;
}
