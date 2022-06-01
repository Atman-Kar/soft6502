#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <../src/opcodes.h>
#include <../src/cpu.h>
#include "unittest.h"

void test_immediate(struct cpu* CPU) {
    reset_cpu();
    uint8_t expected = 0x27;
    CPU->memory[CPU->PC] = expected;

    uint8_t result = CPU->memory[operand_address_resolve(Immediate)];
    ASSERT_EQUAL(expected, result);
}

void test_zero_page(struct cpu* CPU) {
    reset_cpu();
    uint8_t expected = 0x27;
    uint16_t loc = 0x0018;

    CPU->memory[loc] = expected;

    CPU->memory[CPU->PC] = (uint8_t) loc;

    uint8_t result = CPU->memory[operand_address_resolve(ZeroPage)];
    ASSERT_EQUAL(expected, result);
}

void test_zero_page_x(struct cpu* CPU) {
    reset_cpu();
    uint8_t expected = 0x27;
    uint16_t loc = 0x0018;
    uint16_t x = 0x0013;

    CPU->memory[loc + x] = expected;
    CPU->memory[CPU->PC] = (uint8_t) loc;
    CPU->X = 0x0013;

    uint8_t result = CPU->memory[operand_address_resolve(ZeroPageX)];
    ASSERT_EQUAL(expected, result);
}

void test_absolute(struct cpu* CPU) {
    reset_cpu();
    int expected = 0x23;
    uint16_t loc = 0x90FF;
    
    CPU->memory[loc] = expected;
    CPU->memory[CPU->PC] = 0xFF;
    CPU->memory[(CPU->PC) + 1] = 0x90;

    uint8_t result = CPU->memory[operand_address_resolve(Absolute)];
    ASSERT_EQUAL(expected, result);
}

void test_absolute_x(struct cpu* CPU) {
    reset_cpu();
    int expected = 0x23;
    uint16_t loc = 0x9000;
    
    CPU->memory[0x9032] = expected;
    CPU->memory[CPU->PC] = 0x00;
    CPU->memory[(CPU->PC) + 1] = 0x90;
    CPU->X = 0x32;

    uint8_t result = CPU->memory[operand_address_resolve(AbsoluteX)];
    ASSERT_EQUAL(expected, result);
}

void test_indirect_x(struct cpu* CPU) {
    reset_cpu();
    int expected = 0x23;
    uint16_t loc = 0x6322;
    
    CPU->memory[loc] = expected;
    CPU->memory[CPU->PC] = 0x17;
    CPU->X = 0x2A;
    CPU->memory[0x0041] = 0x22;
    CPU->memory[0x0042] = 0x63;

    uint8_t result = CPU->memory[operand_address_resolve(IndirectX)];
    ASSERT_EQUAL(expected, result);
}

void test_ldx(struct cpu* CPU) {
    reset_cpu();
    int expected = 0x23;
    uint8_t program[] = {0xA2, 0x23, 0x02};
    size_t program_len = sizeof(program) / sizeof(program[0]);
    load_program(program, program_len);
    execute();
    ASSERT_EQUAL(CPU->X, 0x23);
}

void test_adc_lda(struct cpu* CPU) {
    reset_cpu();
    uint8_t A = 0x47;
    uint8_t M = 0x24;
    uint8_t expected = 0x6B;
    uint8_t program[] = {0xA9, 0x47, 0x69, 0x24, 0x02};
    size_t program_len = sizeof(program) / sizeof(program[0]);
    load_program(program, program_len);
    execute();
    ASSERT_EQUAL(CPU->A, expected);

}

void test_brk(struct cpu* CPU) {
    reset_cpu();
    uint8_t program[] = {0xA9, 0x47, 0x69, 0x24, 0x00, 0x02};
    size_t program_len = sizeof(program) / sizeof(program[0]);
    CPU->memory[0xFFFF] = 0x41;
    CPU->memory[0xFFFE] = 0x07;
    CPU->memory[0x4107] = 0x02;    
    load_program(program, program_len);
    execute();
    ASSERT_EQUAL(1, process_status_val(INTERRUPT_DISABLED_FLAG));
    ASSERT_EQUAL(0x4108, CPU->PC);
}

void test_and(struct cpu* CPU) {
    reset_cpu();
    uint8_t expected = (0x47 & 0x31);
    uint8_t program[] = {0xA9, 0x47, 0x29, 0x31, 0x02};
    size_t program_len = sizeof(program) / sizeof(program[0]);    
    load_program(program, program_len);
    execute();
    ASSERT_EQUAL(CPU->A, expected);    
}

void test_asl_accumulator(struct cpu* CPU) {
    reset_cpu();
    uint8_t expected = (0x71 << 1);
    uint8_t program[] = {0xA9, 0x71, 0x0A, 0x02};
    size_t program_len = sizeof(program) / sizeof(program[0]);    
    load_program(program, program_len);
    execute();  
    ASSERT_EQUAL(expected, CPU->A);
}

void test_asl_memory(struct cpu* CPU) {
    reset_cpu();
    uint8_t expected = (0x71 << 1);
    uint8_t program[] = {0x06, 0x17, 0x02};
    size_t program_len = sizeof(program) / sizeof(program[0]);

    CPU->memory[0x0017] = 0x71;    
    load_program(program, program_len);
    execute();  
    ASSERT_EQUAL(expected, CPU->memory[0x0017]);
}

void test_bcc(struct cpu* CPU) {
    reset_cpu();
    uint16_t expected = 0x8005;
    uint8_t program[] = {0x90, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02};
    reset_process_status_reg(CARRY_FLAG);
    size_t program_len = sizeof(program) / sizeof(program[0]);    
    load_program(program, program_len);
    execute(); 
    ASSERT_EQUAL(expected, CPU->PC);
}

