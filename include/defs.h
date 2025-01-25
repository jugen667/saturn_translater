// ========================================
// > Author :   jugen 667 
// > Title  :   defs.h
// > Desc.  :   Header with node structs   
//              and arch specs
// ========================================

#ifndef _DEFS_H_
#define _DEFS_H_

#include <stdint.h>

// for pre-C99 standard
typedef enum { false = 0, true = !false } bool;

// ===== register description =====
// ======================= REGISTER STRUCTURES IN HP48 ======================== //
//                                                                              //
//      | F | E | D | C | B | A | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |       //
//      |                                                               |       //
//       <------------------------------W------------------------------>        //
//                                               <----------A---------->        //
//                                                           <----X---->        //
//                                                           <XS>               //
//                                                               <--B-->        //
//           <-----------------------M--------------------->                    //
//       <S>                                                                    //
//                                                                              //
// ============================================================================ //

enum REGISTER_TYPE  // each of 64 bits (16 nibbles)
{
    T_WORKING,
    T_SAVE,
    T_POINTER,
    MAX_REGISTER_TYPE,
};
enum WORKING_REGISTER   // each of 64 bits (16 nibbles)
{
    A,
    B,
    C,
    D,
    MAX_WORKING_REGISTER,
};

enum SAVE_REGISTER      // each of 64 bits (16 nibbles)
{
    R0,
    R1,
    R2,
    R3,
    R4,
    MAX_SAVE_REGISTER,
};

enum HARDWARE_STATUS  
{
    SR,                 // Service Request
    SB,                 // Sticky Bit
    MP,                 // Module Pulled
    XM,                 // eXternal Module missing
    MAX_HST,
};

enum POINTER_REGISTER   // 5 nibbles each (an adress is 5 nibbles)
{
    D0,
    D1,
    MAX_POINTER_REGISTER
};

enum REGISTER_FIELDS
{
    W_FIELD,            // WORD (64 bits = 16 nibbles)
    A_FIELD,            // ADRESS (5 lowest nibbes)
    B_FIELD,            // BYTE (1 BYTE nibble 1 & nibble 0)
    X_FIELD,            // X go along OUT coponent of the CPU (3 nibbles)
    XS_FIELD,           // XS MSB of X_FIELD (1 nibble) [XS = eXponent Sign]
    M_FIELD,            // MANTISSA, nibble 3 to 14
    S_FIELD,            // SIGN, last nibble of the register; nibble 15
    WP_FIELD,           // user defined, start at the value of P
    P_FIELD,            // definition for WP field (can be used as a field can store one nibble but is a register)
    MAX_FIELD,
};

enum DIRECTION          // for bit/nibble shift
{
    RIGHT,
    LEFT,
    MAX_DIRECTION,
};

// ================================

// ===== Address description =====
#define MAX_ADDRESS_512KB       0xFFFFF         // 5 nibbles for address 
#define MAX_PRACTICAL_ADDRESS   0x7DFFF         // for test case of GX
#define MIN_ADDRESS             0x00140         // first address allowed 

// add forbidden subroutine ??

// -- Memory mapping -- useless maybe with RAM card but not implemented
// __ TO DO __ but add different targets

// ===============================

// ===== Node description =====

#define VAR_MAX_SIZE 32
#define VAR_MAX_NUMBER 32

#define printf_level(level, ...) ({         \
    if (level < trace_level) {              \
        printf(__VA_ARGS__);                \
    }                                       \
})


typedef enum node_nature_s {
    NONE,
    NODE_PROGRAM,
    NODE_BLOCK,
    NODE_LIST,
    NODE_DECLS,
    NODE_DECL,
    NODE_IDENT,
    NODE_TYPE,
    NODE_INTVAL,
    NODE_FLOATVAL,      
    NODE_BOOLVAL,
    NODE_STRINGVAL,
    NODE_FUNC,
    NODE_IF,
    NODE_WHILE,
    NODE_FOR,
    NODE_DOWHILE,
    NODE_PLUS,
    NODE_MINUS,
    NODE_MUL,
    NODE_DIV,
    NODE_MOD,
    NODE_LT,
    NODE_GT,
    NODE_LE,
    NODE_GE,
    NODE_EQ,
    NODE_NE,
    NODE_AND,
    NODE_OR,
    NODE_BAND,
    NODE_BOR,
    NODE_BXOR,
    NODE_NOT,
    NODE_BNOT,
    NODE_SLL,
    NODE_SRA,
    NODE_SRL,
    NODE_UMINUS,
    NODE_AFFECT,
    NODE_PRINT,
    NODE_ELSE,
} node_nature;


typedef enum node_type_s {
    TYPE_NONE,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_BOOL,
    TYPE_VOID,
} node_type;


// === NODE STRUCT ===
typedef struct _node_s {
    // node info
    node_nature nature;
    node_type type;
    int32_t nops;
    struct _node_s ** opr;
    
    // node values
    uint64_t value;
    uint32_t address;            // adress on 5 nibbles (20 bits)
    bool global_decl;
    int32_t lineno;
    char * ident;
    char * str;

    // for tree dump
    int32_t node_num;
} node_s;

typedef node_s * node_t;


typedef struct{
    char varName[VAR_MAX_SIZE];
    node_t node;
} decl_table;

// =============================

#endif

