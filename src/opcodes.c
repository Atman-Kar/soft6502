#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>

#include "opcodes.h"

// Function Prototypes

int ADC(struct cpu* CPU, admod add_mode);
int BRK(struct cpu* CPU);
int LDX(struct cpu* CPU, admod add_mode);
int LDY(struct cpu* CPU, admod add_mode);
int LDA(struct cpu* CPU, admod add_mode);
int AND(struct cpu* CPU, admod add_mode);
int ASL(struct cpu* CPU, admod add_mode);
int BCC(struct cpu* CPU);
int BCS(struct cpu* CPU);
int BEQ(struct cpu* CPU);
int BIT(struct cpu* CPU, admod add_mode);
int BMI(struct cpu* CPU);
int BNE(struct cpu* CPU);
int BPL(struct cpu* CPU);
int BVC(struct cpu* CPU);
int BVS(struct cpu* CPU);
int CLC();
int CLD();
int CLI();
int NOP();
int CLV();
int HLT();
int CMP(struct cpu* CPU, admod add_mode);
int CPX(struct cpu* CPU, admod add_mode);
int CPY(struct cpu* CPU, admod add_mode);
int DEC(struct cpu* CPU, admod add_mode);
int DEX(struct cpu* CPU);
int DEY(struct cpu* CPU);
int EOR(struct cpu* CPU, admod add_mode);

/* Huuuuuge opcode switch case lol */
int run(uint8_t opcode, struct cpu* CPU) {
        
    switch (opcode){
        case 0x69:
            return ADC(CPU, Immediate);
        case 0x65:
            return ADC(CPU, ZeroPage);
        case 0x75:
            return ADC(CPU, ZeroPageX);
        case 0x6D:
            return ADC(CPU, Absolute);
        case 0x7D:
            return ADC(CPU, AbsoluteX);
        case 0x79:
            return ADC(CPU, AbsoluteY);
        case 0x61:
            return ADC(CPU, IndirectX);
        case 0x71:
            return ADC(CPU, IndirectY);
        case 0x00:
            return BRK(CPU);
        case 0xA2:
            return LDX(CPU, Immediate);
        case 0xA6:
            return LDX(CPU, ZeroPage);
        case 0xB6:
            return LDX(CPU, ZeroPageY);
        case 0xAE:
            return LDX(CPU, Absolute);
        case 0xBE:
            return LDX(CPU, AbsoluteY);
        case 0xA0:
            return LDY(CPU, Immediate);
        case 0xA4:
            return LDY(CPU, ZeroPage);
        case 0xB4:
            return LDY(CPU, ZeroPageX);
        case 0xAC:
            return LDY(CPU, Absolute);
        case 0xBC:
            return LDY(CPU, AbsoluteX);
        case 0xA9:
            return LDA(CPU, Immediate);
        case 0xA5:
            return LDA(CPU, ZeroPage);
        case 0xB5:
            return LDA(CPU, ZeroPageX);
        case 0xAD:
            return LDA(CPU, Absolute);
        case 0xBD:
            return LDA(CPU, AbsoluteX);
        case 0xA1:
            return LDA(CPU, IndirectX);
        case 0xB1:
            return LDA(CPU, IndirectY);
        case 0x29:
            return AND(CPU, Immediate);
        case 0x25:
            return AND(CPU, ZeroPage);
        case 0x35:
            return AND(CPU, ZeroPageX);
        case 0x2D:
            return AND(CPU, Absolute);
        case 0x3D:
            return AND(CPU, AbsoluteX);
        case 0x39:
            return AND(CPU, AbsoluteY);
        case 0x21:
            return AND(CPU, IndirectX);
        case 0x31:
            return AND(CPU, IndirectY);
        case 0x0A:
            return ASL(CPU, Accumulator);
        case 0x06:
            return ASL(CPU, ZeroPage);
        case 0x16:
            return ASL(CPU, ZeroPageX);
        case 0x0E:
            return ASL(CPU, Absolute);
        case 0x1E:
            return ASL(CPU, AbsoluteX);
        case 0x90:
            return BCC(CPU);
        case 0xB0:
            return BCS(CPU);
        case 0xF0:
            return BEQ(CPU);
        case 0x24:
            return BIT(CPU, ZeroPage);
        case 0x2C:
            return BIT(CPU, Absolute);
        case 0x30:
            return BMI(CPU);
        case 0xD0:
            return BNE(CPU);
        case 0x10:
            return BPL(CPU);
        case 0x50:
            return BVC(CPU);
        case 0x70:
            return BVS(CPU);
        case 0x18:
            return CLC();
        case 0xD8:
            return CLD();
        case 0x58:
            return CLI();
        case 0xEA:
            return NOP();
        case 0xB8:
            return CLV();
        case 0x02:
            return HLT();
        case 0xC9:
            return CMP(CPU, Immediate);
        case 0xC5:
            return CMP(CPU, ZeroPage);
        case 0xD5:
            return CMP(CPU, ZeroPageX);
        case 0xCD:
            return CMP(CPU, Absolute);
        case 0xDD:
            return CMP(CPU, AbsoluteX);
        case 0xD9:
            return CMP(CPU, AbsoluteY);
        case 0xC1:
            return CMP(CPU, IndirectX);
        case 0xD1:
            return CMP(CPU, IndirectY);
        case 0xE0:
            return CPX(CPU, Immediate);
        case 0xE4:
            return CPX(CPU, ZeroPage);
        case 0xEC:
            return CPX(CPU, Absolute);
        case 0xC0:
            return CPY(CPU, Immediate);
        case 0xC4:
            return CPY(CPU, ZeroPage);
        case 0xCC:
            return CPY(CPU, Absolute);
        case 0xC6:
            return DEC(CPU, ZeroPage);
        case 0xD6:
            return DEC(CPU, ZeroPageX);
        case 0xCE:
            return DEC(CPU, Absolute);
        case 0xDE:
            return DEC(CPU, AbsoluteX);
        case 0xCA:
            return DEX(CPU);
        case 0x88:
            return DEY(CPU);
        case 0x49:
            return EOR(CPU, Immediate);
        case 0x45:
            return EOR(CPU, ZeroPage);
        case 0x55:
            return EOR(CPU, ZeroPageX);
        case 0x4D:
            return EOR(CPU, Absolute);
        case 0x5D:
            return EOR(CPU, AbsoluteX);
        case 0x59:
            return EOR(CPU, AbsoluteY);
        case 0x41:
            return EOR(CPU, IndirectX);
        case 0x51:
            return EOR(CPU, IndirectY);

    };

    return ILLEGAL_INSTRUCTION;
}

