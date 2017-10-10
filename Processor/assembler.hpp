#ifndef ASM_HPP
#define ASM_HPP

#include "superHeader.hpp"

class Assembler
{

private:
    size_t FromFileToArray           ();
    int RecognizeLabels              ();
    void FirstPassing                ();
    ASM_CMDS GetNumFromName (const char* word);
    size_t FromCharArrayToIntArray   ();
    void FromArrayToFile             ();

    FILE* inputFile_;
    FILE* outputFile_;

    char OldBuff_        [SIZE_OF_BUFF];
    int  NewBuff_        [SIZE_OF_BUFF];
    int labelsArray_ [NUMBER_OF_LABELS];
    size_t charQt_;       //сколько считал из файла в массив
    size_t fileSize_;     //размер исходного файла
    size_t wordsQt_;
    ASM_CMDS cmd_;

public:
     void Assemble (FILE* inputFile, FILE* outputFile);
     Assembler  ();
     ~Assembler ();
};

long int FileLength (FILE* stream);
int GetCmdArgQt (ASM_CMDS cmd);

#endif
