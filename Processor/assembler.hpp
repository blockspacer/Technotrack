#ifndef ASM_HPP
#define ASM_HPP

#include "superHeader.hpp"

class Assembler
{

private:
    void FromFileToArray                    ();
    void RecognizeLabels                    ();
    void FirstPassing                       ();
    ASM_CMDS GetNumFromName (const char* word);
    void FromCharArrayToIntArray            ();
    void WriteToFile                        ();

    FILE* inputFile_;
    FILE* outputFile_;

    char OldBuff_        [SIZE_OF_BUFF];
    int  NewBuff_        [SIZE_OF_BUFF];
    int labelsArray_ [NUMBER_OF_LABELS];
    size_t fileSize_; 
    size_t cmdsNum_;

public:
     void Assemble (FILE* inputFile, FILE* outputFile);
     Assembler  ();
     ~Assembler ();
};
#endif