/* Add with Carry */
int ADC(struct cpu* CPU, admod add_mode){

    /*
    * Manage the following flags:
    *   Carry Flag
    *   Zero Flag
    *   Overflow Flag
    *   Negative Flag
    */

    uint16_t mem_addr = operand_address_resolve(add_mode);
    uint8_t operand = CPU->memory[mem_addr]; // Retrieve the operand 
    uint8_t old_A = CPU->A; // For C flag setting 

    CPU->A = CPU->A + operand + process_status_val(CARRY_FLAG); // ADD

    if((CPU->A < old_A) && (CPU->A < operand)) {
        set_process_status_reg(CARRY_FLAG); // CARRY FLAG
        set_process_status_reg(OVERFLOW_FLAG); // OVERFLOW FLAG
    } else {
        reset_process_status_reg(CARRY_FLAG); // CARRY FLAG
        reset_process_status_reg(OVERFLOW_FLAG); // OVERFLOW FLAG
    }

    if(CPU->A == 0) {
        set_process_status_reg(ZERO_FLAG); // ZERO FLAG
        reset_process_status_reg(NEGATIVE_FLAG); // NEGATIVE FLAG
    }

    if(CPU->A & (1 << NEGATIVE_FLAG)) {
        set_process_status_reg(NEGATIVE_FLAG); // NEGATIVE FLAG
        reset_process_status_reg(ZERO_FLAG); // ZERO FLAG
    }

    return EXECUTION;
}

