#ifndef SUPER_HEADER_INCLUDED
#define SUPER_HEADER_INCLUDED

enum ASM_CMDS
{
#define CPU_CMDS(cmd_name, arg_qt) \
    ASM_##cmd_name,

#include "Commands"

#undef CPU_CMDS
    ASM_DEFAULT
};

enum
{
    SIZE_OF_BUFF     = 1024,
    SIZE_OF_WORD     = 16,
    POISON           = -666,
    NUMBER_OF_LABELS = 10,
};

//#define PRINT(...)  printf(__VA_ARGS__)
#define PRINT(...)

#endif
