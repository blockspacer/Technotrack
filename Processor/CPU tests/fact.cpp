#include <stdio.h>

int main ()
{
    int val = -1;

    scanf ("%d", &val);

    int res = val;

    while (val != 1)
    {
        res *= (val - 1);
        val --;
    }

    printf ("%d\n", res);

    return 0;
}

/*
IN R0 5
IN R1 R0
JMP :8
:6
IN R2 -1
ADDREG R1 R2 R1
MULREG R0 R1 R0
:8
JNE R1 1 :6
*/

