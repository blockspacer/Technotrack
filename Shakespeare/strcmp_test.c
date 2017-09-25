#include <stdio.h>
#include <string.h>

int main ()
{
	char *a = "abc";
	char *b = "abc";
	char *c = "bde";
	printf ("comparing a vs b: %d\n", strcmp (a, b));
	printf ("comparing b vs c: %d\n", strcmp (b, c));	
	printf ("comparing c vs a: %d\n", strcmp (c, a));
	return 0;
}
