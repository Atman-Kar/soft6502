#include<stdio.h> 
#include<stdlib.h>
#include<stdint.h>
#include<assert.h>
#include<string.h>

#include "cpu.h"
#include "opcodes.h"

/*
* Define the CPU registers:
* PC - Program Counter Register
* SP - Stack Pointer Register
* A  - Accumulator Register
* X  - Index Register
* Y  - Index Register
* P  - Processor Status Register
*/

/* Print the CPU Regs neatly
*  - debugging purposes  
*/
void display_cpu_regs(void) {
    /*
    * Dump out all the register contents neatly.
    */

    printf("###################################\n");
    printf("PC : %x\nSP : %x\n", CPU.PC, CPU.SP);
    printf("A  : %x\nX  : %x\n", CPU.A, CPU.X);
    printf("Y  : %x\nP  : %x\n", CPU.Y, CPU.P);
    printf("###################################\n");
}

/* Reset the CPU */
void reset_cpu(void) {   

    CPU.PC = 0;                            
    CPU.SP = 0;                            
    CPU.A =  0;                             
    CPU.X =  0;                             
    CPU.Y =  0;                             
    CPU.P =  0;                             
    memset(CPU.memory, 0x00, MEM_SIZE);    
}


/* Read 1 byte from the given memory address M*/
uint8_t mem_read(uint16_t mem_addr) {
    /* Read this mem location - PC */
    return CPU.memory[mem_addr];
}

/* Read 2 bytes respectively from the given memory address M and M+1 */
uint16_t mem_read_u16(uint16_t mem_addr) {
    /* Read 2 bytes out from this mem loc - PC */
    uint16_t lo_byte = (uint16_t) mem_read(mem_addr);
    uint16_t hi_byte = (uint16_t) mem_read(mem_addr + 1);

    return ((hi_byte << 8) | lo_byte); 
}

/* Write 1 byte of data into memory location M */
void mem_write(uint16_t mem_addr, uint8_t data) {
    /* Write to memory location */

    CPU.memory[mem_addr] = data;
}

/* Push byte to stack */
void push(uint8_t stack_data) {
    CPU.memory[CPU.SP + STACK_OFFSET_VAL] = stack_data;
    (CPU.SP)--;
    // printf("Pushed 0x%x\n", stack_data);
}

/* Push word to stack */
void push_u16(uint16_t stack_data) {
    uint8_t lo = (uint8_t) (stack_data & 0x00FF);
    uint8_t hi = (uint8_t) ((stack_data & 0xFF00) >> 8);
    CPU.memory[CPU.SP + STACK_OFFSET_VAL] = hi;
    (CPU.SP)--;
    CPU.memory[CPU.SP + STACK_OFFSET_VAL] = lo;
    (CPU.SP)--;
    // printf("Pushed 0x%x\n", (hi << 8) | lo);
}

/* pull byte from stack */
uint8_t pull() {
    (CPU.SP)++;
    // printf("Popped 0x%x\n", CPU.memory[CPU.SP]);
    return CPU.memory[CPU.SP + STACK_OFFSET_VAL];
}

/* pull word from stack */
uint16_t pull_u16() {
    (CPU.SP)++;
    uint8_t val_lo = CPU.memory[CPU.SP + STACK_OFFSET_VAL];
    (CPU.SP)++;
    uint8_t val_hi = CPU.memory[CPU.SP + STACK_OFFSET_VAL];
    // printf("Popped 0x%x\n", (val_hi << 8) | val_lo);
    return ((val_hi << 8) | val_lo);
}


