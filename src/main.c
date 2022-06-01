#include<stdio.h>
#include "cpu.h"

int main() {

    uint8_t program[] = {0xA9, 0x21, 0x0A, 0x29, 0x49, 0x02};
    size_t program_len = sizeof(program) / sizeof(program[0]);
    load_program(program, program_len);
    execute();

    display_cpu_regs();

    return 0;
}
