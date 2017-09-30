#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>

//#define PRINT(...) printf (__VA_ARGS__)
#define PRINT(...)

const char* sort_res     = "./Result/sort";
const char* sort_res_inv = "./Result/sort_inv";

typedef struct 
{
	char* buffer;
	char** strings;
	size_t str_num;
} Text;

Text   MakeText      (const char* filename);
char*  ReadData      (FILE* source);
int    CountStrings  (char* buffer);
char** GetStrPtrs    (char* buffer, int str_num);
int    Comparator    (const void* arg1, const void* arg2);
int    ComparatorInv (const void* arg1, const void* arg2);
int    PrintText     (Text* text, const char* filename);

int main (int argc, char* argv [])
{
	assert (argc == 2);
	
	Text text = MakeText (argv [1]);
	
	qsort (text.strings, text.str_num, sizeof (*text.strings), Comparator);
	PrintText (&text, sort_res);
	
	qsort (text.strings, text.str_num, sizeof (*text.strings), ComparatorInv);
	PrintText (&text, sort_res_inv);

	return 0;
}

Text MakeText (const char* filename)
{
	assert (filename);
	
	Text text = {};

	FILE* input = fopen (filename, "r");
	assert (input);
	
	text.buffer = ReadData (input);
	assert (text.buffer);
	PRINT ("\n%s\n", text.buffer);

	text.str_num = CountStrings (text.buffer); 
	PRINT ("Number of lines: %zu \n\n", text.str_num);

	text.strings = GetStrPtrs (text.buffer, text.str_num);
	assert (text.strings);
	
	fclose (input);
	return text;
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
	PRINT ("File size: %d\n", (int) file_size);
 
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

char** GetStrPtrs (char* buffer, int str_num)
{
	assert (buffer);

	int i = 0;
	int line = 1;
	
	char** lines_arr = new char* [str_num + 1];
	lines_arr [0] = buffer;
	lines_arr [str_num] = NULL;

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

int Comparator (const void* arg1, const void* arg2)
{
	assert (arg1);
	assert (arg2);

	const char* str1 = *(const char**) arg1;
	const char* str2 = *(const char**) arg2;

	while (isspace (*str1) || ispunct (*str1)) str1++;
	while (isspace (*str2) || ispunct (*str2)) str2++;

	return strcmp (str1, str2);
}

int ComparatorInv (const void* arg1, const void* arg2)
{
	assert (arg1);
	assert (arg2);

	const char* str1 = *(char**) arg1;
	const char* str2 = *(char**) arg2;
	
	const char* end_line1 = str1 + strlen (str1) - 1;
	const char* end_line2 = str2 + strlen (str2) - 1;

	while (isspace (*end_line1) || ispunct (*end_line1)) end_line1--;
	while (isspace (*end_line2) || ispunct (*end_line2)) end_line2--;

	return strcmp (end_line1, end_line2);
}

int PrintText (Text* text, const char* filename)
{
	assert (text);
	assert (filename);

	FILE* output = fopen (filename, "w");
	assert (output);

	for (int i = 0; i < text->str_num; i++) 
	{
		fprintf (output, "%s\n", text->strings[i]);
	}

	fclose (output);
	return 0;
}
