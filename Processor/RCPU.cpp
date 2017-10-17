#include <cassert>
#include <cmath>
#include <cstdlib>
#include "RCPU.hpp"
#include "assembler.hpp"

Processor::Processor (FILE* stream):
        CStack    (stackCapacity),
        callStack (stackCapacity),
        Buff_            {},
        Args_            {},
        Registers_       {},
        instructionPtr_ (0),
        sizeOfCmdBuff_  (0)
{
    ReadDataInBuffFromFile (stream);
}


Processor::~Processor () {}


int Processor::NOP ()
{
    PRINT("~Nop~\n");
    return 0;
}


int Processor::PUSH ()
{
    assert(CStack.Ok ());
	PRINT("~Push~\n");
    CStack.Push (Args_[0]);
    PRINT("You've pushed %d.\n", Args_[0]);
    return 0;
}


int Processor::POP ()
{
    assert(CStack.Ok());
    PRINT("~Pop~\n");
    int result = CStack.Pop ();
    PRINT("You've popped %d. \n", result);
    return result;
}


#define ProcFunc(Function, condition)           \
    int Processor::Function ()                  \
    {                                           \
        assert(CStack.Ok ());                   \
        int val1   = CStack.Pop ();    	        \
        int val2   = CStack.Pop ();    	        \
        int result = val1 condition val2;       \
        PRINT("~%s~\n", #Function);             \
        PRINT("Value 1 - %d. \n", val1);        \
        PRINT("Value 2 - %d. \n", val2);        \
        PRINT("Result  - %d. \n", result);      \
        CStack.Push(result);                    \
        return result;                          \
        }

    ProcFunc(ADD, +)
    ProcFunc(SUB, -)
    ProcFunc(MUL, *)

#undef ProcFunc


int Processor::DIV ()
{
    int val1 = CStack.Pop ();
    int val2 = CStack.Pop ();

    PRINT("~Div~\n");
    PRINT("Value 1 - %d.\n", val1);
    PRINT("Value 2 - %d.\n", val2);

    if (val2 == 0)
    {
        PRINT("You cannot divide by zero!\n");
        exit(0);
    }

    else
    {
        int result = val1/val2;
        CStack.Push (result);
        PRINT("Result  - %d. \n", result);
        return result;
    }
}


int Processor::SQRT ()
{
    PRINT("~Sqrt~\n");
	int val = CStack.Pop();

    if (val < 0)
    {
        PRINT("Operation can't be executed! \n");
        exit (0);
    }

    else {
        PRINT("Result - %lg. \n", sqrt(val));
        CStack.Push (sqrt(val));
        return sqrt(val);
    }
}


int Processor::JMP () // improve
{
    int ip = 0;
    for (int i = 0; i < Args_[0]; i++)
    {
        ip += (GetCmdArgQt((ASM_CMDS)Buff_[ip]) + 1);
    }
    instructionPtr_ = ip;
    PRINT("~Jmp to %d~\n", instructionPtr_);
    return 0;
}


#define ProcFuncJmp(Function, condition)                         \
   int  Processor::Function ()                                   \
    {                                                            \
        PRINT("~%s~\n", #Function);                              \
        PRINT("Register  value - %d.\n", Registers_[Args_[1]]);  \
        PRINT("Condition value - %d.\n", Args_[2]);              \
        if (Registers_[Args_[1]] condition Args_[2])             \
            JMP ();                                              \
        return 0;                                                \
    }

    ProcFuncJmp(JGE, >=)
    ProcFuncJmp(JG,   >)
    ProcFuncJmp(JLE, <=)
    ProcFuncJmp(JL,   <)
    ProcFuncJmp(JE,  ==)
    ProcFuncJmp(JNE, !=)

#undef ProcFuncJmp


int Processor::IN ()
{
    PRINT("~In~\n");
    Registers_[Args_[0]] = Args_ [1];
    PRINT("You've pushed %d in register %d . \n",
           Args_ [1], Args_[0]);
    return 0;
}

int Processor::INREG ()
{
    PRINT("~InReg~\n");
    Registers_[Args_[0]] = Registers_[Args_[1]];
    PRINT("You've pushed value from R%d to R%d.\n",
           Args_[0], Args_[1]);
    return 0;
}

int Processor::OUT ()
{
    PRINT("~Out~\n");
    PRINT("Value in R%d - %d\n", Args_[0], Registers_[Args_[0]]);
    printf ("Result - %d\n", Registers_[Args_[0]]);
    return 0;
}


#define ProcFuncReg(Function, condition)    \
  int Processor::Function()                 \
  {                                         \
      int val1 = Registers_[Args_[0]];      \
      int val2 = Registers_[Args_[1]];      \
      int result = val1 condition val2;     \
      PRINT("~%s~\n", #Function);           \
      PRINT("Value 1 - %d. \n", val1);      \
      PRINT("Value 2 - %d. \n", val2);      \
      PRINT("Result  - %d. \n", result);    \
      Registers_[Args_[2]] = result;        \
      return result;                        \
  }

    ProcFuncReg(ADDREG, +)
    ProcFuncReg(SUBREG, -)
    ProcFuncReg(MULREG, *)

#undef ProcFuncReg


int Processor::DIVREG ()
{
    int val1 = Registers_[Args_[0]];
    int val2 = Registers_[Args_[1]];

    PRINT("~DivReg~\n");
    PRINT("Value 1 - %d. \n", val1);
    PRINT("Value 2 - %d. \n", val2);

    if (val2 == 0)
    {
        PRINT("You cannot divide by zero!\n");
        exit(0);
    }

    else
    {
        int result = val1 / val2;
        Registers_[Args_[2]] = result;
        PRINT("Result - %d. \n", result);
        return result;
    }
}


int Processor::SQRTREG ()
{
    PRINT("~SqrtReg~\n");
    int value = Registers_[Args_[0]];

    if (value < 0)
       {
           PRINT("Operation can't be executed! \n");
           exit (0);
       }

    else
       {
           PRINT("Result - %lg. \n", sqrt(value));
           Registers_[Args_[1]] = sqrt(value);
           return sqrt(value);
       }
}

int Processor::CALL ()
{
    assert (callStack.Ok ());
    PRINT("~Call~\n");
    callStack.Push (instructionPtr_);
    JMP ();
    //callStack.Dump ();
    return 0;
}

int Processor::RET ()
{
    assert (callStack.Ok ());
    PRINT("~Ret~\n");
    instructionPtr_ = callStack.Pop ();
    //callStack.Dump ();
    return 0;
}

int Processor::HLT ()
{
    PRINT("~Hlt~\n");
    instructionPtr_ = sizeOfCmdBuff_;
    return 0;
}


size_t Processor::ReadDataInBuffFromFile (FILE* stream)
{
    char CharBuff[SIZE_OF_BUFF] = {};
    int sizeOfCmd_ = 0;

    size_t fileSize = FileLength (stream);
    size_t charQt = fread (CharBuff, sizeof(char), fileSize, stream);
    assert (charQt == fileSize);
    CharBuff[fileSize] = '\0';

    PRINT("\nCharBuff: %s \n", CharBuff);

    int i = 0;
    int j = 0;
    while (CharBuff[i] != '\0')
    {
        sscanf (CharBuff + i, " %d %n", Buff_ + j, &sizeOfCmd_);
        i+= sizeOfCmd_;
        j++;
    }
        sizeOfCmdBuff_ = j;

    PRINT("Number of commands and agruments:  = %d\n", 
            sizeOfCmdBuff_);
    PRINT("CmdBuff_: ");
    for (int cnt = 0; cnt < sizeOfCmdBuff_; cnt++)
    {
        PRINT("%d ", Buff_[cnt]);
    }
    PRINT("\n\n");
    return sizeOfCmdBuff_;
}

int Processor::Execute ()
{
    while (instructionPtr_ < sizeOfCmdBuff_)
     {
         ASM_CMDS cmd = (ASM_CMDS) Buff_[instructionPtr_];

         PRINT("\n======| START CYCLE |======\n");
         PRINT("InstructionPtr = %d\n", instructionPtr_);
         PRINT("cmd = %d\n", (int) cmd);

         instructionPtr_++;
         size_t argQt = GetCmdArgQt (cmd);
         PRINT("argQt = %zu\n", argQt);
         for (size_t j = 0; j < argQt; j++)
         {
             Args_[j] = Buff_[instructionPtr_];
             instructionPtr_++;
         }

         if (argQt > 0)
         {
             PRINT("Arguments: ");
             for (size_t i = 0; i < argQt; i++)
             {
                 if (Args_[i] != 0)
                 {
                    PRINT(" %d ", Args_[i]);
                 }
             }
             PRINT("\n");
         }

         switch (cmd)
         {

#define CPU_CMDS(cmdName, argQt)                \
case ASM_##cmdName:                             \
{                                               \
    cmdName ();                                 \
                                                \
    PRINT("Registers: \n");                     \
    for (size_t i = 0; i < NUMBER_OF_REGS; i++) \
    {                                           \
        PRINT("%d ", Registers_[i]);            \
    }                                           \
                                                \
    PRINT("\n\n======| END CYCLE |======\n");   \
                                                \
}; break;

#include "Commands"

#undef CPU_CMDS

default:
{
    printf ("CPU_CMDS switch failed!\n");
    exit(0);
}; break;

         };
     }
return 0;
}
