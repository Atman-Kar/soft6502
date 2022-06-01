#ifndef _OPCODE_H
#define _OPCODE_H

#include "cpu.h"

typedef enum PROGRAM_FLAG{
    EXECUTION,
    EXIT_PROG,
    ILLEGAL_INSTRUCTION,
} PRG_FLAG;

int run(uint8_t opcode, struct cpu* CPU);
#endif // _OPCODE_H