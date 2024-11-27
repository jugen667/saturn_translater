// ========================================
// > Author :   jugen 667 
// > Title  :   arch.c
// > Desc.  :   Architecture description
// > Associated header : arch.h
// ========================================

#include <stdint.h>

#include "../include/arch.h"

#define working_registers   4       // A, B, C, D               = 64 bits each
#define pointer_registers   2       // D0, D1                   = 20 bits each (five nibbles)
#define save_registers      5       // R0, R1, R2, R3, R4, R5   = temporary area 64 bits each 

// Useless to use less than 2 pointers regs and less than 4 working reg

static int32_t max_save_regs = save_registers;


void set_max_registers(int32_t n) {
    max_save_regs = n;
}

int32_t get_num_registers() {
    return max_save_regs;
}

int32_t get_save_registers() {
    return save_registers;
}