/* Force Break */
int BRK(struct cpu* CPU) {
    // Push "PC + 2", PC at BRK instruction
    // Skipping one slot for break mark -> Reason for breaking 
    // Also push Process Status Register

    // Break Flag is set while pushed to stack
    // But on popping using RTI / PLP - Break Flag ignored

    if(!process_status_val(INTERRUPT_DISABLED_FLAG)) {

        uint8_t to_stack_P = CPU->P | (1 << BREAK_FLAG);                // Process Status with BRK = 1

        push_u16(CPU->PC);
        push(to_stack_P);                                               // Push P with BRK = 1

        CPU->PC = mem_read_u16(IRQ_ADDR);
        set_process_status_reg(INTERRUPT_DISABLED_FLAG);

    }
    return EXECUTION;
}

/* Load X register */
int LDX(struct cpu* CPU, admod add_mode) {
    /*
    * Manage the following flags:
    *   Zero Flag
    *   Negative Flag
    */   
    uint16_t mem_addr = operand_address_resolve(add_mode);
    uint8_t operand = CPU->memory[mem_addr]; // Retrieve the operand 

    CPU->X = operand;

    if(CPU->X == 0) {
        set_process_status_reg(ZERO_FLAG); // ZERO FLAG
        reset_process_status_reg(NEGATIVE_FLAG); // NEGATIVE FLAG
    }

    if(CPU->X & (1 << NEGATIVE_FLAG)) {
        set_process_status_reg(NEGATIVE_FLAG); // NEGATIVE FLAG
        reset_process_status_reg(ZERO_FLAG); // ZERO FLAG
    }

    return EXECUTION;
}

/* Load Y register */
int LDY(struct cpu* CPU, admod add_mode) {
    /*
    * Manage the following flags:
    *   Zero Flag
    *   Negative Flag
    */   
    uint16_t mem_addr = operand_address_resolve(add_mode);
    uint8_t operand = CPU->memory[mem_addr]; // Retrieve the operand 

    CPU->Y = operand;

    if(CPU->Y == 0) {
        set_process_status_reg(ZERO_FLAG); // ZERO FLAG
        reset_process_status_reg(NEGATIVE_FLAG); // NEGATIVE FLAG
    }

    if(CPU->Y & (1 << NEGATIVE_FLAG)) {
        set_process_status_reg(NEGATIVE_FLAG); // NEGATIVE FLAG
        reset_process_status_reg(ZERO_FLAG); // ZERO FLAG
    }

    return EXECUTION;
}

/* Load Accumulator */
int LDA(struct cpu* CPU, admod add_mode) {
    /*
    * Manage the following flags:
    *   Zero Flag
    *   Negative Flag
    */   
    uint16_t mem_addr = operand_address_resolve(add_mode);
    uint8_t operand = CPU->memory[mem_addr]; // Retrieve the operand 

    CPU->A = operand;

    if(CPU->A == 0) {
        set_process_status_reg(ZERO_FLAG); // ZERO FLAG
        reset_process_status_reg(NEGATIVE_FLAG); // NEGATIVE FLAG
    }

    if(CPU->A & (1 << NEGATIVE_FLAG)) {
        set_process_status_reg(NEGATIVE_FLAG); // NEGATIVE FLAG
        reset_process_status_reg(ZERO_FLAG); // ZERO FLAG
    }

    return EXECUTION;
}

/* AND memory with accumulator */
int AND(struct cpu* CPU, admod add_mode) {
    /*
    * Manage the following flags:
    *   Zero Flag
    *   Negative Flag
    */   
    uint16_t mem_addr = operand_address_resolve(add_mode);
    uint8_t operand = CPU->memory[mem_addr]; // Retrieve the operand 

    CPU->A = (CPU->A) & operand;

    if(CPU->A == 0) {
        set_process_status_reg(ZERO_FLAG); // ZERO FLAG
        reset_process_status_reg(NEGATIVE_FLAG); // NEGATIVE FLAG
    }

    if(CPU->A & (1 << NEGATIVE_FLAG)) {
        set_process_status_reg(NEGATIVE_FLAG); // NEGATIVE FLAG
        reset_process_status_reg(ZERO_FLAG); // ZERO FLAG
    }

    return EXECUTION;
}

