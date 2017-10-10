#ifndef RCPU_HPP
#define RCPU_HPP

#include <cstdio>
#include "superHeader.hpp"
#include "StackForRCPU.hpp"

class Processor
{

private:

    size_t ReadDataInBuffFromFile (FILE* stream);
    class Stack CStack;
    class Stack callStack;

    static const size_t NUMBER_OF_ARGS = 3;
    static const size_t stackCapacity  = 16;
    static const size_t NUMBER_OF_REGS = 16;

    int Buff_           [SIZE_OF_BUFF];
    int Args_           [NUMBER_OF_ARGS];
    int Registers_      [NUMBER_OF_REGS];
    int instructionPtr_;
    int sizeOfCmdBuff_;

public:

    Processor(FILE* stream);
    ~Processor();
    int Execute ();

#define CPU_CMDS(cmdName, argQt) \
    int cmdName ();

#include "Commands"

#undef CPU_CMDS
};

#endif