/* Load the program into memory at 
*  location MEM_PROG_BEGIN 
*/
void load_program(uint8_t *program, size_t len) {
    /* 
    * Load a program into the memory
    * at the address 0x8000
    */

   uint16_t load_prog_addr = MEM_PROG_BEGIN;
   for(size_t i=0; i < len; i++) {
       CPU.memory[load_prog_addr] = program[i];
       load_prog_addr++;

       /* load_prog_addr will always be less than 0xFFFF due to data type */
       /* Assert that no overflow has occured */
       assert(load_prog_addr > MEM_PROG_BEGIN && "FATAL: MEM_PRG OVERFLOW");
   }

   /* Init Program Counter Register at MEM_PROG_BEGIN location */
   CPU.PC = MEM_PROG_BEGIN;

   /* Init Stack Pointer Register at STACK_BEGIN location */
   CPU.SP = STACK_BEGIN;
}

/* 
* Resolve the memory address of the operand
* based on the type of addressing mode 
*/ 
uint16_t operand_address_resolve(admod mode){

   uint16_t mem_addr; 
   uint16_t ptr;
   switch (mode) {
       case Immediate:
            mem_addr = CPU.PC;
            (CPU.PC)++;
            break;
            
        case ZeroPage:
            mem_addr = (uint16_t) mem_read(CPU.PC);
            (CPU.PC)++;
            break;
        
        case Absolute:
            mem_addr = mem_read_u16(CPU.PC);
            CPU.PC = CPU.PC + 2;
            break;
        
        case ZeroPageX:
            mem_addr = (uint16_t) mem_read(CPU.PC);
            mem_addr = mem_addr + (uint16_t) CPU.X;
            (CPU.PC)++;
            break;
        
        case ZeroPageY:
            mem_addr = (uint16_t) mem_read(CPU.PC);
            mem_addr = mem_addr + (uint16_t) CPU.Y;
            (CPU.PC)++;
            break;
        
        case AbsoluteX:
            mem_addr = (uint16_t) mem_read_u16(CPU.PC);
            mem_addr = mem_addr + (uint16_t) CPU.X;
            CPU.PC = CPU.PC + 2;
            break;

        case AbsoluteY:
            mem_addr = (uint16_t) mem_read_u16(CPU.PC);
            mem_addr = mem_addr + (uint16_t) CPU.Y;
            CPU.PC = CPU.PC + 2;
            break;
        
        case IndirectX:
            ptr  = (uint16_t) (mem_read(CPU.PC) + CPU.X);
            mem_addr = mem_read_u16(ptr);
            (CPU.PC)++;
            break;
        
        case IndirectY:
            ptr  = (uint16_t) (mem_read(CPU.PC) + CPU.X);
            mem_addr = mem_read_u16(ptr);
            (CPU.PC)++;
            break;
        
        case Indirect:
            ptr  = mem_read_u16(CPU.PC);
            mem_addr = mem_read_u16(ptr);
            CPU.PC = CPU.PC + 2;
            break;
        
        case Accumulator:
            mem_addr = 0;
            (CPU.PC)++;
            break;
        
        case Implied:
            /* Do nothing */
            break;

   }

   return mem_addr;
}

/* Set the FLAG in process status register */
void set_process_status_reg(PS_FLAG FLAG) {
    CPU.P |= (1 << FLAG);
}

/* Reset the FLAG in process status register */
void reset_process_status_reg(PS_FLAG FLAG) {
    CPU.P &= ~(1 << FLAG);
}

/* Return if FLAG is set or not */
int process_status_val(PS_FLAG FLAG) {
    if(CPU.P & (1 << FLAG)) {
        return 1;
    } else {
        return 0;
    }
}

/* Execute all the opcodes in the program */
void execute(uint16_t break_point){
    PRG_FLAG FLAG;
    uint8_t opcode;
    while(1) {
        opcode = mem_read(CPU.PC);
        printf("Running Opcode : 0x%x\n", opcode);
        display_cpu_regs();
        if(break_point == CPU.PC) return;

        (CPU.PC)++; // Increment PC

        /* Execute the opcode switch statements here */
        FLAG = run(opcode, &CPU);
        switch (FLAG) {
            case EXECUTION:
                continue;
            
            case EXIT_PROG:
                return;
            
            case ILLEGAL_INSTRUCTION:
                printf("FATAL: ILLEGAL INSTRUCTION\n");
                return;
        }
    }   
}