void test_bcs(struct cpu* CPU) {
    reset_cpu();
    uint16_t expected = 0x8005;
    uint8_t program[] = {0xB0, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02};
    set_process_status_reg(CARRY_FLAG);
    size_t program_len = sizeof(program) / sizeof(program[0]);    
    load_program(program, program_len);
    execute(); 
    ASSERT_EQUAL(expected, CPU->PC);
}

void test_beq(struct cpu* CPU) {
    reset_cpu();
    uint16_t expected = 0x8005;
    uint8_t program[] = {0xF0, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02};
    set_process_status_reg(ZERO_FLAG);
    size_t program_len = sizeof(program) / sizeof(program[0]);    
    load_program(program, program_len);
    execute(); 
    ASSERT_EQUAL(expected, CPU->PC);
}

void test_bit(struct cpu* CPU) {
    reset_cpu();
    uint8_t expected = 0b11000010;
    CPU->A = 0x12;
    CPU->memory[0x0045] = 0xC5;

    uint8_t program[] = {0x24, 0x45, 0x02};
    size_t program_len = sizeof(program) / sizeof(program[0]);    
    load_program(program, program_len);
    execute();
    ASSERT_EQUAL(CPU->P, expected);    

}

void test_bmi(struct cpu* CPU) {
    reset_cpu();
    uint16_t expected = 0x8005;
    uint8_t program[] = {0x30, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02};
    set_process_status_reg(NEGATIVE_FLAG);
    size_t program_len = sizeof(program) / sizeof(program[0]);    
    load_program(program, program_len);
    execute(); 
    ASSERT_EQUAL(expected, CPU->PC);
}

void test_bne(struct cpu* CPU) {
    reset_cpu();
    uint16_t expected = 0x8005;
    uint8_t program[] = {0xD0, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02};
    reset_process_status_reg(ZERO_FLAG);
    size_t program_len = sizeof(program) / sizeof(program[0]);    
    load_program(program, program_len);
    execute(); 
    ASSERT_EQUAL(expected, CPU->PC);
} 

void test_bpl(struct cpu* CPU) {
    reset_cpu();
    uint16_t expected = 0x8005;
    uint8_t program[] = {0x10, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02};
    reset_process_status_reg(NEGATIVE_FLAG);
    size_t program_len = sizeof(program) / sizeof(program[0]);    
    load_program(program, program_len);
    execute(); 
    ASSERT_EQUAL(expected, CPU->PC);
}

void test_bvc(struct cpu* CPU) {
    reset_cpu();
    uint16_t expected = 0x8005;
    uint8_t program[] = {0x50, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02};
    reset_process_status_reg(OVERFLOW_FLAG);
    size_t program_len = sizeof(program) / sizeof(program[0]);    
    load_program(program, program_len);
    execute(); 
    ASSERT_EQUAL(expected, CPU->PC);   
}

void test_bvs(struct cpu* CPU) {
    reset_cpu();
    uint16_t expected = 0x8005;
    uint8_t program[] = {0x70, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02};
    set_process_status_reg(OVERFLOW_FLAG);
    size_t program_len = sizeof(program) / sizeof(program[0]);    
    load_program(program, program_len);
    execute(); 
    ASSERT_EQUAL(expected, CPU->PC);   
}

void test_clc(struct cpu* CPU) {
    reset_cpu();
    set_process_status_reg(CARRY_FLAG);
    uint8_t expected = 0b00000000;
    uint8_t program[] = {0x18, 0x02};
    size_t program_len = sizeof(program) / sizeof(program[0]);    
    load_program(program, program_len);
    execute(); 
    ASSERT_EQUAL(expected, CPU->P);    
}

void test_cld(struct cpu* CPU) {
    reset_cpu();
    set_process_status_reg(DECIMAL_MODE_FLAG);
    uint8_t expected = 0b00000000;
    uint8_t program[] = {0xD8, 0x02};
    size_t program_len = sizeof(program) / sizeof(program[0]);    
    load_program(program, program_len);
    execute(); 
    ASSERT_EQUAL(expected, CPU->P);    
}

void test_clv(struct cpu* CPU) {
    reset_cpu();
    set_process_status_reg(OVERFLOW_FLAG);
    uint8_t expected = 0b00000000;
    uint8_t program[] = {0xB8, 0x02};
    size_t program_len = sizeof(program) / sizeof(program[0]);    
    load_program(program, program_len);
    execute(); 
    ASSERT_EQUAL(expected, CPU->P);    
}

int main() {

    /* Append function pointer to this list */
    void (*utest_ptr[]) (struct cpu* c) = {test_ldx                     \
                                  ,test_immediate                       \
                                  ,test_zero_page                       \
                                  ,test_zero_page_x                     \
                                  ,test_absolute                        \
                                  ,test_absolute_x                      \
                                  ,test_indirect_x                      \
                                  ,test_adc_lda                         \
                                  ,test_brk                             \
                                  ,test_and                             \
                                  ,test_asl_accumulator                 \
                                  ,test_asl_memory                      \
                                  ,test_bcc                             \
                                  ,test_bcs                             \
                                  ,test_beq                             \
                                  ,test_bit                             \
                                  ,test_bmi                             \
                                  ,test_bne                             \
                                  ,test_bpl                             \
                                  ,test_bvc                             \
                                  ,test_bvs                             \
                                  ,test_clc                             \
                                  ,test_cld                             \
                                  ,test_clv
                                  };
    size_t len = sizeof(utest_ptr)/sizeof(utest_ptr[0]);
    for(size_t i = 0; i < len; i ++) {
        (*utest_ptr[i])(&CPU);
    }
}
