#include <cstdio>
#include <cassert>
#include "RCPU.hpp"

int main ()
{
    FILE* binFile = fopen ("NewFile", "r");
    assert (binFile);

    Processor RCPU (binFile);
    RCPU.Execute ();

    fclose (binFile);

	return 0;
}
