#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

//#define PRINT(...) printf (__VA_ARGS__)
#define PRINT(...)

typedef struct 
{
	char* buffer;
	char** strings;
	size_t file_size;
	size_t str_amount;
} Text;

char*  ReadData     (FILE* source);
char** GetStrPtrs   (char* buffer, int str_amount);
int    CountStrings (char* buffer);

int main (int argc, char* argv [])
{
	assert (argc == 2);
	
	Text text = {};
	
	FILE* input = fopen (argv [1], "r");
	assert (input);
	
	text.buffer = ReadData (input);
	assert (text.buffer);
	PRINT ("\n%s\n", text.buffer);

	text.str_amount = CountStrings (text.buffer); 
	PRINT ("Number of lines: %zu \n", text.str_amount);

	text.strings = GetStrPtrs (text.buffer, text.str_amount);
	assert (text.strings);
	PRINT ("\nfirst string: %s\n", text.strings [0]);
	PRINT ("third string: %s\n", text.strings [2]);
	
	fclose (input);

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

int CountStrings (char* buffer)
{
	assert (buffer);
	
	int str_cnt = 0;
	int i = 0;
	while (buffer [i] != '\0')
	{
		if (buffer [i] == '\n') str_cnt ++;
		i++;
	}
	return str_cnt;
}

char** GetStrPtrs (char* buffer, int str_amount)
{
	assert (buffer);

	int i = 0;
	int line = 1;
	
	char** lines_arr = new char* [str_amount + 1];
	lines_arr [0] = buffer;
	lines_arr [str_amount] = NULL;

	while (buffer [i] != '\0')
	{
		if (buffer [i] == '\n')
		{
			lines_arr [line] = buffer + i + 1;
			buffer [i] = '\0';
			line++;
		}
		i++;
	}
	
	return lines_arr;
}
