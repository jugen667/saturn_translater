// ========================================
// > Author :   jugen 667 
// > Title  :   defs.h
// > Desc.  :   Header with node structs   
//              and enums
// ========================================

#ifndef _DEFS_H_
#define _DEFS_H_

#include <stdint.h>

#define DEFAULT_OUTFILE "out.s"
#define DEFAULT_TRACE_LEVEL 0

#define VAR_MAX_SIZE 32
#define VAR_MAX_NUMBER 32


#define printf_level(level, ...) ({         \
    if (level < trace_level) {              \
        printf(__VA_ARGS__);                \
    }                                       \
})


typedef enum { false = 0, true = !false } bool;

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
    node_nature nature;
    node_type type;

    int32_t int_value;
    double float_value;         // double for accuracy 
    int32_t address;            // adress on 5 nibbles (20 bits)
    bool global_decl;
    int32_t lineno;

    int32_t nops;
    struct _node_s ** opr;
    
    struct _node_s * decl_node;

    char * ident;               // array ? 
    char * str;

    // Pour l'affichage du graphe
    int32_t node_num;

} node_s;

typedef node_s * node_t;


typedef struct{
    char varName[VAR_MAX_SIZE];
    node_t node;
} decl_table;

#endif