/* Left shift memory or accumulator */
int ASL(struct cpu* CPU, admod add_mode) {
    /*
    * Manage the following flags:
    *   Zero Flag
    *   Negative Flag
    *   Carry Flag 
    */   

    if (add_mode == Accumulator) {
        /* Handle separately */
        if((CPU->A) & (1 << NEGATIVE_FLAG)) {
            set_process_status_reg(CARRY_FLAG); // CARRY FLAG
        }

        CPU->A = (CPU->A) << 1;

        if(CPU->A == 0) {
            set_process_status_reg(ZERO_FLAG); // ZERO FLAG
            reset_process_status_reg(NEGATIVE_FLAG); // NEGATIVE FLAG
        }

        if(CPU->A & (1 << NEGATIVE_FLAG)) {
            set_process_status_reg(NEGATIVE_FLAG); // NEGATIVE FLAG
            reset_process_status_reg(ZERO_FLAG); // ZERO FLAG
        }

        return EXECUTION;
    }

    uint16_t mem_addr = operand_address_resolve(add_mode); 

    if((CPU->memory[mem_addr]) & (1 << NEGATIVE_FLAG)) {
        set_process_status_reg(CARRY_FLAG); // CARRY FLAG
    }

    CPU->memory[mem_addr] = (CPU->memory[mem_addr]) << 1;

    if(CPU->memory[mem_addr] == 0) {
        set_process_status_reg(ZERO_FLAG); // ZERO FLAG
        reset_process_status_reg(NEGATIVE_FLAG); // NEGATIVE FLAG
    }

    if(CPU->memory[mem_addr] & (1 << NEGATIVE_FLAG)) {
        set_process_status_reg(NEGATIVE_FLAG); // NEGATIVE FLAG
        reset_process_status_reg(ZERO_FLAG); // ZERO FLAG
    }

    return EXECUTION;
}

/* Branch on Carry Clear */
int BCC(struct cpu* CPU){
    uint8_t operand = CPU->memory[CPU->PC]; // Retrieve the operand 
    if (!process_status_val(CARRY_FLAG)) {
        CPU->PC = CPU->PC + (int8_t) operand;        // Jump by offset 
    } else {
        (CPU->PC)++;
    }

    return EXECUTION;
}

/* Branch on Carry Set */
int BCS(struct cpu* CPU){
    uint8_t operand = CPU->memory[CPU->PC]; // Retrieve the operand 
    if (process_status_val(CARRY_FLAG)) {
        CPU->PC = CPU->PC + (int8_t) operand;        // Jump by offset 
    } else {
        (CPU->PC)++;
    }

    return EXECUTION;
}

/* Branch on Zero FLag */
int BEQ(struct cpu* CPU){
    uint8_t operand = CPU->memory[CPU->PC]; // Retrieve the operand  
    if (process_status_val(ZERO_FLAG)) {
        CPU->PC = CPU->PC + (int8_t) operand;        // Jump by offset 
    } else {
        (CPU->PC)++;
    }

    return EXECUTION;
}

/* Test bits in memory with accumulator */
int BIT(struct cpu* CPU, admod add_mode){
    /*
    * Manage the following flags:
    *   Zero Flag
    *   Negative Flag
    *   Overflow Flag 
    */ 

    uint8_t operand = CPU->memory[operand_address_resolve(add_mode)];
    if(((CPU->A) & (operand)) == 0x00) {
        set_process_status_reg(ZERO_FLAG);
    }

    if(operand & (1 << 7)) { // BIT M7
        set_process_status_reg(NEGATIVE_FLAG);
    } else {
        reset_process_status_reg(NEGATIVE_FLAG);
    }

    if(operand & (1 << 6)) { // BIT M6
        set_process_status_reg(OVERFLOW_FLAG);
    } else {
        reset_process_status_reg(OVERFLOW_FLAG);
    }
     
    return EXECUTION;
}

