#ifndef _CPU_H
#define _CPU_H

#include <stdint.h>

/* Macros */
#define MEM_SIZE            0xFFFF
#define MEM_PROG_BEGIN      0x8000
#define STACK_OFFSET_VAL    0x0100
#define STACK_BEGIN         0xFF 
#define IRQ_ADDR            0xFFFE

/* CPU definition */
struct cpu
{
    uint16_t PC; 
    uint8_t SP;
    uint8_t A;
    uint8_t X;
    uint8_t Y;
    uint8_t P;
    uint8_t memory[MEM_SIZE];
} CPU;

typedef enum {
    CARRY_FLAG,
    ZERO_FLAG,
    INTERRUPT_DISABLED_FLAG,
    DECIMAL_MODE_FLAG,
    BREAK_FLAG,
    UNUSED_FLAG,
    OVERFLOW_FLAG,
    NEGATIVE_FLAG,
} PS_FLAG;

/* Addressing Modes */
typedef enum addressing_modes {
    Immediate,
    ZeroPage,
    ZeroPageX,
    ZeroPageY,
    Absolute,
    AbsoluteX,
    AbsoluteY,
    IndirectX,
    IndirectY,
    Accumulator,
    Implied,
    Indirect
} admod;


/* Function Prototypes */

void display_cpu_regs(void);
uint8_t mem_read(uint16_t mem_addr);
uint16_t mem_read_u16(uint16_t mem_addr);
void mem_write(uint16_t mem_addr, uint8_t data);
void load_program(uint8_t *program, size_t len);
void execute(void);
uint16_t operand_address_resolve(admod mode);
void set_process_status_reg(PS_FLAG FLAG);
void reset_process_status_reg(PS_FLAG FLAG);
int process_status_val(PS_FLAG FLAG);
void reset_cpu(void);
void push(uint8_t stack_data);
void push_u16(uint16_t stack_data);
uint8_t pull();
uint16_t pull_u16();


#endif // _CPU_H
