#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

//#define PRINT(...) printf (__VA_ARGS__)
#define PRINT(...)

typedef struct 
{
	char* string;
	size_t string_length;
} String;

char* ReadData (FILE* source);

int main (int argc, char* argv [])
{
	assert (argc == 2);
	
	FILE* input = fopen (argv [1], "r");
	assert (input);
	char* buffer = ReadData (input);
	assert (buffer);
	fclose (input);
	printf ("\n%s\n", buffer);

	return 0;
}

char* ReadData (FILE* source)
{
	assert (source);

	fseek (source, 0, SEEK_END);
        long file_size = ftell (source);
        rewind (source);

        char* buffer = new char [file_size + 1];
        size_t char_qt = fread (buffer,
                sizeof(char), (size_t) file_size, source);
        assert (char_qt == (size_t) file_size);
        buffer [file_size] = '\0';
	PRINT ("file_size = %d\n", (int) file_size);
 
	return buffer;
}