/* Branch on result minus */
int BMI(struct cpu* CPU){
    uint8_t operand = CPU->memory[CPU->PC]; // Retrieve the operand  
    if (process_status_val(NEGATIVE_FLAG)) {
        CPU->PC = CPU->PC + (int8_t) operand;        // Jump by offset 
    } else {
        (CPU->PC)++;
    }

    return EXECUTION;
}

/* Branch on result not zero */
int BNE(struct cpu* CPU){
    uint8_t operand = CPU->memory[CPU->PC]; // Retrieve the operand  
    if (!process_status_val(ZERO_FLAG)) {
        CPU->PC = CPU->PC + (int8_t) operand;        // Jump by offset 
    } else {
        (CPU->PC)++;
    }

    return EXECUTION;
}

/* Branch on positive result */
int BPL(struct cpu* CPU){
    uint8_t operand = CPU->memory[CPU->PC]; // Retrieve the operand  
    if (!process_status_val(NEGATIVE_FLAG)) {
        CPU->PC = CPU->PC + (int8_t) operand;        // Jump by offset 
    } else {
        (CPU->PC)++;
    }

    return EXECUTION;
}

/* Branch on overflow zero */
int BVC(struct cpu* CPU){
    uint8_t operand = CPU->memory[CPU->PC]; // Retrieve the operand  
    if (!process_status_val(OVERFLOW_FLAG)) {
        CPU->PC = CPU->PC + (int8_t) operand;        // Jump by offset 
    } else {
        (CPU->PC)++;
    }

    return EXECUTION;
}

/* Branch on overflow set */
int BVS(struct cpu* CPU){
    uint8_t operand = CPU->memory[CPU->PC]; // Retrieve the operand  
    if (process_status_val(OVERFLOW_FLAG)) {
        CPU->PC = CPU->PC + (int8_t) operand;        // Jump by offset 
    } else {
        (CPU->PC)++;
    }

    return EXECUTION;
}

/* Clear the carry flag */
int CLC() {
    reset_process_status_reg(CARRY_FLAG);
    return EXECUTION;
}

/* Clear the Decimal flag */
int CLD() {
    reset_process_status_reg(DECIMAL_MODE_FLAG);
    return EXECUTION;
}

/* Clear the Interrupt Disable flag */
int CLI() {
    reset_process_status_reg(INTERRUPT_DISABLED_FLAG);
    return EXECUTION;
}

/* No OPeration */
int NOP() {
    return EXECUTION;
}

/* Clear the overflow flag */
int CLV() {
    reset_process_status_reg(OVERFLOW_FLAG);
    return EXECUTION;
}

/* Freeze the CPU */
int HLT() {
    return EXIT_PROG;
}

/* Compare instruction */
int CMP(struct cpu* CPU, admod add_mode) {
    /*
    * Manage the following flags:
    *   Zero Flag
    *   Negative Flag
    *   Carry Flag 
    */ 

    uint8_t operand = CPU->memory[operand_address_resolve(add_mode)];
    
    if(CPU->A > operand){
        reset_process_status_reg(ZERO_FLAG);
        reset_process_status_reg(CARRY_FLAG);
        reset_process_status_reg(NEGATIVE_FLAG);
    } else if (CPU->A == operand) {
        set_process_status_reg(ZERO_FLAG);
        set_process_status_reg(CARRY_FLAG);
        reset_process_status_reg(NEGATIVE_FLAG);
    } else {
        reset_process_status_reg(ZERO_FLAG);
        set_process_status_reg(CARRY_FLAG);
        set_process_status_reg(NEGATIVE_FLAG);
    }

    return EXECUTION;
}

