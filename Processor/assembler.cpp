#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <cctype>
#include "assembler.hpp"

//This function is used in RCPU
long int FileLength (FILE* stream)
{
    assert (stream);
    fseek(stream, 0, SEEK_END);
    long int fileSize = ftell(stream);
    rewind (stream);
    return fileSize;
}


//This function is used in RCPU
int GetCmdArgQt (ASM_CMDS cmd)
{
#define CPU_CMDS(cmd_name, arg_qt)    \
if (cmd == ASM_##cmd_name)            \
    return arg_qt;

#include "Commands"
#undef CPU_CMDS

    return -1;
}

Assembler::Assembler ():
    fileSize_    (0),
    cmdsNum_     (0),
    inputFile_   (NULL),
    outputFile_  (NULL)
{
    memset (OldBuff_,      0, SIZE_OF_BUFF    * sizeof(char));
    memset (NewBuff_,      0, SIZE_OF_BUFF     * sizeof(int));
    memset (labelsArray_, -1, NUMBER_OF_LABELS * sizeof(int));
}


Assembler::~Assembler () {}


void Assembler::FromFileToArray ()
{
    size_t charQt_ = 
        fread (OldBuff_, sizeof(char), fileSize_, inputFile_);
    assert (charQt_ == fileSize_);
    OldBuff_ [fileSize_] = '\0';
    PRINT("\nSymbols in input file: %zu\n\n", fileSize_);
}


void Assembler::RecognizeLabels ()
{
    //For labels recognition
    int stringNum = 0;
    int label     = 0;

    //Counting strings
    for (size_t j = 0; j < fileSize_; j++)
    {
        if (OldBuff_[j] == '\n') stringNum++;
    }
    PRINT ("stringNum = %d\n", stringNum);

    char command [SIZE_OF_WORD] = {};
    int cmdCnt  = 0;
    int strSize = -1;
    int index   = 0;
    int lineCnt = 0;

    while (lineCnt < stringNum)
    {
        int cmdIndicator = -1;
        sscanf (OldBuff_ + index, "%s%n", command, &cmdIndicator);
        sscanf (OldBuff_ + index, "%*[^\n]%n", &strSize);
        index += strSize + 1;

        if (cmdIndicator != -1)
        {
            if (!(GetNumFromName (command) == ASM_DEFAULT))
                cmdCnt++;
        }

        if (OldBuff_[index] == ':')
        {
            if (!isdigit (OldBuff_ [index+1]))
            {
                printf ("ERROR! Wrong label.\n");
                printf ("%c in line %d is not a label.\n",
                    OldBuff_ [index+1], stringNum); exit(0);
            }

            else
            {
                label = (int) OldBuff_ [index+1];
                if (labelsArray_[label - '0'] != -1)
                {
                    printf ("ERROR! This label was used before.\n");
                    exit(0);
                }
                else
                {
                    labelsArray_ [label - '0'] = cmdCnt;
                    PRINT("Label - %d\n", cmdCnt);
                }
            }
        }
        lineCnt ++;
    }

    PRINT("cmdCnt = %d\n", cmdCnt);
    PRINT("Labels: \n");

    for (int i = 0; i < NUMBER_OF_LABELS; i++)
    {
        PRINT("%d ", labelsArray_ [i]);
    }
}


void Assembler::FirstPassing ()
{
    //For deleting comments
    ptrdiff_t i = 0;

    //For deleting labels
    ptrdiff_t c = 0;

    while (true)
    {
        //Delete comments
        char* commentStartPtr = strchr (OldBuff_ + i, ';');
        char* commentEndPtr   = strchr (OldBuff_ + i, '\n');

        for (int j = 0; commentStartPtr && 
                (j < commentEndPtr - commentStartPtr); j++)
        {
            commentStartPtr[j] = ' ';
        }

        //Delete labels
        char* labelStartPtr = strchr (OldBuff_ + c, ':');
        char* labelEndPtr   = strchr (OldBuff_ + c, '\n');

        for (int j = 0; labelStartPtr && 
                (j < labelEndPtr - labelStartPtr); j++)
        {
            labelStartPtr[j] = ' ';
        }

        //Jump to next line
        char* temp = strchr(OldBuff_ + i, '\n');
        if (!temp) break;
        i = temp - OldBuff_ + 1;
        c = i;
    }
   PRINT("\n\nOldBuff:\n%s\n\n", OldBuff_);
}


ASM_CMDS Assembler::GetNumFromName(const char* word)
{
#define CPU_CMDS(cmd_name, arg_qt)         \
    if (!strcasecmp (#cmd_name, word))     \
        return ASM_##cmd_name;

#include "Commands"

#undef CPU_CMDS

    return ASM_DEFAULT;
}


void Assembler::FromCharArrayToIntArray ()
{
    char word_ [SIZE_OF_WORD] = {}; 
    size_t i         = 0;
    int wordSize     = -1;
    char* OldBuffPtr = OldBuff_;

    while (*OldBuffPtr != '\0')
    {
        sscanf (OldBuffPtr, "%[a-zA-Z0-9_] %n", word_, &wordSize);
        OldBuffPtr += wordSize;
        PRINT("\nCommand name:   %s\n", word_);

        ASM_CMDS cmd_ = GetNumFromName (word_);
        if (cmd_ == ASM_DEFAULT)
        {
            printf ("\nERROR! %s is not a command\n", word_);
            exit(0);
        }

        NewBuff_[i++] = cmd_;
        PRINT("Command number: %d \n", cmd_);

        int argQt = GetCmdArgQt (cmd_);
        for (int argCnt = 0; argCnt < argQt; argCnt++)
        {
            int argSize = -1;

            if   ( (!isdigit(*OldBuffPtr))
                   && (*OldBuffPtr != 'R')
                   && (*OldBuffPtr != ':')
                   && (*OldBuffPtr != '-'))
            {
                printf ("*OldBuffPtr = %c\n", *OldBuffPtr);
                printf ("ERROR! Wrong argument\n");
                exit (0);
            }

            if (*OldBuffPtr == 'R' || *OldBuffPtr == ':')
                OldBuffPtr++;

            int argValue = -1;
            sscanf (OldBuffPtr, "%d %n", &argValue, &argSize);

            bool isLabel = (cmd_ >= ASM_JMP) 
                && (cmd_ <= ASM_RET) && (argCnt == 0);

            NewBuff_[i] = isLabel ?
                labelsArray_[argValue] : argValue;

            OldBuffPtr += argSize;

            PRINT("Argument: %d\n", NewBuff_[i]);
            i++;
        }
    }
    cmdsNum_ = i;
}


void Assembler::WriteToFile ()
{
    for (unsigned i = 0; i < cmdsNum_; i++)
    {
        fprintf (outputFile_, "%d ", NewBuff_[i]);
    }
}


void Assembler::Assemble (FILE* inputFile, FILE* outputFile)
{
    inputFile_    =  inputFile;
    outputFile_   = outputFile;

    fileSize_ = FileLength (inputFile_);
    FromFileToArray         ();
    RecognizeLabels         ();
    FirstPassing            ();
    FromCharArrayToIntArray ();
    WriteToFile             ();
}
