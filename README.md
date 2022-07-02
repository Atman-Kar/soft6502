# MOS 6502 Emulator

**Warning** : The project is still under development. 

Welcome to MOS 6502 Emulator Dev. My goal is to get a software implementation 6502 running smoothly, and then deploy a tiny Operating System on the emulator to manage programs. I will be maintaining a small [blog](https://atman-kar.github.io/soft6502/) where I write about the project. This emulator will be completely implemented in C. 

## Files

Here are the list of files & directories in the project.

```
soft6501
│   README.md
│   Makefile    
│   NESDoc.pdf
|
└───src
│   │   cpu.c
│   │   cpu.h
│   │   main.c
│   │   opcodes.c
│   │   opcodes.h
│   │
│   └───test
│       │   unittest.c
│       │   unittest.h

```

[NESDoc.pdf](https://www.nesdev.com/NESDoc.pdf) is the source of inspiration for this project. 

## Running the Program

**Warning** : Currently does not accept ".S"/".bin" files as program arguments. Running procedure will change as dev continues. As of now, all the opcodes are not implemented, therefore some programs my crash with exit error "ILLEGAL_INSTRUCTION".

To load the program you want to execute, go to the src/main.c and input your opcodes into the program array as shown below.

```cpp
int main() {

    /* Program in words: 
    *    1. 0xA9 - Load Accumulator (Immediate Mode) with 0x21
    *    2. 0x0A - Arithmetic Shift Left Accumulator
    *    3. 0x29 - AND Accumulator and 0x49 back to Accumulator
    *    4. 0x02 - Undocumented Opcode, freeze CPU
    */

    uint8_t program[] = {0xA9, 0x21, 0x0A, 0x29, 0x49, 0x02};
    size_t program_len = sizeof(program) / sizeof(program[0]);

    /* Loads the program into the emulator and inits PC reg*/
    load_program(program, program_len);

    /* Start fetching and executing opcodes */
    execute();

    /* Display CPU info to stdout */
    display_cpu_regs();

    return 0;
}
```

Running the program, we see the expected output 0x49 & (0x21 << 1) = 0x40 stored in accumulator.

```bash
$ make build
$ ./main

###################################
PC : 8006
SP : ff
A  : 40
X  : 0
Y  : 0
P  : 0
###################################
```

## A running emulator! - Snake Game

[wkjagt](https://gist.github.com/wkjagt) has written a nice snake game program in 6502 assembly. The program is very well written and readable, do check it out. I disassembled the program and passed it as an input to my emulator like this: 

```cpp
#include<stdio.h>
#include<stdlib.h>
#include "cpu.h"
#include "string.h"

int main(int argc, char *argv[]) {

    uint16_t break_point = -1;
    if(argc > 1) {
        if(strcmp(argv[1],"-break")==0){
            break_point = (uint16_t) strtol(argv[2], NULL, 16);
            printf("Breakpoint set at : 0x%X\n",break_point); 
        }
    }
    // try to run snake program 
    uint8_t program[] = {0x20, 0x06, 0x06, 0x20, 0x38, 0x06, 0x20, 0x0d, 0x06, 0x20, 0x2a, 0x06, 0x60, 0xa9, 0x02, 0x85,
                            0x02, 0xa9, 0x04, 0x85, 0x03, 0xa9, 0x11, 0x85, 0x10, 0xa9, 0x10, 0x85, 0x12, 0xa9, 0x0f,
                            0x85, 0x14, 0xa9, 0x04, 0x85, 0x11, 0x85, 0x13, 0x85, 0x15, 0x60, 0xa5, 0xfe, 0x85, 0x00,
                            0xa5, 0xfe, 0x29, 0x03, 0x18, 0x69, 0x02, 0x85, 0x01, 0x60, 0x20, 0x4d, 0x06, 0x20, 0x8d,
                            0x06, 0x20, 0xc3, 0x06, 0x20, 0x19, 0x07, 0x20, 0x20, 0x07, 0x20, 0x2d, 0x07, 0x4c, 0x38,
                            0x06, 0xa5, 0xff, 0xc9, 0x77, 0xf0, 0x0d, 0xc9, 0x64, 0xf0, 0x14, 0xc9, 0x73, 0xf0, 0x1b,
                            0xc9, 0x61, 0xf0, 0x22, 0x60, 0xa9, 0x04, 0x24, 0x02, 0xd0, 0x26, 0xa9, 0x01, 0x85, 0x02,
                            0x60, 0xa9, 0x08, 0x24, 0x02, 0xd0, 0x1b, 0xa9, 0x02, 0x85, 0x02, 0x60, 0xa9, 0x01, 0x24,
                            0x02, 0xd0, 0x10, 0xa9, 0x04, 0x85, 0x02, 0x60, 0xa9, 0x02, 0x24, 0x02, 0xd0, 0x05, 0xa9,
                            0x08, 0x85, 0x02, 0x60, 0x60, 0x20, 0x94, 0x06, 0x20, 0xa8, 0x06, 0x60, 0xa5, 0x00, 0xc5,
                            0x10, 0xd0, 0x0d, 0xa5, 0x01, 0xc5, 0x11, 0xd0, 0x07, 0xe6, 0x03, 0xe6, 0x03, 0x20, 0x2a,
                            0x06, 0x60, 0xa2, 0x02, 0xb5, 0x10, 0xc5, 0x10, 0xd0, 0x06, 0xb5, 0x11, 0xc5, 0x11, 0xf0,
                            0x09, 0xe8, 0xe8, 0xe4, 0x03, 0xf0, 0x06, 0x4c, 0xaa, 0x06, 0x4c, 0x35, 0x07, 0x60, 0xa6,
                            0x03, 0xca, 0x8a, 0xb5, 0x10, 0x95, 0x12, 0xca, 0x10, 0xf9, 0xa5, 0x02, 0x4a, 0xb0, 0x09,
                            0x4a, 0xb0, 0x19, 0x4a, 0xb0, 0x1f, 0x4a, 0xb0, 0x2f, 0xa5, 0x10, 0x38, 0xe9, 0x20, 0x85,
                            0x10, 0x90, 0x01, 0x60, 0xc6, 0x11, 0xa9, 0x01, 0xc5, 0x11, 0xf0, 0x28, 0x60, 0xe6, 0x10,
                            0xa9, 0x1f, 0x24, 0x10, 0xf0, 0x1f, 0x60, 0xa5, 0x10, 0x18, 0x69, 0x20, 0x85, 0x10, 0xb0,
                            0x01, 0x60, 0xe6, 0x11, 0xa9, 0x06, 0xc5, 0x11, 0xf0, 0x0c, 0x60, 0xc6, 0x10, 0xa5, 0x10,
                            0x29, 0x1f, 0xc9, 0x1f, 0xf0, 0x01, 0x60, 0x4c, 0x35, 0x07, 0xa0, 0x00, 0xa5, 0xfe, 0x91,
                            0x00, 0x60, 0xa6, 0x03, 0xa9, 0x00, 0x81, 0x10, 0xa2, 0x00, 0xa9, 0x01, 0x81, 0x10, 0x60,
                            0xa2, 0x00, 0xea, 0xea, 0xca, 0xd0, 0xfb, 0x60};
    size_t program_len = sizeof(program) / sizeof(program[0]);
    load_program(program, program_len);

    /* Initial configs for snake program */
    CPU.memory[0x00FE] = (uint8_t) 0x02;        // random number at loc xFE
    CPU.memory[0x00FF] = (uint8_t) 0x73;        // initial snake direction -> down
    /*************************************/


    // Game must end with snake hitting the wall
    execute(break_point);
    return 0;
}

```

An explanation of how the program works is [here](https://skilldrick.github.io/easy6502/).

I verified the proper execution of the program by analysing the [log](log) file. Yet to add a graphical interface for the user to actually play the game on the emulator.

## Debugging (As of now)

You can pass ```-break``` flag as an argument following with the program counter address at which you want a breakpoint (in hexadecimal). No functionality for stepping to next line has been implemented yet. 

```bash
./main -break 6c3 # Breakpoint at 0x06c3
```

## Running Tests

To run the test script:

```bash
$ make utest

[+] Passed Test Case: test_ldx, FILE: test/unittest.c
[+] Passed Test Case: test_immediate, FILE: test/unittest.c
[+] Passed Test Case: test_zero_page, FILE: test/unittest.c
[+] Passed Test Case: test_zero_page_x, FILE: test/unittest.c
[+] Passed Test Case: test_absolute, FILE: test/unittest.c
[+] Passed Test Case: test_absolute_x, FILE: test/unittest.c
[+] Passed Test Case: test_indirect_x, FILE: test/unittest.c
[+] Passed Test Case: test_adc_lda, FILE: test/unittest.c
[+] Passed Test Case: test_brk, FILE: test/unittest.c
[+] Passed Test Case: test_brk, FILE: test/unittest.c
[+] Passed Test Case: test_and, FILE: test/unittest.c
[+] Passed Test Case: test_asl_accumulator, FILE: test/unittest.c
[+] Passed Test Case: test_asl_memory, FILE: test/unittest.c
[+] Passed Test Case: test_bcc, FILE: test/unittest.c
[+] Passed Test Case: test_bcs, FILE: test/unittest.c
[+] Passed Test Case: test_beq, FILE: test/unittest.c
[+] Passed Test Case: test_bit, FILE: test/unittest.c
[+] Passed Test Case: test_bmi, FILE: test/unittest.c
[+] Passed Test Case: test_bne, FILE: test/unittest.c
[+] Passed Test Case: test_bpl, FILE: test/unittest.c
[+] Passed Test Case: test_bvc, FILE: test/unittest.c
[+] Passed Test Case: test_bvs, FILE: test/unittest.c
[+] Passed Test Case: test_clc, FILE: test/unittest.c
[+] Passed Test Case: test_cld, FILE: test/unittest.c
[+] Passed Test Case: test_clv, FILE: test/unittest.c

$
```

## Todo 

* Create some kind of program for viewing snake game like [this](https://skilldrick.github.io/easy6502/) blog does - maybe python 

* Allow user to pass disassembled programs as a file argument. 

* Come up with better debugging functionality
