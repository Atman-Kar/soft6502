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