/* Compare with X register */
int CPX(struct cpu* CPU, admod add_mode) {
    /*
    * Manage the following flags:
    *   Zero Flag
    *   Negative Flag
    *   Carry Flag 
    */ 

    uint8_t operand = CPU->memory[operand_address_resolve(add_mode)];
    
    if(CPU->X > operand){
        reset_process_status_reg(ZERO_FLAG);
        reset_process_status_reg(CARRY_FLAG);
        reset_process_status_reg(NEGATIVE_FLAG);
    } else if (CPU->X == operand) {
        set_process_status_reg(ZERO_FLAG);
        set_process_status_reg(CARRY_FLAG);
        reset_process_status_reg(NEGATIVE_FLAG);
    } else {
        reset_process_status_reg(ZERO_FLAG);
        set_process_status_reg(CARRY_FLAG);
        set_process_status_reg(NEGATIVE_FLAG);
    }

    return EXECUTION;
}

/* Compare with Y register */
int CPY(struct cpu* CPU, admod add_mode) {
    /*
    * Manage the following flags:
    *   Zero Flag
    *   Negative Flag
    *   Carry Flag 
    */ 

    uint8_t operand = CPU->memory[operand_address_resolve(add_mode)];
    
    if(CPU->Y > operand){
        reset_process_status_reg(ZERO_FLAG);
        reset_process_status_reg(CARRY_FLAG);
        reset_process_status_reg(NEGATIVE_FLAG);
    } else if (CPU->Y == operand) {
        set_process_status_reg(ZERO_FLAG);
        set_process_status_reg(CARRY_FLAG);
        reset_process_status_reg(NEGATIVE_FLAG);
    } else {
        reset_process_status_reg(ZERO_FLAG);
        set_process_status_reg(CARRY_FLAG);
        set_process_status_reg(NEGATIVE_FLAG);
    }

    return EXECUTION;
}

/* Decrement Memory by 1 */
int DEC(struct cpu* CPU, admod add_mode) {
    /*
    * Manage the following flags:
    *   Zero Flag
    *   Negative Flag
    */ 

    uint8_t operand = CPU->memory[operand_address_resolve(add_mode)];

    if (operand == 1) {
        reset_process_status_reg(NEGATIVE_FLAG);
        set_process_status_reg(ZERO_FLAG);
    }

    if (operand == 0) {
        set_process_status_reg(NEGATIVE_FLAG);
        reset_process_status_reg(ZERO_FLAG);
    }

    CPU->memory[operand_address_resolve(add_mode)] = operand - 1;

    return EXECUTION;
}

/* Decrement X Register */
int DEX(struct cpu* CPU) {
    /*
    * Manage the following flags:
    *   Zero Flag
    *   Negative Flag
    */ 

    uint8_t operand = CPU->X;

    if (operand == 1) {
        reset_process_status_reg(NEGATIVE_FLAG);
        set_process_status_reg(ZERO_FLAG);
    }

    if (operand == 0) {
        set_process_status_reg(NEGATIVE_FLAG);
        reset_process_status_reg(ZERO_FLAG);
    }

    CPU->X = operand - 1;

    return EXECUTION;
}

/* Decrement Y Register */
int DEY(struct cpu* CPU) {
    /*
    * Manage the following flags:
    *   Zero Flag
    *   Negative Flag
    */ 

    uint8_t operand = CPU->Y;

    if (operand == 1) {
        reset_process_status_reg(NEGATIVE_FLAG);
        set_process_status_reg(ZERO_FLAG);
    }

    if (operand == 0) {
        set_process_status_reg(NEGATIVE_FLAG);
        reset_process_status_reg(ZERO_FLAG);
    }

    CPU->Y = operand - 1;

    return EXECUTION;
}

/* Exculive OR Memory with Accumulator */
int EOR(struct cpu* CPU, admod add_mod) {
    /*
    * Manage the following flags:
    *   Zero Flag
    *   Negative Flag
    */ 

    uint8_t operand = CPU->memory[operand_address_resolve(add_mod)];

    CPU->A = CPU->A ^ operand;

    if (CPU->A == 0) {
        reset_process_status_reg(NEGATIVE_FLAG);
        set_process_status_reg(ZERO_FLAG);
    }

    if ((int8_t) CPU->A < 0) {
        set_process_status_reg(NEGATIVE_FLAG);
        reset_process_status_reg(ZERO_FLAG);
    }

    return EXECUTION;
}