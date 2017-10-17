#include <stdio.h>

int r1 = 5;
int r2 = 0;
int r3 = 1;

void factorial ()
{
    if (r1 > 1)
    {
        r1 = r1 - 1;
        r2 = r1 * r2;
        factorial ();
    }
}

int main () 
{
    r2 = r1; // = 5
    factorial ();
    printf ("%d\n", r9);
    return 0;
}



/*
IN R1 5
IN R3 -1
INREG R2 R1
CALL 2
JE 4 R1 1
:2
ADDREG R1 R3 R1
MULREG R1 R2 R2 
RET
:4
*/

